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

// Struktur til at holde brugerdata
struct Bruger {
    string navn;
    string email;
    string password;
    int alder;
    int rabatniveau; // 0-4
};

// Struktur til at holde varedata
struct Vare {
    string kategori;
    int vareID;
    string vareNavn;
    double pris;
};

// Liste over varer i butikken
Vare varer[] = {
    {"Fruits", 0, "Apple", 0.99},
    {"Fruits", 1, "Banana", 0.59},
    {"Vegetables", 2, "Carrot", 0.79},
    {"Fruits", 3, "Date", 1.29},
    {"Vegetables", 4, "Eggplant", 1.49},
    {"Fruits", 5, "Fig", 2.99},
    {"Fruits", 6, "Grape", 2.49},
    {"Fruits", 7, "Honeydew", 3.99},
    {"Fruits", 8, "Kiwi", 0.89},
    {"Fruits", 9, "Lemon", 0.69},
    {"Electronics", 10, "Macbook", 999.99},
    {"Electronics", 11, "Acer", 799.99},
    {"Electronics", 12, "Dell", 699.99},
    {"Electronics", 13, "Asus", 899.99},
    {"Electronics", 14, "Lenovo", 749.99},
    {"Electronics", 15, "HP", 649.99},
    {"Electronics", 16, "Samsung", 599.99},
    {"Electronics", 17, "Sony", 549.99},
    {"Electronics", 18, "LG", 499.99},
    {"Electronics", 19, "HTC", 399.99}
};

// Rabatniveauer i procent
array<double, 5> rabatniveauer = {0.0, 0.05, 0.10, 0.15, 0.20};

// Globale variabler
bool foundUser = false; // Global variabel til at spore om bruger er registreret
string basket[100];
int basketCount = 0;

// Hovedprogram
int main() 
{
    // Opret bruger eller brug eksisterende
    Bruger bruger;
    if (!foundUser){
        cout << "Please register to continue." << endl;
        cout << "Enter your name: ";
        cin >> bruger.navn;
        cout << "Enter your age: ";
        cin >> bruger.alder;
        cout << "Enter your email: ";
        cin >> bruger.email;
        cout << "Enter your password: ";
        cin >> bruger.password;
        foundUser = true;
        bruger.rabatniveau = 0; // Start uden rabat
        cout << "Registration complete!" << endl;
    }
}
