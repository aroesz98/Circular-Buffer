/*
 * CircularmBuffer
 * Author: Arkadiusz Szlanta
 * Date: 04 Dec 2024
 *
 * License:
 * Use at your own risk. The author(s) hold no responsibility for any damages
 * or losses resulting from the use of this software.
 *
 */
#include <CircularBuffer.hpp>
#include <cstring>

Mutex::Mutex() : flag(ATOMIC_FLAG_INIT)
{
}

void Mutex::lock()
{
    while (flag.test_and_set(std::memory_order_acquire));
}

void Mutex::unlock()
{
    flag.clear(std::memory_order_release);
}

CircularBuffer::CircularBuffer(uint32_t mBuffer_size)
    : mHead(0u), mTail(0u), mCurrentSize(0u), mBufferSize(mBuffer_size)
{
    mBuffer = new uint8_t[mBufferSize];
}

CircularBuffer::CircularBuffer(const CircularBuffer &old)
{
    mHead = old.mHead;
    mTail = old.mTail;
    mCurrentSize = old.mCurrentSize;
    mBufferSize = old.mBufferSize;
    mBuffer = new uint8_t[mBufferSize];
    memcpy(&mBuffer[0], &(old.mBuffer[0]), mBufferSize);
}

CircularBuffer::~CircularBuffer()
{
    delete[] mBuffer;
}

bool CircularBuffer::isFull() const
{
    return mCurrentSize == mBufferSize;
}

bool CircularBuffer::isEmpty() const
{
    return mCurrentSize == 0u;
}

bool CircularBuffer::put(const uint8_t *data, uint32_t size)
{
    mMutex.lock();

    if (mCurrentSize + size > mBufferSize)
    {
        mMutex.unlock();
        return false;
    }

    if (mHead + size <= mBufferSize)
    {
        memcpy(&mBuffer[mHead], data, size);
    }
    else
    {
        uint32_t firstPartSize = mBufferSize - mHead;

        memcpy(&mBuffer[mHead], data, firstPartSize);
        memcpy(mBuffer, &data[firstPartSize], size - firstPartSize);
    }

    mHead = (mHead + size) % mBufferSize;
    mCurrentSize += size;

    mMutex.unlock();

    return true;
}

bool CircularBuffer::get(uint8_t *data, uint32_t size)
{
    mMutex.lock();

    if (mCurrentSize < size)
    {
        mMutex.unlock();
        return false;
    }

    if (mTail + size <= mBufferSize)
    {
        memcpy(data, &mBuffer[mTail], size);
    }
    else
    {
        uint32_t firstPartSize = mBufferSize - mTail;

        memcpy(data, &mBuffer[mTail], firstPartSize);
        memcpy(&data[firstPartSize], mBuffer, size - firstPartSize);
    }

    mTail = (mTail + size) % mBufferSize;
    mCurrentSize -= size;

    mMutex.unlock();

    return true;
}
