#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
#include <string>
#include <cstdlib>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    set<Goat> goat_trip;
    int menu_choice = 0;

    //main application loop
    do {
        menu_choice = main_menu();
        
        switch (menu_choice) {
            case 1:
                add_goat(goat_trip, names, colors);
                break;
            case 2:
                delete_goat(goat_trip);
                break;
            case 3:
                display_trip(goat_trip);
                break;
            case 4:
                cout << "Thanks for using Goat Manager 3001." << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
        
    } while (menu_choice != 4);

    return 0;




    return 0;
}
int main_menu() {
    int choice = 0;
    cout << "*** GOAT MANAGER 3001 ***" << endl; 
    cout << "[1] Add a goat" << endl; 
    cout << "[2] Delete a goat" << endl; 
    cout << "[3] List goats" << endl; 
    cout << "[4] Quit" << endl; 
    cout << "Choice --> ";

    cin >> choice;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid input. Please enter a number." << endl;
        cout << "Choice --> ";
        cin >> choice;
    }
    return choice;
}


void add_goat(set<Goat> &trip, string names[], string colors[]){
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % MAX_AGE; // random age from 0 to 19

    // create and add the goat
    Goat newGoat(name, age, color);
    trip.insert(newGoat);
    
    
    cout << "\n" << name << " the " << color << " goat (age " << age << ") has joined the trip!" << endl;
}

void display_trip(set<Goat> trip) {
    if (trip.empty()) {
        cout << "The trip is empty. No goats yet!" << endl;
        return;
    }
    int i= 1;
    cout << "CURRENT GOAT TRIP" << endl;
    //loop to iterate
    for (const auto& goat : trip) {
        cout << "[" << i << "] " << left << setw(5) << goat.get_name() 
             << " (" << goat.get_age() 
             << ", " << goat.get_color() << ")" << endl;
        i++;
    }
    cout << "-------------------------" << endl;
}

int select_goat(set<Goat> trip) {
    int i = 1; // start at 1 for the menu
    cout << "Select a goat" << endl;
    
    // iterator for a list
    for (auto it = trip.begin(); it != trip.end(); ++it) {
        cout << "[" << i << "] " << left << setw(5) << it->get_name()
             << " (" << it->get_age() 
             << ", " << it->get_color() << ")" << endl;
        i++;
    }
    int choice = 0;
    cout << "Choice --> ";
    cin >> choice;
    
    // validate input
    while (cin.fail() || choice < 1 || choice > trip.size()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid choice. Enter a number from 1 to " << trip.size() << "." << endl;
        cout << "Choice --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "There are no goats to delete. " << endl;
        return;
    }

    // Get the user's 1-based choice
    int choice = select_goat(trip);
    
    // Get an iterator to the start
    auto it = trip.begin();
    
    for (int i  = 1; i<choice; i++){
        ++it;
    }
    
    cout << "\n" << it->get_name() << " has been removed from the trip." << endl;
    
    // erase the goat at the iterator's position
    trip.erase(it);
}