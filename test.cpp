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

    cout << greeting << endl; // Udskriver velkomstbeskeden
    cout << "What is your name? "; // Spørger brugeren om deres navn
    getline(cin, name); // Læser hele linjen ind, inklusiv mellemrum og tilføjer den til variablen 'name'
    
    cout << "Hello " << name << "!" << endl; // Hilser brugeren velkommen
    
    cout << farewell << names << endl; // Udskriver afskedsbeskeden med listen af navne

    return 0; // Returnerer 0 for at indikere, at programmet er afsluttet korrekt
}
