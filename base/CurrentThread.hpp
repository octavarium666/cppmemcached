#pragma once

#include <stdint.h>

namespace CurrentThread {
    extern __thread int cachedTid;
    extern __thread char tidString[32];
    extern __thread int tidStringLength;
    extern __thread const char* threadName;

    
}
