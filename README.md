# Circular-Buffer

The implementation consists of a synchronized circular buffer designed for high-speed data transfer between tasks in a FreeRTOS system. The circular buffer stores data in a fixed-size array and uses a simple locking mechanism to ensure safe access in a multi-threaded environment. The implementation includes two main classes: CircularBuffer and Mutex.

Class CircularBuffer: Manages the circular buffer, allowing data to be added and retrieved. The buffer synchronizes access to its data using the Mutex class.

Constructor (CircularBuffer(uint32_t buffer_size)): Initializes the buffer with the specified size, allocating memory for the data storage.

Destructor (~CircularBuffer()): Deallocates the memory used by the buffer.

isFull() const: Checks if the buffer is full, returning true if the buffer cannot accept more data.

isEmpty() const: Checks if the buffer is empty, returning true if there is no data to retrieve.

put(uint8_t data): Adds data to the buffer if it is not full. This function locks the buffer during the operation to ensure thread safety.

get(uint8_t &data): Retrieves data from the buffer if it is not empty. This function also locks the buffer during the operation to ensure thread safety.

Class Mutex: Implements a simple locking mechanism using an atomic flag to ensure synchronized access to the circular buffer.

Constructor (Mutex()): Initializes the atomic flag used for locking.

lock(): Locks the mutex, blocking if necessary until the lock is acquired.

unlock(): Unlocks the mutex, allowing other threads to acquire the lock.

This structure ensures that data can be safely transferred between producer and consumer tasks, avoiding data corruption or race conditions in a multi-threaded environment. The simple locking mechanism reduces overhead and ensures that the buffer operations are as efficient as possible, which is critical for systems requiring high-speed data transfer.

# How does it work and FreeRTOS use case:
![asdasd](https://github.com/user-attachments/assets/1de050fd-37db-492f-9c2c-ff30c9683614)
