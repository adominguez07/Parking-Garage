#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

class Vehicle {
protected:
    std::string licensePlate;
    std::string ownerName;

public:
    // Stores the shared vehicle details used by derived classes.
    Vehicle(const std::string& plate, const std::string& owner)
        : licensePlate(plate), ownerName(owner) {}

    // Enables safe cleanup through a base-class pointer.
    virtual ~Vehicle() = default;

    // Returns the vehicle category for display purposes.
    virtual std::string getType() const = 0;

    // Returns the license plate identifier.
    std::string getLicensePlate() const {
        return licensePlate;
    }

    // Returns the vehicle owner's name.
    std::string getOwnerName() const {
        return ownerName;
    }

    // Builds a readable summary of the vehicle.
    virtual std::string getDisplayText() const {
        return getType() + " | Plate: " + licensePlate + " | Owner: " + ownerName;
    }
};

class Car : public Vehicle {
private:
    std::string color;

public:
    // Creates a car with its plate, owner, and color information.
    Car(const std::string& plate, const std::string& owner, const std::string& carColor)
        : Vehicle(plate, owner), color(carColor) {}

    // Identifies this derived class as a car.
    std::string getType() const override {
        return "Car";
    }

    // Returns the car color.
    std::string getColor() const {
        return color;
    }

    // Extends the base vehicle summary with the color attribute.
    std::string getDisplayText() const override {
        return Vehicle::getDisplayText() + " | Color: " + color;
    }
};

#endif
