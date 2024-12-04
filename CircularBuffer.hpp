/*
 * CircularBuffer
 * Author: Arkadiusz Szlanta
 * Date: 04 Dec 2024
 *
 * License:
 * This source code is provided for hobbyist and private use only.
 * Any commercial or industrial use, including distribution, reproduction, or
 * incorporation in commercial or industrial products or services is prohibited.
 * Use at your own risk. The author(s) hold no responsibility for any damages
 * or losses resulting from the use of this software.
 *
 */
#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <cstdint>
#include <atomic>

class Mutex
{
    public:
        Mutex();
        void lock();
        void unlock();

    private:
        std::atomic_flag flag;
};

class CircularBuffer
{
    public:
        explicit CircularBuffer(uint32_t buffer_size = 256u);
        CircularBuffer(const CircularBuffer &t);
        ~CircularBuffer();

        bool isFull() const;
        bool isEmpty() const;
        bool put(const uint8_t *data, uint32_t size);
        bool get(uint8_t *data, uint32_t size);

    private:
        uint8_t *mBuffer;
        uint32_t mHead;
        uint32_t mTail;
        uint32_t mCurrentSize;
        uint32_t mBufferSize;
        Mutex    mMutex;
};

#endif // CIRCULARBUFFER_HPP
