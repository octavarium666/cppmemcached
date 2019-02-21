#include "EventLoop.hpp"
#include "Channel.hpp"
#include <assert.h>
#include <sys/epoll.h>

__thread EventLoop* t_loopInThisThread = nullptr;
const int pollTime = 10000;

EventLoop::EventLoop()
  : _looping(false),
    _quit(false),
    _threadId(0),    //Todo CurrentThread::tid()
    _poller(new Poller(this)){

}

EventLoop::~EventLoop() {
    assert(_looping);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop() {
    assert(!_looping);
    _looping = true;
    _quit = false;

    while(!_quit) {
        _activeChannels.clear();
        _poller->poll(pollTime, &_activeChannels);
        for (auto &activeChannel : _activeChannels) {
            activeChannel->handleEvent();
        }
    }

    _looping = false;
}

void EventLoop::quit() {
    _quit = true;
}

void EventLoop::updateChannel(Channel *channel) {
    assert(channel->ownerLoop() == this);
    _poller->updateChannel(channel);
}

