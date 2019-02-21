#pragma once

#include <vector>
#include <map>
#include "noncopyable.hpp"
#include "EventLoop.hpp"

struct epollfd;

class Channel;

class EventLoop;

class Poller : noncopyable
{
public:
    typedef std::vector<Channel*> ChannelList;

    Poller(EventLoop* loop);
    ~Poller();

    int poll(int timeout, ChannelList *activeChannels);

    void updateChannel(Channel* channel);

    void assertInLoopThread() {}
private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    typedef std::vector<struct pollfd> PollfdList;
    typedef std::map<int, Channel*> ChannelMap;

    EventLoop* _ownerLoop;
    PollfdList _pollfds;
    ChannelMap _channels;
};

