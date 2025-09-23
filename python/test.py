import json
import os
import tkinter as tk
from tkinter import messagebox, simpledialog

# ----------------- Data -----------------
PRODUCTS = [
    {"id": 1, "name": "Æble", "price": 5.0},
    {"id": 2, "name": "Banan", "price": 6.0},
    {"id": 3, "name": "Gulerod", "price": 2.0},
]

USER_FILE = "customers.json"
current_user = None

# ----------------- Helper Functions -----------------
def load_users():
    if not os.path.exists(USER_FILE):
        return []
    with open(USER_FILE, "r") as f:
        return json.load(f)

def save_users(users):
    with open(USER_FILE, "w") as f:
        json.dump(users, f, indent=4)

def username_exists(username):
    users = load_users()
    return any(u["username"] == username for u in users)

def get_next_id():
    users = load_users()
    if not users:
        return 1
    return max(u["id"] for u in users) + 1

def basket_total(user):
    total = 0
    counts = {}
    for pid in user["basket"]:
        counts[pid] = counts.get(pid, 0) + 1
    for pid, qty in counts.items():
        total += PRODUCTS[pid-1]["price"] * qty
    total *= (1 - user["coupon"]/100)
    return total

def save_current_user():
    users = load_users()
    for i, u in enumerate(users):
        if u["username"] == current_user["username"]:
            users[i] = current_user
            break
    save_users(users)

# ----------------- GUI Functions -----------------
def register():
    global current_user
    name = simpledialog.askstring("Register", "Enter your full name:")
    if not name:
        messagebox.showerror("Error", "Name cannot be empty.")
        return register()

    while True:
        username = simpledialog.askstring("Register", "Choose a username:")
        if username_exists(username):
            messagebox.showerror("Error", "Username already exists (case-insensitive).")
        else:
            break

    password = simpledialog.askstring("Register", "Set a password:", show="*")
    coupon = simpledialog.askfloat("Register", "Enter coupon % (0 if none):", minvalue=0, maxvalue=100)

    current_user = {
        "name": name.capitalize(),
        "username": username,  # keep original casing
        "id": get_next_id(),
        "password": password,
        "coupon": coupon or 0,
        "balance": 1000.0,
        "basket": []
    }

    users = load_users()
    users.append(current_user)
    save_users(users)
    messagebox.showinfo("Success", f"Registration complete! Welcome {username}!")


def login():
    global current_user
    username = simpledialog.askstring("Login", "Enter your username:")
    password = simpledialog.askstring("Login", "Enter your password:", show="*")
    users = load_users()
    for u in users:
        if u["username"] == username and u["password"] == password:
            current_user = u
            messagebox.showinfo("Success", f"Welcome back, {username}!")
            return True
    messagebox.showerror("Error", "Login failed. Invalid username or password.")
    return False

# ----------------- Shop GUI -----------------
class ShopGUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Mini Shop")
        self.geometry("600x500")
        self.configure(bg="#f0f0f0")

        tk.Label(self, text=f"Welcome {current_user['username']}! Balance: {current_user['balance']:.2f} DKK",
                 bg="#f0f0f0", font=("Helvetica", 12, "bold")).pack(pady=10)

        # Products frame
        self.products_frame = tk.Frame(self, bg="#f0f0f0")
        self.products_frame.pack(pady=10)
        tk.Label(self.products_frame, text="Products:", font=("Helvetica", 12, "bold"), bg="#f0f0f0").grid(row=0, column=0, columnspan=2)
        for idx, p in enumerate(PRODUCTS, start=1):
            tk.Label(self.products_frame, text=f"{p['name']} - {p['price']} DKK", bg="#f0f0f0").grid(row=idx, column=0, padx=5, pady=5)
            tk.Button(self.products_frame, text="Add to Basket", command=lambda pid=p["id"]: self.add_to_basket(pid),
                      bg="#4caf50", fg="white").grid(row=idx, column=1, padx=5, pady=5)

        # Basket frame
        self.basket_frame = tk.Frame(self, bg="#f0f0f0")
        self.basket_frame.pack(pady=10, fill=tk.X)
        tk.Label(self.basket_frame, text="Basket:", font=("Helvetica", 12, "bold"), bg="#f0f0f0").pack()
        self.basket_text = tk.Text(self.basket_frame, height=8, width=50, state=tk.DISABLED, bg="#e0e0e0")
        self.basket_text.pack(padx=5, pady=5)
        self.update_basket_text()

        tk.Button(self.basket_frame, text="Remove Selected", command=self.remove_selected, bg="#f44336", fg="white").pack(pady=2)
        tk.Button(self.basket_frame, text="Pay", command=self.pay, bg="#2196f3", fg="white").pack(pady=2)

        # User info and logout
        control_frame = tk.Frame(self, bg="#f0f0f0")
        control_frame.pack(pady=10)
        tk.Button(control_frame, text="User Info", command=self.show_user_info, bg="#ff9800", fg="white", width=15).grid(row=0, column=0, padx=10)
        tk.Button(control_frame, text="Logout", command=self.logout, bg="#9c27b0", fg="white", width=15).grid(row=0, column=1, padx=10)

    # ----------------- Basket Handling -----------------
    def add_to_basket(self, pid):
        current_user["basket"].append(pid)
        save_current_user()
        self.update_basket_text()

    def update_basket_text(self):
        counts = {}
        for pid in current_user["basket"]:
            counts[pid] = counts.get(pid, 0) + 1

        self.basket_text.config(state=tk.NORMAL)
        self.basket_text.delete("1.0", tk.END)
        for pid, qty in counts.items():
            p = PRODUCTS[pid-1]
            self.basket_text.insert(tk.END, f"{p['name']} x{qty} - {p['price']*qty:.2f} DKK\n")
        total = basket_total(current_user)
        self.basket_text.insert(tk.END, f"\nTotal (with coupon {current_user['coupon']}%): {total:.2f} DKK")
        self.basket_text.config(state=tk.DISABLED)

    def remove_selected(self):
        selected = self.basket_text.index(tk.SEL_FIRST).split(".")[0]  # line number
        line_num = int(selected) - 1
        counts = {}
        for pid in current_user["basket"]:
            counts[pid] = counts.get(pid, 0) + 1
        pid_to_remove = list(counts.keys())[line_num]
        current_user["basket"].remove(pid_to_remove)
        save_current_user()
        self.update_basket_text()

    def pay(self):
        total = basket_total(current_user)
        if total > current_user["balance"]:
            messagebox.showerror("Error", "Insufficient balance!")
            return
        current_user["balance"] -= total
        current_user["basket"].clear()
        save_current_user()
        self.update_basket_text()
        messagebox.showinfo("Success", f"Payment successful! Remaining balance: {current_user['balance']:.2f} DKK")

    def show_user_info(self):
        info = f"Name: {current_user['name']}\nUsername: {current_user['username']}\n"
        info += f"ID: {current_user['id']}\nCoupon: {current_user['coupon']}%\nBalance: {current_user['balance']:.2f} DKK"
        messagebox.showinfo("User Info", info)

    def logout(self):
        save_current_user()
        messagebox.showinfo("Logout", "You have been logged out.")
        self.destroy()

# ----------------- Start -----------------
if __name__ == "__main__":
    root = tk.Tk()
    root.withdraw()  # hide root

    if messagebox.askyesno("Welcome", "Do you want to login? (No = Register)"):
        if not login():
            exit()
    else:
        register()

    app = ShopGUI()
    app.mainloop()
