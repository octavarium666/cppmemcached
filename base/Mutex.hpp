//_mutex RAII class

#pragma once

#include <pthread.h>
#include <assert.h>
#include "noncopyable.hpp"

class MutexLock : noncopyable
{
public:
    MutexLock() {
        pthread_mutex_init(&mutex, nullptr);
    }

    ~MutexLock() {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }

    void lock() {
        pthread_mutex_lock(&mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t* getThreadMutex() {
        return &mutex;
    }
private:
    pthread_mutex_t mutex;

    friend class Condition;
};

class MutexLockGuard
{
public:
    explicit MutexLockGuard(MutexLock &mutexLock) :
    _mutex(mutexLock) {
        _mutex.lock();
    }
    ~MutexLockGuard() {
        _mutex.unlock();
    }
private:
    MutexLock& _mutex;
};

