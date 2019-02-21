#include "Thread.hpp"

#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <type_traits>

void Thread::start() {
}

int Thread::join() {
    assert(_starded);
    assert(!_joined);
    _joined = true;
    return pthread_join(_pthreadId, NULL);
} 