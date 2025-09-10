import webbrowser
import tkinter as tk

def main():
    def open_google():
        webbrowser.open("https://www.google.com")

    root = tk.Tk()
    root.title("Open Google")

    button = tk.Button(root, text="Open Google.com", command=open_google)
    button.pack(padx=20, pady=20)

    root.mainloop()

if __name__ == "__main__":
    main()