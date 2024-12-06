# Implementation
The implementation consists of a synchronized circular buffer designed for high-speed data transfer between tasks in a FreeRTOS system. The circular buffer stores data in a fixed-size array and uses a simple locking mechanism to ensure safe access in a multi-threaded environment. The implementation includes two main classes: CircularBuffer and Mutex.

# Class `Mutex`

#### Member Functions:
- **Constructor:** `Mutex()`
  - Initializes the `flag` variable as `ATOMIC_FLAG_INIT`.
- **Method `lock()`:**
  - Locks the mutex by setting the `flag`. It waits in a loop until it successfully sets the flag.
- **Method `unlock()`:**
  - Unlocks the mutex by clearing the `flag`.

# Class `CircularBuffer`

#### Member Functions:
- **Constructor:** `CircularBuffer(uint32_t buffer_size = 256u)`
  - Initializes all member variables and allocates memory for the buffer of the given size.
- **Copy Constructor:** `CircularBuffer(const CircularBuffer &old)`
  - Copies data from another circular buffer.
- **Destructor:** `~CircularBuffer()`
  - Frees the memory allocated for the buffer.
- **Method `isFull()`:**
  - Checks if the buffer is full.
- **Method `isEmpty()`:**
  - Checks if the buffer is empty.
- **Method `put(const uint8_t *data, uint32_t size)`:**
  - Inserts data into the buffer. If the insertion would exceed the buffer's size, the method returns `false`.
- **Method `get(uint8_t *data, uint32_t size)`:**
  - Retrieves data from the buffer. If the retrieval would exceed the current content of the buffer, the method returns `false`.

# Algorithm of Circular Buffer Operation

1. *Inserting Data (`put`):*
   - Checks if adding the new data exceeds the buffer's size.
   - If the addition is possible, the data is copied into the buffer:
     - If the data fits in a single copy operation, it is copied directly.
     - If the data exceeds the end of the buffer, the first part is copied to the end of the buffer, and the remaining part to the beginning.
   - Updates the head (`mHead`) and the current size of the buffer (`mCurrentSize`).

2. *Retrieving Data (`get`):*
   - Checks if it is possible to retrieve the requested amount of data.
   - If the retrieval is possible, the data is copied from the buffer:
     - If the data can be retrieved in a single copy operation, it is copied directly.
     - If the data exceeds the end of the buffer, the first part is copied from the end of the buffer, and the remaining part from the beginning.
   - Updates the tail (`mTail`) and the current size of the buffer (`mCurrentSize`).

3. *Synchronization (`Mutex`):*
   - The `put` and `get` methods are secured by a mutex (`mMutex`) to ensure safe operation in multithreaded conditions.

# How does it work and FreeRTOS use case:
![asdasd](https://github.com/user-attachments/assets/1de050fd-37db-492f-9c2c-ff30c9683614)

# Function flow diagram and sequence diagram
![codetoflow (6)](https://github.com/user-attachments/assets/e0602663-1892-4b4d-891a-0d7518ecdbbb)
![codetoflow (7)](https://github.com/user-attachments/assets/06338495-7de7-4dca-9bd0-316a047e4517)

# Class diagram
![codetoflow (9)](https://github.com/user-attachments/assets/709e7ff5-01d6-4b49-ad46-1d95f238bfde)
