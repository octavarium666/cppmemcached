#pragma once
#include "Thread.hpp"
#include "EventLoop.hpp"

class EventLoop;

class Channel
{

public:
    typedef std::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);

    void handleEvent();
    void setReadCallback(const EventCallback& cb) {
        readCallback = cb;
    }
    void setWriteCallback(const EventCallback& cb) {
        writeCallback = cb;
    }
    void setErrorCallback(const EventCallback& cb) {
        errorCallback = cb;
    }

    ~Channel();
private:
    void update();
    static const int readEvent;

    EventLoop*  loop;
    const int   fd;
    int         events;
    int         revents;
    int         index;

    EventCallback readCallback;
    EventCallback writeCallback;
    EventCallback errorCallback;
};
