#include <iostream>
#include <string>
using namespace std;

struct Kunde{
    string navn;
    int alder;
    string email;
    string gadenavn;
    int husnummer;
    string by;
    int postnummer;
    double balance;
};

int main(){
    Kunde klaus;
    klaus.navn = "Sebastian Reimers";
    klaus.alder = 26;
    klaus.email = "sebr1999@gmail.com";
    klaus.gadenavn = "Søndergade";
    klaus.husnummer = 12;
    klaus.by = "Aarhus";
    klaus.postnummer = 8000;
    klaus.balance = 10500.50;

    cout << klaus.navn << " " << klaus.alder << endl;
    cout << klaus.email << endl;
    cout << klaus.gadenavn << " " << klaus.husnummer << endl;
    cout << klaus.postnummer << " " << klaus.by << endl;
    cout << "Balance: $" << klaus.balance << endl;

    return 0;
}