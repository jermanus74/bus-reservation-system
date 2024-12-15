#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Base class for Bus
class Bus {
protected:
    string busName;
    string plateNo;

public:
    Bus(string name, string plate) : busName(name), plateNo(plate) {}

    // Getter methods
    string getBusName() const {
        return busName;
    }

    string getPlateNo() const {
        return plateNo;
    }

    virtual float calculateFare(float baseFare) const {
        return baseFare;  // Basic fare calculation for generic bus
    }

    virtual ~Bus() {}
};

// Derived class for LuxuryBus
class LuxuryBus : public Bus {
public:
    LuxuryBus(string name, string plate) : Bus(name, plate) {}

    // Overriding the calculateFare function to apply extra luxury charge
    float calculateFare(float baseFare) const override {
        return baseFare + 20.0f;  // Adding extra charge for luxury bus
    }
};

// Derived class for RegularBus
class RegularBus : public Bus {
public:
    RegularBus(string name, string plate) : Bus(name, plate) {}

    // Overriding the calculateFare function to apply regular fare
    float calculateFare(float baseFare) const override {
        return baseFare;  // No extra charge for regular bus
    }
};

// Class to store reservation details (Encapsulation)
class BusReservation {
private:
    string passengerName;
    string fromPlace;
    string destination;
    int seatNo;
    Bus* bus;   // Bus is a pointer to the base class (polymorphism)
    float fare;
    float totalFare;

public:
    // Constructor
    BusReservation(string pName, string from, string dest, int seat, Bus* b, float baseFare)
            : passengerName(pName), fromPlace(from), destination(dest), seatNo(seat), bus(b), fare(baseFare) {
        totalFare = bus->calculateFare(fare);
    }

    // Display reservation details
    void displayDetails() const {
        cout << "\nPayment Details:\n";
        cout << "Passenger Name: " << passengerName << endl;
        cout << "From: " << fromPlace << " To: " << destination << endl;
        cout << "Bus Name: " << bus->getBusName() << endl;
        cout << "Plate Number: " << bus->getPlateNo() << endl;
        cout << "Seat Number: " << seatNo << endl;
        cout << "Fare: " << fixed << setprecision(2) << fare << endl;
        cout << "Total Fare: " << fixed << setprecision(2) << totalFare << endl;
    }

    // Save reservation details to file
    void saveToFile() const {
        ofstream outFile("bus.txt", ios::app);
        if (!outFile) {
            cerr << "Error opening file!" << endl;
            return;
        }

        outFile << "Passenger Name: " << passengerName << endl;
        outFile << "From: " << fromPlace << " To: " << destination << endl;
        outFile << "Bus Name: " << bus->getBusName() << " Plate No: " << bus->getPlateNo() << endl;
        outFile << "Seat No: " << seatNo << endl;
        outFile << "Fare: " << fixed << setprecision(2) << fare << endl;
        outFile << "Total Fare: " << fixed << setprecision(2) << totalFare << endl;
        outFile << "-------------------------------" << endl;

        outFile.close();
    }
};

// Function to make a reservation
void makeReservation() {
    string pName, from, dest, busName, plate;
    int seat;
    float baseFare;

    cout << "Enter passenger name: ";
    getline(cin, pName);

    cout << "Enter from place: ";
    getline(cin, from);

    cout << "Enter destination place: ";
    getline(cin, dest);

    cout << "Enter seat number: ";
    cin >> seat;
    cin.ignore(); // To clear the newline left in the input buffer

    cout << "Enter bus name: ";
    getline(cin, busName);

    cout << "Enter bus plate number: ";
    getline(cin, plate);

    cout << "Enter base fare: ";
    cin >> baseFare;

    Bus* bus;
    char busType;

    // Ask for bus type (Luxury or Regular)
    cout << "Enter bus type (L for Luxury, R for Regular): ";
    cin >> busType;

    if (busType == 'L' || busType == 'l') {
        bus = new LuxuryBus(busName, plate);
    } else {
        bus = new RegularBus(busName, plate);
    }

    // Create the reservation object
    BusReservation reservation(pName, from, dest, seat, bus, baseFare);

    // Display reservation details
    reservation.displayDetails();

    // Save reservation to file
    reservation.saveToFile();

    // Clean up dynamically allocated memory
    delete bus;
}

int main() {
    int choice;

    cout << "Welcome to Bus Seat Reservation System\n";
    while (true) {
        cout << "\n1. Make Reservation\n2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character

        switch (choice) {
            case 1:
                makeReservation();
                break;
            case 2:
                cout << "Exiting system. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
