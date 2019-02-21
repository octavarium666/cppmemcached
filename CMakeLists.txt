cmake_minimum_required(VERSION 3.13)
project(cppmemcached)

set(CMAKE_CXX_STANDARD 14)

include_directories(base)
include_directories(net)
include_directories(server)
include_directories(test)

add_executable(cppmemcached
        base/Condition.cpp
        base/Condition.hpp
        base/copyable.hpp
        base/CurrentThread.hpp
        base/FileUtil.cpp
        base/FileUtil.hpp
        base/LogFile.cpp
        base/LogFile.hpp
        base/MemoryPool.cpp
        base/MemoryPool.hpp
        base/Mutex.hpp
        base/noncopyable.hpp
        base/Thread.cpp
        base/Thread.hpp
        net/Channel.cpp
        net/Channel.hpp
        net/Poller.cpp
        net/Poller.hpp
        net/EventLoop.cpp
        net/EventLoop.hpp
        server/Item.cpp
        server/Item.hpp
        server/MemcacheServer.cpp
        server/MemcacheServer.hpp
        test/NoneLockQueue.cc base/AsyncLogging.cpp base/AsyncLogging.hpp base/Timestamp.cpp base/Timestamp.hpp base/Timestamp.cpp net/TimerQueue.cpp net/TimerQueue.hpp)
