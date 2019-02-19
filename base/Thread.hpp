#pragma once 
#include <memory>
#include <functional>
#include <pthread.h>
#include "noncopyable.hpp"

class Thread
{

public:
    typedef std::function<void()> ThreadFunc;

    Thread();
    ~Thread();

    void start();

    int join();

    bool started() const { return starded; }

    pid_t tid() const { return tid; }

    const std::string& name() const { return name; }


private:

    bool            starded;
    bool            joined;
    pthread_t       pthreadId;
    pid_t           tid;
    std::string     name;

};
