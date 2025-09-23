#include <iostream>
#include <string>
using namespace std;

int i; // loop variabel

// 3. Tænk på nogle af de varer du skal have i en shop. Hvordan vil du beskrive varer i en struct
/*
Vil have følgende varer:
 - Æble
 - Banan
 - Gulerod
*/

// 4. Lav en struct til varer. Definér den før int main ...

struct Product {
    string name;
    double price;
    int id;
    int quantity;
};

string basket[100]; // array til at holde styr på varer i kurven
int basketCount = 0; // tæller antal varer i kurven

// 5. Brug denne struct til at oprette én vare.
Product products[] = {
    {"Æble", 5, 1, 100},
    {"Banan", 6, 2, 150},
    {"Gulerod", 2, 3, 200}
};

int maxProducts = sizeof(products) / sizeof(products[0]);

int main () {
    int choice;  
    cout << "How can I help you?\n 1) View products \n 2) View basket \n 3) About us" << endl;
    cin >> choice;
    cout << " " << endl; // blank linje
    
// 1. Lav en condition der tjekker hvilken valgmulighed brugeren har valgt.

// Hvis valget ikke er 1-maxProducts får man en fejl.
// maxProducts er defineret som 3 under vores Products struct array.

    if (choice < 1 || choice > maxProducts) {
        cout << "Invalid choice. Please select a number between 1 and 3." << endl;
        return 1; // Slukker programmet med en fejl kode
    }

    
// Viser hvilket valg brugeren har lavet
    cout << "You chose " << choice << endl; 

// 2. Baseret på det de har valgt, skal du bruge `cout` til at fortælle brugeren hvad de har valgt.
    
    if (choice == 1) {
        // Viser alle produkter i shoppen
        cout << "You chose to view products." << endl;
        cout << "-----------------------------" << endl;
        for (i = 0; i < maxProducts; i++) {
            cout << "ID: " << products[i].id 
            << ", Navn: " << products[i].name 
            << ", Pris: " << products[i].price << ",- DKK"
            << ", Antal på lager: " << products[i].quantity << endl;
        }
        cout << "-----------------------------" << endl;
        cout << "Please enter the ID of the product you want to add to your basket: ";
        basket[basketCount] = products[choice - 1].name; // Tilføjer valgt produkt til kurven
        basketCount++;
        cout << "Product added to your basket." << endl;
        cout << "Your basket contains: ";
        for (i = 0; i < basketCount; i++) {
            cout << basket[i] << " ";
        }


    }
    else if (choice == 2) {
        cout << "You chose to view your basket." << endl;
        
    }
    // Om os sektion
    else if (choice == 3) {
        cout << "You chose to learn about us." << endl;
        cout << "We are a small shop selling fruits and vegetables." << endl;
        cout << "We have been in business for 10 years." << endl;
        cout << "We are located in Copenhagen, Denmark." << endl;
        cout << "Our mission is to provide fresh and healthy food to our customers." << endl;
        cout << "Thank you for choosing us!" << endl;
        
    }
    
    return 0;
}