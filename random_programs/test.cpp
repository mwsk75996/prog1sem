#include <iostream>
#include <string>
using namespace std;

int main() {
    string name; // Virable der gemmer brugerns navn senere
    string greeting = "Hello, World!\n"; // Velkomstbesked
    string farewell = "Goodbye "; // Afskedsbesked til listen af navne

    string name1 = "Sebastian, "; // Navn 1
    string name2 = "Oliver, "; // Navn 2
    string name3 = "Ruben"; // Navn 3
    string names = name1 + name2 + name3 + "."; // Samlet liste af navne

    double pi = 3.14159; // Variabel der gemmer værdien af pi
    double tyve = 20; 

    cout << greeting << endl; // Udskriver velkomstbeskeden
    cout << "What is your name? Insert beneath\n"; // Spørger brugeren om deres navn
    getline(cin, name); // Læser hele linjen ind, inklusiv mellemrum og tilføjer den til variablen 'name'
    
    cout << "Hello " << name << "!" << endl; // Hilser brugeren velkommen
    
    cout << farewell << names << endl; // Udskriver afskedsbeskeden med listen af navne

    cout << "The value of pi is approximately " << pi << "." << endl; // Udskriver værdien af pi
    cout << "The value of 20 divided by 7 is approximately " << tyve / 7 << "." << endl; // Udskriver resultatet af 20 divideret med 7

    return 0; // Returnerer 0 for at indikere, at programmet er afsluttet korrekt

    /*
    C/C++ Linter til at finde syntaksfejl.
    C/C++ Linter til at formatere koden.

    Code Runner til finde miljøvariabler.
    */
}
