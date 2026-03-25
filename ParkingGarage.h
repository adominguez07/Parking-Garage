#ifndef PARKING_GARAGE_H
#define PARKING_GARAGE_H

#include "CircularQueue.h"
#include "Vehicle.h"

#include <sstream>
#include <string>
#include <vector>

class ParkingGarage {
private:
    struct ParkingRecord {
        Car car;
        int spotNumber;

        // Stores a parked car together with its assigned spot number.
        ParkingRecord(const Car& parkedCar, int assignedSpot)
            : car(parkedCar), spotNumber(assignedSpot) {}
    };

    int capacity;
    std::vector<ParkingRecord> activeSpots;
    CircularQueue<Car> waitingQueue;
    int carsServed;

    // Returns the next open spot number in ascending order.
    int getNextOpenSpot() const {
        for (int spot = 1; spot <= capacity; ++spot) {
            bool occupied = false;

            for (const ParkingRecord& record : activeSpots) {
                if (record.spotNumber == spot) {
                    occupied = true;
                    break;
                }
            }

            if (!occupied) {
                return spot;
            }
        }

        return -1;
    }

    // Moves the next waiting car into the garage if space becomes available.
    std::string admitNextWaitingCar() {
        if (waitingQueue.isEmpty() || static_cast<int>(activeSpots.size()) >= capacity) {
            return "";
        }

        Car nextCar = waitingQueue.dequeue();
        int spotNumber = getNextOpenSpot();
        activeSpots.emplace_back(nextCar, spotNumber);
        ++carsServed;

        std::ostringstream output;
        output << "Spot " << spotNumber << " opened, so " << nextCar.getOwnerName()
               << " was moved from the waiting queue into the garage.";
        return output.str();
    }

public:
    // Sets the total number of parking spots available in the garage.
    explicit ParkingGarage(int totalSpots)
        : capacity(totalSpots), carsServed(0) {}

    // Processes a new car arrival and either parks it or places it in the queue.
    std::string arriveCar(const Car& arrivingCar) {
        std::ostringstream output;

        if (static_cast<int>(activeSpots.size()) < capacity) {
            int spotNumber = getNextOpenSpot();
            activeSpots.emplace_back(arrivingCar, spotNumber);
            ++carsServed;
            output << arrivingCar.getOwnerName() << " parked immediately in spot " << spotNumber << ".";
        } else {
            waitingQueue.enqueue(arrivingCar);
            output << "Garage is full. " << arrivingCar.getOwnerName()
                   << " joined the waiting queue in position " << waitingQueue.size() << ".";
        }

        return output.str();
    }

    // Removes a parked car by license plate and then fills the new opening from the queue.
    std::string departCar(const std::string& licensePlate) {
        for (std::size_t index = 0; index < activeSpots.size(); ++index) {
            if (activeSpots[index].car.getLicensePlate() == licensePlate) {
                ParkingRecord departingRecord = activeSpots[index];
                activeSpots.erase(activeSpots.begin() + static_cast<long long>(index));

                std::ostringstream output;
                output << departingRecord.car.getOwnerName() << " left spot "
                       << departingRecord.spotNumber << ".";

                std::string queuedAdmissionMessage = admitNextWaitingCar();
                if (!queuedAdmissionMessage.empty()) {
                    output << '\n' << queuedAdmissionMessage;
                }

                return output.str();
            }
        }

        return "No parked car was found with that license plate.";
    }

    // Returns a human-readable snapshot of parked cars and queued cars.
    std::string getStatusReport() const {
        std::ostringstream output;

        output << "Garage capacity: " << capacity << '\n';
        output << "Occupied spots: " << activeSpots.size() << '\n';
        output << "Cars waiting in queue: " << waitingQueue.size() << '\n';
        output << "Cars served so far: " << carsServed << "\n\n";

        output << "Parked Cars:\n";
        if (activeSpots.empty()) {
            output << "  None\n";
        } else {
            for (const ParkingRecord& record : activeSpots) {
                output << "  Spot " << record.spotNumber << ": "
                       << record.car.getDisplayText() << '\n';
            }
        }

        output << "\nNext Car In Queue:\n";
        if (waitingQueue.isEmpty()) {
            output << "  None\n";
        } else {
            output << "  " << waitingQueue.front().getDisplayText() << '\n';
        }

        return output.str();
    }
};

#endif
