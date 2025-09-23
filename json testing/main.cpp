#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

// ---------- Structs ----------
struct Product {
    int id;
    string name;
    double price;
    int stock;
};

struct Customer {
    string name;
    string username;
    string password;
    double coupon;
    double balance;
    vector<int> basket; // product IDs
};

// ---------- JSON Serialization ----------
void to_json(json& j, const Product& p) {
    j = json{{"id", p.id}, {"name", p.name}, {"price", p.price}, {"stock", p.stock}};
}

void from_json(const json& j, Product& p) {
    j.at("id").get_to(p.id);
    j.at("name").get_to(p.name);
    j.at("price").get_to(p.price);
    j.at("stock").get_to(p.stock);
}

void to_json(json& j, const Customer& c) {
    j = json{{"name", c.name}, {"username", c.username}, {"password", c.password},
             {"coupon", c.coupon}, {"balance", c.balance}, {"basket", c.basket}};
}

void from_json(const json& j, Customer& c) {
    j.at("name").get_to(c.name);
    j.at("username").get_to(c.username);
    j.at("password").get_to(c.password);
    j.at("coupon").get_to(c.coupon);
    j.at("balance").get_to(c.balance);
    j.at("basket").get_to(c.basket);
}

// ---------- File Operations ----------
vector<Product> loadProducts(const string& filename) {
    ifstream file(filename);
    if (!file) return {};
    json j;
    file >> j;
    return j.get<vector<Product>>();
}

void saveProducts(const vector<Product>& products, const string& filename) {
    json j = products;
    ofstream file(filename);
    file << j.dump(4);
}

vector<Customer> loadCustomers(const string& filename) {
    ifstream file(filename);
    if (!file) return {};
    json j;
    file >> j;
    return j.get<vector<Customer>>();
}

void saveCustomers(const vector<Customer>& customers, const string& filename) {
    json j = customers;
    ofstream file(filename);
    file << j.dump(4);
}

// ---------- Helper Functions ----------
bool usernameExists(const vector<Customer>& users, const string& username) {
    for (const auto& u : users) {
        string uname_lower = username;
        string u_lower = u.username;
        transform(uname_lower.begin(), uname_lower.end(), uname_lower.begin(), ::tolower);
        transform(u_lower.begin(), u_lower.end(), u_lower.begin(), ::tolower);
        if (uname_lower == u_lower) return true;
    }
    return false;
}

Customer* login(vector<Customer>& users) {
    string username, password;
    cout << "\n╔════════════════ LOGIN ════════════════╗\n";
    cout << "Username: "; cin >> username;
    cout << "Password: "; cin >> password;

    for (auto& u : users) {
        if (u.username == username && u.password == password) {
            cout << "╚══════════ Login successful! ══════════╝\n";
            return &u;
        }
    }
    cout << "╚══════ Invalid credentials ════════════╝\n";
    return nullptr;
}

Customer* registerUser(vector<Customer>& users) {
    string name, username, password;
    double coupon;
    cin.ignore(); // clear input buffer
    cout << "\n╔════════════ REGISTER ════════════════╗\n";
    cout << "Full Name: "; getline(cin, name);

    do {
        cout << "Username: "; cin >> username;
        if (usernameExists(users, username))
            cout << "Username taken! Try again.\n";
        else break;
    } while (true);

    cout << "Password: "; cin >> password;
    cout << "Coupon % (0 if none): "; cin >> coupon;

    Customer c{name, username, password, coupon, 1000.0, {}};
    users.push_back(c);
    cout << "╚══════════ Registration complete ══════╝\n";
    return &users.back();
}

// ---------- Shop Functions ----------
void displayProducts(const vector<Product>& products) {
    cout << "\n╔════════════ PRODUCTS ═════════════════╗\n";
    for (const auto& p : products) {
        cout << "| [" << p.id << "] " << setw(10) << left << p.name
             << "Price: " << setw(5) << p.price
             << "Stock: " << setw(3) << p.stock << " |\n";
    }
    cout << "╚═══════════════════════════════════════╝\n";
}

void addToBasket(Customer& user, vector<Product>& products) {
    int id;
    cout << "Enter product ID to add: "; cin >> id;
    auto it = find_if(products.begin(), products.end(), [id](Product& p){ return p.id == id; });
    if (it == products.end()) { cout << "Invalid ID.\n"; return; }
    if (it->stock <= 0) { cout << "Out of stock!\n"; return; }
    user.basket.push_back(it->id);
    cout << it->name << " added to basket.\n";
}

void viewBasket(const Customer& user, const vector<Product>& products) {
    if (user.basket.empty()) {
        cout << "Basket is empty.\n";
        return;
    }

    cout << "\n╔════════════ BASKET ═════════════════╗\n";
    vector<int> counted;
    double total = 0;
    for (int pid : user.basket) {
        if (find(counted.begin(), counted.end(), pid) != counted.end()) continue;
        counted.push_back(pid);
        int quantity = count(user.basket.begin(), user.basket.end(), pid);
        auto it = find_if(products.begin(), products.end(), [pid](const Product& p){ return p.id == pid; });
        double price = it->price * quantity;
        cout << "| " << setw(10) << left << it->name
             << " x" << setw(3) << quantity
             << " - " << price << " DKK |\n";
        total += price;
    }
    total *= (1 - user.coupon / 100);
    cout << "| Total after coupon: " << total << " DKK" << setw(12) << "|\n";
    cout << "╚═══════════════════════════════════════╝\n";
}

void checkout(Customer& user, vector<Product>& products) {
    if (user.basket.empty()) { cout << "Basket empty!\n"; return; }

    double total = 0;
    for (int pid : user.basket) {
        auto it = find_if(products.begin(), products.end(), [pid](Product& p){ return p.id == pid; });
        total += it->price;
    }
    total *= (1 - user.coupon / 100);

    if (total > user.balance) {
        cout << "Insufficient balance!\n";
        return;
    }

    user.balance -= total;
    for (int pid : user.basket) {
        auto it = find_if(products.begin(), products.end(), [pid](Product& p){ return p.id == pid; });
        if (it->stock > 0) it->stock--;
    }
    user.basket.clear();
    cout << "Purchase successful! Remaining balance: " << user.balance << " DKK\n";
}

// ---------- Main ----------
int main() {
    vector<Product> products = loadProducts("products.json");
    vector<Customer> users = loadCustomers("users.json");

    cout << "\033[1;35m╔══════════════ MINI SHOP ══════════════╗\033[0m\n";
    cout << "1) Login\n2) Register\nChoose: ";
    int choice; cin >> choice;
    Customer* currentUser = nullptr;

    if (choice == 1) currentUser = login(users);
    else if (choice == 2) currentUser = registerUser(users);
    else return 0;

    if (!currentUser) return 0;

    bool running = true;
    while (running) {
        cout << "\n╔════════════ MENU ════════════════════╗\n";
        cout << "1) View Products\n2) View Basket\n3) Add Product\n4) Checkout\n5) User Info\n6) Exit\nChoose: ";
        cin >> choice;
        switch (choice) {
            case 1: displayProducts(products); break;
            case 2: viewBasket(*currentUser, products); break;
            case 3: addToBasket(*currentUser, products); break;
            case 4: checkout(*currentUser, products); break;
            case 5:
                cout << "\n╔════════════ USER INFO ═══════════════╗\n";
                cout << "| Name: " << setw(15) << left << currentUser->name
                     << " |\n| Username: " << setw(15) << currentUser->username
                     << " |\n| Balance: " << setw(10) << currentUser->balance
                     << " DKK |\n| Coupon: " << currentUser->coupon << "% |\n";
                cout << "╚═══════════════════════════════════════╝\n";
                break;
            case 6: running = false; break;
            default: cout << "Invalid choice.\n";
        }
    }

    saveProducts(products, "products.json");
    saveCustomers(users, "users.json");
    cout << "\033[1;35m╔════════════════ GOODBYE ══════════════╗\033[0m\n";
    return 0;
}
