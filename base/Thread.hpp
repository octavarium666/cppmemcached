#pragma once 
#include <memory>
#include <functional>
#include <pthread.h>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>


#include "noncopyable.hpp"

class Thread
{

public:
    typedef std::function<void()> ThreadFunc;

    explicit Thread(const ThreadFunc&, const std::string& name = std::string());
    ~Thread();

    void start();

    int join();

    bool started() const { return _starded; }

    pid_t tid() const { return _tid; }

    const std::string& name() const { return _name; }


private:

    bool            _starded;
    bool            _joined;
    pthread_t       _pthreadId;
    pid_t           _tid;
    std::string     _name;
};
