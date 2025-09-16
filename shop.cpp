#include <iostream>
#include <string>
#include <cctype> // for std::toupper
#include <array>

using namespace std;

// Funktion til at kapitalisere det første bogstav i en streng
string Capitalize(const std::string& input) {
    if (input.empty()) return input; // tom streng = retur som er

    std::string result = input; // kopiér input
    result[0] = std::toupper(static_cast<unsigned char>(result[0]));
    return result;
}

struct Bruger {
    string navn;
    int alder;
    string email;
    string password;
};

struct Vare {
    string navn;
    double pris;
    int vareID;
    string kategori;
};

Vare varer[]{
    {"Apple", // Navn
        0.99, // Pris
        0, // VareID
        "Fruits" // Kategori
    },
    
    {"Banana", 0.59, 1, "Fruits"},
    {"Carrot", 0.79, 2, "Vegetables"},
    {"Date", 1.29, 3, "Fruits"},
    {"Eggplant", 1.49, 4, "Vegetables"},
    {"Fig", 2.99, 5, "Fruits"},
    {"Grape", 2.49, 6, "Fruits"},
    {"Honeydew", 3.99, 7, "Fruits"},
    {"Kiwi", 0.89, 8, "Fruits"},
    {"Lemon", 0.69, 9, "Fruits"},
    {"Macbook", 999.99, 10, "Electronics"},
    {"Acer", 799.99, 11, "Electronics"},
    {"Dell", 699.99, 12, "Electronics"},
    {"Asus", 899.99, 13, "Electronics"},
    {"Lenovo", 749.99, 14, "Electronics"},
    {"HP", 649.99, 15, "Electronics"},
    {"Samsung", 599.99, 16, "Electronics"},
    {"Sony", 549.99, 17, "Electronics"},
    {"LG", 499.99, 18, "Electronics"},
    {"HTC", 399.99, 19, "Electronics"}
};


int check;
int size;
string basket[100];
int basketCount = 0;
bool found = false;

array<double, 5> rabatniveauer = {0.0, 0.05, 0.10, 0.15, 0.20}; // Rabatniveauer i procent

int main() {
    cout << "Welcome to the Shop!" << endl;
    // Check if user is registered
    Bruger bruger;
    if (!found){
        cout << "Please register to continue." << endl;
        cout << "Enter your name: ";
        getline(cin, bruger.navn);
        cout << "Enter your age: ";
        cin >> bruger.alder;
        cin.ignore(); // Ryd input bufferen
        cout << "Enter your email: ";
        getline(cin, bruger.email);
        found = true;
        cout << "Registration complete!" << endl;
    }
    

    cout << "Hello " << Capitalize(bruger.navn) << ", age " << bruger.alder << ". Your email is " << bruger.email << "." << endl;
    // Show categories
    cout << "Here are the available categories:" << endl;
    cout << "1. Fruits" << endl;
    cout << "2. Vegetables" << endl;
    cout << "3. Electronics" << endl;
    cout << "Please enter a category to view items: ";

    // Læs nummeret for kategorien
    int categoryNumber;
    cin >> categoryNumber;
    cin.ignore(); // Ryd input bufferen
    string category;
    switch (categoryNumber) {
        case 1:
            category = "Fruits";
            break;
        case 2:
            category = "Vegetables";
            break;
        case 3:
            category = "Electronics";
            break;
        default:
            cout << "Invalid category number." << endl;
            return 1;
    }
    cout << "You selected: " << category << endl;
    cout << "Here are the items in this category:" << endl;
    int size = sizeof(varer) / sizeof(varer[0]);
    for (int i = 0; i < size; i++) {
        if (varer[i].kategori == category) {
            cout << "ID: " << varer[i].vareID << " | Name: " << varer[i].navn << " | Price: $" << varer[i].pris << endl;
        }
    }
    cout << "Please enter the ID of the item you wish to purchase: ";
    int itemID;
    cin >> itemID;
    cin.ignore(); // Ryd input bufferen
    // Add item to basket
    bool found = false;
    for (int i = 0; i < size; i++) {   
        if (varer[i].vareID == itemID) {
            basket[basketCount++] = varer[i].navn + " - $" + to_string(varer[i].pris);
            cout << "You have added: " << varer[i].navn << " for $" << varer[i].pris << " to your basket." << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Item with ID " << itemID << " not found." << endl;
    }
    cout << "Your basket contains:" << endl;
    for (int i = 0; i < basketCount; i++) {
        cout << "- " << basket[i] << endl;
    }
    cout << "Do you wish to add more items to your basket?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    int more;
    cin >> more;
    cin.ignore(); // Ryd input bufferen
    if (more == 1) {
        main(); // Restart processen
    } else {
        cout << "Thank you for shopping with us!" << endl;
        cout << "Your final basket contains:" << endl;
        for (int i = 0; i < basketCount; i++) {
            cout << "- " << basket[i] << endl;
        }
        cout << "That will be $" << endl;
        double total = 0.0;
        for (int i = 0; i < basketCount; i++) {
            size_t pos = basket[i].find("$");
            if (pos != string::npos) {
                total += stod(basket[i].substr(pos + 1));
            }
        }
        cout << total << endl;
        cout << "Have a great day " << bruger.navn << "!" << endl;
    }


    
    /*
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (varer[i].vareID == itemID) {
            cout << "You have purchased: " << varer[i].navn << " for $" << varer[i].pris << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Item with ID " << itemID << " not found." << endl;
    }
    cout << "Thank you for shopping with us!" << endl;
    */


    return 0;
}


