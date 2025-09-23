#include <iostream>
#include <string>
#include <cctype> // for std::toupper
#include <array>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

// Funktion til at kapitalisere det første bogstav i en streng
string Capitalize(const std::string& input) {
    if (input.empty()) return input; // tom streng = retur som er

    std::string result = input; // kopiér input
    result[0] = std::toupper(static_cast<unsigned char>(result[0]));
    return result;
}

int getNextId(const std::vector<Customer>& customers) {
    int maxId = 0; // start at 0
    for (const auto& c : customers) {
        if (c.id > maxId) {
            maxId = c.id;
        }
    }
    return maxId + 1; // next ID
}

// List of functions used in the program
void user();
void shop();
void shop_menu();
void shop_products();
void shop_basket();
void shop_about();
void shop_user();

int i; // loop variabel

struct Product {
    int id;
    string name;
    double price;
};

Product products[] = {
    {1, "Æble", 5.0},
    {2, "Banan", 6.0},
    {3, "Gulerod", 2.0}
};
int maxProducts = sizeof(products) / sizeof(products[0]);

struct Customer {
    string name;
    int id;
    double userCoupon;
    string password;
};

Customer customer;

void to_json(json& j, const Customer& c) {
    j = json{
        {"name", c.name},
        {"id", c.id},
        {"userCoupon", c.userCoupon},
        {"password", c.password}
    };
}

void from_json(const json& j, Customer& c) {
    j.at("name").get_to(c.name);
    j.at("id").get_to(c.id);
    j.at("userCoupon").get_to(c.userCoupon);
    j.at("password").get_to(c.password);
}

void saveCustomers(const vector<Customer>& customers, const string& filename) {
    json j;
    j["customers"] = customers; // thanks to to_json
    ofstream file(filename);
    file << j.dump(4); // pretty print
}

vector<Customer> loadCustomers(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    vector<Customer> customers = j.at("customers").get<vector<Customer>>();
    return customers;
}


void user(){
    cout << "Welcome to the shop! What is your name?" << endl;
    cin >> customer.name;
    if (customer.name.empty()) {
        cout << "Name cannot be empty. Please enter your name: ";
        cin >> customer.name;
    }
    else if (!isalpha(customer.name[0])) {
        cout << "Name must start with a letter. Please enter a valid name: ";
        cin >> customer.name;
    }
    else if (customer.name.length() > 20) {
        cout << "Name is too long. Please enter a name with less than 50 characters: ";
        cin >> customer.name;
    }
    else if (customer.name.length() < 2) {
        cout << "Name is too short. Please enter a name with at least 2 characters: ";
        cin >> customer.name;
    }
    else if (customer.name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
        cout << "Name contains invalid characters. Please enter a name with only letters: ";
        cin >> customer.name;
    }
    else if (customer.name.find(' ') != string::npos) {
        cout << "Name cannot contain spaces. Please enter a name without spaces: ";
        cin >> customer.name;
    }

    customer.name = Capitalize(customer.name); // Kapitaliserer det første bogstav i navnet
    cout << "Please enter your customer ID: " << endl;
    cin >> customer.id;

    if (customer.id < 1 || customer.id > 10000) {
        cout << "Invalid ID. Please enter a number between 1 and 10000: ";
        cin >> customer.id;
    }
    else if (customer.id == 0) {
        cout << "ID cannot be zero. Please enter a valid ID: ";
        cin >> customer.id;
    }
    else if (isdigit(customer.id)){
        cout << "ID must be a number. Please enter a valid ID: ";
        cin >> customer.id;
    }


    cout << "Thank you, " << customer.name << ". Your customer ID is " << customer.id << "." << endl;
    cout << "Do you have a coupon? If yes, please enter the discount percentage (e.g., 10 for 10%). If no, enter 0." << endl;
    cin >> customer.userCoupon;
    if (customer.userCoupon < 0 || customer.userCoupon > 100) {
        cout << "Invalid coupon percentage. Setting coupon to 0%." << endl;
        customer.userCoupon = 0;
    }
    cout << "You have a coupon for " << customer.userCoupon << "% off your total purchase." << endl;
    cout << "\n-----------------------------" << endl;
    cout << "Welcome, " << customer.name << "! Let's start shopping!" << endl;
    cout << "-----------------------------" << endl;

    
    cin >> customer.password;
    // Now we decrypt the password
    
    
    

    // Save all the data so it can be used in the shop function
    // Passing customer to shop function could be done with global variable or passing as parameter
    // For simplicity, we will use a global variable here
    // In a larger program, consider using a more robust method like a class or passing parameters
    // Here we will use a global variable for the coupon
    
}

bool running = true;
int basket = 0; // Total pris af varer i kurven



void shop_products(){
    while (running){
    }
}

void shop_basket(){

}
 
void shop_about(){

}

void shop_user(){
    cout << "-----------------------------" << endl;
    cout << "Information about the user:" << endl;
    cout << "Name: " << customer.name << endl;
    cout << "Customer ID: " << customer.id << endl;
    cout << "Coupon: " << customer.userCoupon << "%" << endl;
    cout << "-----------------------------" << endl;
    
    cout << "\nDo you wish to go to the menu?" << endl;
    cout << "1) Yes \n2) No" << endl;
    int choice;
    cin >> choice;
    if (choice == 2){
        cout << "Thank you for visiting the shop!" << endl;
        return;
    }
    else if (choice != 1){
        cout << "Invalid choice. Returning to menu." << endl;
    }
    shop_menu();
    return;
}

void shop_menu(){
    cout << "How can I help you?\n 1) View products \n 2) View basket \n 3) About us \n 4) User Information" << endl;
    int choice;
    cin >> choice;
    cout << " " << endl; // blank linje
    if (choice == 1){
        shop_products();
    }
    else if (choice == 2){
        shop_basket();
    }
    else if (choice == 3){
        shop_about();
        return;
    }
    else if (choice == 4){
        shop_user();
        return;
    }
    else {
        cout << "Invalid choice. Please select a number between 1 and 3." << endl;
        shop_menu();
    }
}


// Lav shop delen
void shop(){

    cout << "How can I help you?\n 1) View products \n 2) View basket \n 3) About us" << endl;
    int choice;
    cin >> choice;
    cout << " " << endl; // blank linje
    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Please select a number between 1 and 3." << endl;
    }
    if (choice == 1){
        cout << "You chose to view products." << endl;
    }
    else if (choice == 2){
        cout << "You chose to view your basket." << endl;
    }
    else if (choice == 3){
        cout << "You chose to learn about us." << endl;
        cout << "We are a small shop selling fruits and vegetables." << endl;
        cout << "We have been in business for 10 years." << endl;
        return;
    }
    else {
        cout << "Invalid choice. Please select a number between 1 and 3." << endl;
        return; // Slukker programmet med en fejl kode
    }
    cout << "You chose " << choice << endl;
    while (running){
        for (i = 0; i < maxProducts; i++) {
            cout << products[i].id << ") " << products[i].name << " - " << products[i].price << " DKK" << endl;
        }
        cout << "-----------------------------" << endl;
        cout << "Please enter the ID of the product you want to add to your basket: ";
        cin >> choice;
        if (choice < 1 || choice > maxProducts) {
            cout << "Invalid product ID. Please select a valid ID." << endl;
        } 
        else {
            cout << products[choice - 1].name << " has been added to your basket." << endl;
            basket += products[choice - 1].price; // Tilføjer prisen af det valgte produkt til kurvens total
        }
        cout << "Your basket total is now: " << basket << ",- DKK (Without coupon)" << endl;
        cout << "-----------------------------" << endl;

        /*
        Tjekker om brugeren vil fortsætte eller afslutte
        Hvis de vælger at afslutte, sættes running til false og while loopet stopper
        - Der printes en tak besked og prisen af deres varer i kurven

        Hvis de vælger at fortsætte, fortsætter loopet
        */

        cout << "Do you want to continue shopping? (y/n): ";
        char cont;
        cin >> cont;
        if (cont == 'n' || cont == 'N') {
            running = false;
            cout << "Thank you for shopping with us!" << endl;
            
            cout << "Your total is: " << basket - (basket * (customer.userCoupon / 100)) << ",- DKK" << endl; 
            cout << "Thanks for shopping with us " << customer.name << "!" << endl;
            shop(); // Går tilbage til shop menuen
            return;
        }
        if (cont == 'y' || cont == 'Y') {
            cout << "Continuing shopping..." << endl;
        }
        else {
            cout << "Invalid input. Please enter 'y' to continue or 'n' to exit." << endl;
        }
    }
}

void user_creation(){
    vector<Customer> customers = loadCustomers("customers.json");

    
}

int main() {
    // 1. Create some customers
    vector<Customer> customers = {
        {"Mathias", 1, 20.5, "mypassword"},
        {"Anna", 2, 15.0, "anotherpass"}
    };

    // 2. Save them
    saveCustomers(customers, "customers.json");

    // 3. Load them back 

    vector<Customer> loaded = loadCustomers("customers.json");

    // 4. Print loaded customers
    for (const auto& c : loaded) {
        cout << "Name: " << c.name
             << " | ID: " << c.id
             << " | Coupon: " << c.userCoupon
             << " | Password: " << c.password << endl;
    }

    return 0;
}