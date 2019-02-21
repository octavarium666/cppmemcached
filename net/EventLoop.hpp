#pragma once

#include "noncopyable.hpp"
#include "Thread.hpp"
#include "Poller.hpp"

class EventLoop : noncopyable
{
public:
    std::function<void()> functor;

    EventLoop();
    ~EventLoop();

    void loop();

    void quit();

    void updateChannel(Channel* channel);

    void assertInLoopThread() {

    }

    bool isInLoopThread() const {}
private:
    void abortNotInLoopThread();

    typedef std::vector<Channel*> ChannelList;

    bool _looping;
    bool _quit;
    const pid_t _threadId;
    std::unique_ptr<Poller> _poller;
    ChannelList _activeChannels;
};
