# Parking Garage System

## Project Name
Parking Garage System

## Program Description
This project simulates a small parking garage with limited parking spots. When the garage is full, arriving cars are placed into a waiting queue. When a parked car leaves, the next car in the queue is moved into the open spot.

The main data structure is a **queue implemented using a templated circularly linked list**. The program also demonstrates object-oriented programming with multiple classes and inheritance through the `Vehicle` base class and the `Car` derived class.

## Files Included
- `main.cpp`
- `CircularQueue.h`
- `Vehicle.h`
- `ParkingGarage.h`

## Instructions to Run the Program
1. Open a terminal in the project folder.
2. Compile the program with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o parking_garage
```

3. Run the executable:

```bash
./parking_garage
```

On Windows with MinGW, the executable may be named `parking_garage.exe`.

## Instructions for Using the Program
1. Choose `1` to add a new arriving car.
2. Choose `2` to remove a parked car by license plate.
3. Choose `3` to display the current garage status.
4. Choose `4` to run a built-in sample simulation.
5. Choose `5` to exit the program.

## Implementation Explanation
- `CircularQueue.h` contains a templated queue built with a circularly linked list.
- `Vehicle.h` defines the abstract `Vehicle` base class and the derived `Car` class, which demonstrates inheritance.
- `ParkingGarage.h` manages parking spots, queued cars, and garage operations.
- `main.cpp` provides a menu-driven interface so users can interact with the system.
