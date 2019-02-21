//
// Created by octavarrium on 19-2-21.
//
#pragma once

#include <string>
#include "noncopyable.hpp"
#include "Mutex.hpp"

class AsyncLogging : noncopyable {
public:
    AsyncLogging(const std::string basename);

private:
    MutexLock _mutex;

};
