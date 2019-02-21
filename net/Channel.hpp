#pragma once
#include "Thread.hpp"
#include "EventLoop.hpp"
#include "noncopyable.hpp"

class EventLoop;

class Channel : noncopyable
{

public:
    typedef std::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);

    void handleEvent();
    void setReadCallback(const EventCallback& cb) {
        _readCallback = cb;
    }
    void setWriteCallback(const EventCallback& cb) {
        _writeCallback = cb;
    }
    void setErrorCallback(const EventCallback& cb) {
        _errorCallback = cb;
    }

    int getFd() {
        return _fd;
    }
    int getEvents() {
        return _events;
    }
    void setRevents(int revt) {
        _revents = revt;
    }
    bool isNoneEvents() const {return _events == noneEvent;}

    void enableReading() { _events |= readEvent; update();}

    int getIndex() const {
        return _index;
    }
    void setIndex(int idx) {
        _index = idx;
    }
    EventLoop* ownerLoop() {
        return _loop;
    }

    ~Channel();

private:
    void update();

    static const int readEvent;
    static const int noneEvent;
    static const int writeEvent;

    EventLoop*  _loop;
    const int   _fd;
    int         _events;
    int         _revents;
    int         _index;

    EventCallback _readCallback;
    EventCallback _writeCallback;
    EventCallback _errorCallback;
};
