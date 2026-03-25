#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <cstddef>
#include <stdexcept>

// Stores queue data in a circularly linked list so enqueue and dequeue stay O(1).
template <typename T>
class CircularQueue {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* rear;
    std::size_t itemCount;

public:
    // Creates an empty circular queue.
    CircularQueue() : rear(nullptr), itemCount(0) {}

    // Copies another queue while preserving item order.
    CircularQueue(const CircularQueue& other) : rear(nullptr), itemCount(0) {
        if (other.isEmpty()) {
            return;
        }

        Node* current = other.rear->next;
        do {
            enqueue(current->data);
            current = current->next;
        } while (current != other.rear->next);
    }

    // Replaces this queue's contents with a copy of another queue.
    CircularQueue& operator=(const CircularQueue& other) {
        if (this == &other) {
            return *this;
        }

        clear();

        if (!other.isEmpty()) {
            Node* current = other.rear->next;
            do {
                enqueue(current->data);
                current = current->next;
            } while (current != other.rear->next);
        }

        return *this;
    }

    // Releases all dynamically allocated queue nodes.
    ~CircularQueue() {
        clear();
    }

    // Adds a new item to the back of the queue.
    void enqueue(const T& value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            newNode->next = newNode;
            rear = newNode;
        } else {
            newNode->next = rear->next;
            rear->next = newNode;
            rear = newNode;
        }

        ++itemCount;
    }

    // Removes and returns the item at the front of the queue.
    T dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty.");
        }

        Node* front = rear->next;
        T removedValue = front->data;

        if (front == rear) {
            rear = nullptr;
        } else {
            rear->next = front->next;
        }

        delete front;
        --itemCount;
        return removedValue;
    }

    // Returns the front item without removing it.
    const T& front() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty.");
        }

        return rear->next->data;
    }

    // Returns true when the queue contains no items.
    bool isEmpty() const {
        return rear == nullptr;
    }

    // Returns the number of items currently stored.
    std::size_t size() const {
        return itemCount;
    }

    // Deletes all nodes in the queue.
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};

#endif
