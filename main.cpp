#include "ParkingGarage.h"

#include <iostream>
#include <limits>
#include <string>

// Reads a full line of text after a prompt.
std::string readText(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Reads an integer menu choice safely from the console.
int readMenuChoice() {
    int choice;

    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Enter a valid number: ";
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

// Prints the interactive program menu.
void printMenu() {
    std::cout << "\n==== Parking Garage System ====\n";
    std::cout << "1. Add arriving car\n";
    std::cout << "2. Remove parked car\n";
    std::cout << "3. View garage status\n";
    std::cout << "4. Run sample simulation\n";
    std::cout << "5. Exit\n";
    std::cout << "Choose an option: ";
}

// Demonstrates arrivals, queueing, and departures automatically.
void runSampleSimulation(ParkingGarage& garage) {
    std::cout << "\nRunning sample simulation...\n";

    std::cout << garage.arriveCar(Car("AAA-101", "Mia", "Blue")) << '\n';
    std::cout << garage.arriveCar(Car("BBB-202", "Ethan", "Red")) << '\n';
    std::cout << garage.arriveCar(Car("CCC-303", "Noah", "Black")) << '\n';
    std::cout << garage.arriveCar(Car("DDD-404", "Ava", "White")) << '\n';
    std::cout << garage.arriveCar(Car("EEE-505", "Liam", "Silver")) << '\n';

    std::cout << '\n' << garage.getStatusReport() << '\n';

    std::cout << garage.departCar("BBB-202") << '\n';
    std::cout << garage.departCar("AAA-101") << '\n';

    std::cout << '\n' << garage.getStatusReport() << '\n';
}

// Starts the interactive parking garage program.
int main() {
    ParkingGarage garage(3);
    bool keepRunning = true;

    std::cout << "Parking Garage System\n";
    std::cout << "This program uses a queue implemented with a templated circular linked list.\n";

    while (keepRunning) {
        printMenu();
        int choice = readMenuChoice();

        switch (choice) {
            case 1: {
                std::string plate = readText("Enter license plate: ");
                std::string owner = readText("Enter owner name: ");
                std::string color = readText("Enter car color: ");

                Car arrivingCar(plate, owner, color);
                std::cout << garage.arriveCar(arrivingCar) << '\n';
                break;
            }
            case 2: {
                std::string plate = readText("Enter the license plate of the departing car: ");
                std::cout << garage.departCar(plate) << '\n';
                break;
            }
            case 3:
                std::cout << '\n' << garage.getStatusReport() << '\n';
                break;
            case 4:
                runSampleSimulation(garage);
                break;
            case 5:
                keepRunning = false;
                std::cout << "Program closed.\n";
                break;
            default:
                std::cout << "Choose a menu option from 1 to 5.\n";
                break;
        }
    }

    return 0;
}
