#include <iostream>
#include <string>   
using namespace std;

// Listen af strings
string qname;
string names[] = {"Sebastian, ", "Oliver, ", "Ruben."};

string categories[] = {"Fruits", "Vegetables", "Electronics"};

string items[] = 
{
    "apple", 
    "banana", 
    "carrot", 
    "date", 
    "eggplant", 
    "fig", 
    "grape", 
    "honeydew", 
    "kiwi", 
    "lemon", 
    "macbook", 
    "acer", 
    "dell", 
    "asus", 
    "lenovo", 
    "hp", 
    "samsung", 
    "sony", 
    "lg", 
    "htc"
};
double prices[] = 
{
    0.99, 
    0.59, 
    0.79, 
    1.29, 
    1.49, 
    2.99, 
    2.49, 
    3.99, 
    0.89, 
    0.69, 
    999.99, 
    799.99, 
    699.99, 
    899.99, 
    749.99, 
    649.99, 
    599.99, 
    549.99, 
    499.99, 
    399.99
};

string vareID[] = 
{
    "Apple 0", 
    "Banana 1", 
    "Carrot 2", 
    "Date 3", 
    "Eggplant 4", 
    "Fig 5", 
    "Grape 6", 
    "Honeydew 7", 
    "Kiwi 8", 
    "Lemon 9", 
    "Macbook 10", 
    "Acer 11", 
    "Dell 12", 
    "Asus 13", 
    "Lenovo 14", 
    "HP 15", 
    "Samsung 16", 
    "Sony 17", 
    "LG 18", 
    "HTC 19"
};

int check;
int size;



// Funktion til at kapitalisere det første bogstav i en streng
string Capitalize(const std::string& input) {
    if (input.empty()) return input; // tom streng = retur som er

    std::string result = input; // kopiér input
    result[0] = std::toupper(static_cast<unsigned char>(result[0]));
    return result;
}
//Funktion til at tilføje items til rigtige kategori - ikke færdiggjort
 


// Hovedfunktionen
int main()
{
    /* Simple test of array of strings with names and user input

    cout << "Hello " << names[0] << names[1] << names[2] << endl;
    cout << "\nWhat is your name? Insert beneath\n";
    getline(cin, qname);
    cout << "Hello " << qname << "!" << endl;
    */

    cout << "\nHere is a list of items with their ID:\n";
    cout << "-------------------------------\n";

    int size = sizeof(vareID) / sizeof(vareID[0]);
    for (int i = 0; i < size; i++) {
        cout << vareID[i] << endl;
    }
    
    cout << "-------------------------------\n";
    cout << "\nPlease select an item by entering its ID (0-" << size - 1 << "): ";
    
    cin >> check;

    if (check < 0 || check > size - 1) {
        cout << "Invalid ID. Please run the program again and select a valid ID." << endl;
        return 1; // Exit the program with an error code
    }
    cout << "You have selected " << Capitalize(items[check]) << " which costs: $" << prices[check] << endl;
    cout << "Thank you for using our program!" << endl;

    return 0;
}