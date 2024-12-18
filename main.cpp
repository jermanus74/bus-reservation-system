#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Class representing a Bus
class Bus {
private:
    string busName;
    string from;
    string to;
    double fare;
    int totalSeats;
    vector<int> availableSeats;

public:
    Bus(string name, string from, string to, double fare, int seats)
        : busName(name), from(from), to(to), fare(fare), totalSeats(seats) {
        for (int i = 1; i <= seats; ++i) {
            availableSeats.push_back(i);
        }
    }

    string getBusName() const { return busName; }
    int getAvailableSeatsCount() const { return availableSeats.size(); }
    double getFare() const { return fare; }

    void displayBus() const {
        cout << "Bus Name: " << busName << ", From: " << from << ", To: " << to
             << ", Fare: $" << fixed << setprecision(2) << fare
             << ", Available Seats: " << getAvailableSeatsCount() << "\n";
    }

    void displayAvailableSeats() const {
        cout << "Available Seats: ";
        for (int seat : availableSeats) {
            cout << seat << " ";
        }
        cout << "\n";
    }

    bool bookSeats(const vector<int>& seatsToBook) {
        for (int seat : seatsToBook) {
            auto it = find(availableSeats.begin(), availableSeats.end(), seat);
            if (it == availableSeats.end()) {
                cout << "Seat " << seat << " is not available!\n";
                return false;
            }
        }
        for (int seat : seatsToBook) {
            auto it = find(availableSeats.begin(), availableSeats.end(), seat);
            availableSeats.erase(it);
        }
        return true;
    }

    void cancelSeats(const vector<int>& seatsToCancel) {
        for (int seat : seatsToCancel) {
            if (find(availableSeats.begin(), availableSeats.end(), seat) == availableSeats.end()) {
                availableSeats.push_back(seat);
            }
        }
        sort(availableSeats.begin(), availableSeats.end());
    }

    void editBusDetails(const string& newName, const string& newFrom, const string& newTo, double newFare, int newSeats) {
        busName = newName;
        from = newFrom;
        to = newTo;
        fare = newFare;
        totalSeats = newSeats;
        availableSeats.clear();
        for (int i = 1; i <= newSeats; ++i) {
            availableSeats.push_back(i);
        }
    }

    void saveToFile(ofstream &outFile) const {
        outFile << busName << " " << from << " " << to << " " << fare << " " << totalSeats << " ";
        for (int seat : availableSeats) {
            outFile << seat << " ";
        }
        outFile << "\n";
    }
};

class Passenger {
public:
    string name;
    int seatNumber;

    friend ostream& operator<<(ostream& os, const Passenger& passenger) {
        os << passenger.name << " " << passenger.seatNumber;
        return os;
    }

    friend istream& operator>>(istream& is, Passenger& passenger) {
        is >> passenger.name >> passenger.seatNumber;
        return is;
    }
};

// Function prototypes
void managerMenu(vector<Bus> &buses);
void passengerMenu(vector<Bus> &buses);
void addBus(vector<Bus> &buses);
void editBus(vector<Bus> &buses);
void displayBuses(const vector<Bus> &buses);
void bookSeat(vector<Bus> &buses);
void cancelBooking(vector<Bus> &buses);
void saveBusesToFile(const vector<Bus> &buses);
void loadBusesFromFile(vector<Bus> &buses);

const string fileName = "buses.txt";

int main() {
    vector<Bus> buses;
    loadBusesFromFile(buses);

    int choice;
    do {
        cout << "\n--- Welcome to the Bus Reservation System ---\n";
        cout << "1. Manager\n";
        cout << "2. Passenger\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                managerMenu(buses);
                break;
            case 2:
                passengerMenu(buses);
                break;
            case 3:
                saveBusesToFile(buses);
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}

void managerMenu(vector<Bus> &buses) {
    int choice;
    do {
        cout << "\n--- Manager Menu ---\n";
        cout << "1. Add Bus\n";
        cout << "2. Edit Bus\n";
        cout << "3. View All Buses\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBus(buses);
                break;
            case 2:
                editBus(buses);
                break;
            case 3:
                displayBuses(buses);
                break;
            case 4:
                cout << "Returning to main menu.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

void passengerMenu(vector<Bus> &buses) {
    int choice;
    do {
        cout << "\n--- Passenger Menu ---\n";
        cout << "1. Book Seat\n";
        cout << "2. Cancel Booking\n";
        cout << "3. View Available Buses\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookSeat(buses);
                break;
            case 2:
                cancelBooking(buses);
                break;
            case 3:
                displayBuses(buses);
                break;
            case 4:
                cout << "Returning to main menu.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

void addBus(vector<Bus> &buses) {
    string name, from, to;
    double fare;
    int seats;
    cout << "Enter Bus Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter From Location: ";
    getline(cin, from);
    cout << "Enter To Location: ";
    getline(cin, to);
    cout << "Enter Fare: ";
    cin >> fare;
    cout << "Enter Total Seats: ";
    cin >> seats;
    buses.emplace_back(name, from, to, fare, seats);
    cout << "Bus added successfully!\n";
}
//function to edit bus details
void editBus(vector<Bus> &buses) {
    string name;
    cout << "Enter the name of the bus to edit: ";
    cin.ignore();
    getline(cin, name);

    for (auto &bus : buses) {
        if (bus.getBusName() == name) {
            string newName, newFrom, newTo;
            double newFare;
            int newSeats;
            cout << "Enter New Name: ";
            getline(cin, newName);
            cout << "Enter New From Location: ";
            getline(cin, newFrom);
            cout << "Enter New To Location: ";
            getline(cin, newTo);
            cout << "Enter New Fare: ";
            cin >> newFare;
            cout << "Enter New Total Seats: ";
            cin >> newSeats;
            bus.editBusDetails(newName, newFrom, newTo, newFare, newSeats);
            cout << "Bus details updated successfully!\n";
            return;
        }
    }
    cout << "Bus not found!\n";
}

void displayBuses(const vector<Bus> &buses) {
    if (buses.empty()) {
        cout << "No buses available.\n";
        return;
    }

    cout << "\nAvailable Buses:\n";
    for (const auto &bus : buses) {
        bus.displayBus();
    }
}

void bookSeat(vector<Bus> &buses) {
    string name;
    int count;
    cout << "Enter the name of the bus to book: ";
    cin.ignore();
    getline(cin, name);

    for (auto &bus : buses) {
        if (bus.getBusName() == name) {
            bus.displayAvailableSeats();
            cout << "Enter number of seats to book: ";
            cin >> count;

            if (count > bus.getAvailableSeatsCount()) {
                cout << "Not enough seats available!\n";
                return;
            }

            vector<int> seatsToBook(count);
            cout << "Enter the seat numbers to book: ";
            for (int i = 0; i < count; ++i) {
                cin >> seatsToBook[i];
            }

            if (bus.bookSeats(seatsToBook)) {
                cout << "Total Fare: $" << bus.getFare() * count << "\n";
                cout << "Do you agree to pay? (yes/no): ";
                string confirmation;
                cin >> confirmation;
                if (confirmation == "yes") {
                    cout << "Booking successful!\n";
                    cout << "Receipt: \n";
                    cout << "Bus Name: " << bus.getBusName() << "\nSeats: ";
                    for (int seat : seatsToBook) {
                        cout << seat << " ";
                    }
                    cout << "\nTotal Fare: $" << bus.getFare() * count << "\n";
                } else {
                    cout << "Booking cancelled.\n";
                    // Revert booking
                    bus.cancelSeats(seatsToBook); 
                }
                return;
            } else {
                cout << "Booking failed!\n";
            }
            return;
        }
    }
    cout << "Bus not found!\n";
}

void cancelBooking(vector<Bus> &buses) {
    string name;
    int count;
    cout << "Enter the name of the bus to cancel booking: ";
    cin.ignore();
    getline(cin, name);

    for (auto &bus : buses) {
        if (bus.getBusName() == name) {
            cout << "Enter number of seats to cancel: ";
            cin >> count;

            vector<int> seatsToCancel(count);
            cout << "Enter the seat numbers to cancel: ";
            for (int i = 0; i < count; ++i) {
                cin >> seatsToCancel[i];
            }

            bus.cancelSeats(seatsToCancel);
            cout << "Cancellation successful!\n";
            return;
        }
    }
    cout << "Bus not found!\n";
}

// void saveBusesToFile(const vector<Bus> &buses) {
//     ofstream outFile(fileName);
//     if (!outFile) {
//         cout << "Error saving to file!\n";
//         return;
//     }

//     for (const auto &bus : buses) {
//         bus.saveToFile(outFile);
//     }
//     outFile.close();
//     cout << "Bus data saved successfully!\n";
// }

void loadBusesFromFile(vector<Bus> &buses) {
     ifstream inFile(fileName);
    if (!inFile) {
        return;    }

    string name, from, to;
   double fare;
     int totalSeats;
while (inFile >> name >> from >> to >> fare >> totalSeats) {
       Bus bus(name, from, to, fare, totalSeats);/         int seat;        while (inFile >> seat) {
            End of seat list
            if (seat == -1) break;              bus.cancelSeats({seat});        }
        buses.push_back(bus);
    }
    inFile.close();
 }
