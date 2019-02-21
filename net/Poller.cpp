#include <map>
#include <vector>
#include <assert.h>
#include <sys/poll.h>
#include "Poller.hpp"
#include "Channel.hpp"

Poller::Poller(EventLoop *loop) : _ownerLoop(loop) {

}

Poller::~Poller() {

}

void Poller::fillActiveChannels(int numEvents, Poller::ChannelList *activeChannels) const {
    for(auto pfd = _pollfds.begin(); pfd!= _pollfds.end()&& numEvents > 0; ++pfd){
        if(pfd->revents > 0) {
            --numEvents;
            auto ch = _channels.find(pfd->fd);
            assert(ch != _channels.end());
            Channel* chan = ch->second;
            assert(chan->getFd() == pfd->fd);
            chan->setRevents(pfd->revents);
            activeChannels->push_back(chan);
        }
    }
}

void Poller::updateChannel(Channel *channel) {
    assertInLoopThread();
    if(channel->getIndex() < 0) {
        struct pollfd pfd;
        pfd.fd = channel->getFd();
        pfd.events = static_cast<short>(channel->getEvents());
        pfd.revents = 0;
        _pollfds.push_back(pfd);
        int idx = static_cast<int>(_pollfds.size() - 1);
        channel->setIndex(idx);
        _channels[pfd.fd] = channel;
    } else {
        assert(_channels.find(channel->getFd()) != _channels.end());
        assert(_channels[channel->getFd()] == channel);
        int idx = channel->getIndex();
        assert(0 <= idx && idx < _pollfds.size());
        struct pollfd& pfd = _pollfds[idx];
        assert(pfd.fd == channel->getFd() || pfd.fd == -1);
        pfd.events = static_cast<short>(channel->getEvents());
        pfd.revents = -1;
    }
}


//Todo Timestamp
int Poller::poll(int timeout, Poller::ChannelList *activeChannels) {
    int numEvents = ::poll(&*_pollfds.begin(), _pollfds.size(), timeout);
    if(numEvents > 0) {
        fillActiveChannels(numEvents ,activeChannels);
    } else if (numEvents == 0) {

    } else {

    }
    return 0;
}
