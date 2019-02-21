#include "LogFile.hpp"
#include "FileUtil.hpp"

LogFile::LogFile(const std::string &name, int flushTime)
  : _basename(name),
    _flushEveryN(flushTime),
    _count(0),
    _mutex(new MutexLock)
{

    _file.reset(new AppendFile(_basename));
}

LogFile::~LogFile() {}

void LogFile::append(const char *logline, int len) {
    MutexLockGuard lock(*_mutex);

}

void LogFile::flush() {
    MutexLockGuard lock(*_mutex);
    _file->flush();
}

void LogFile::append_unlock(const char *logline, int len) {
    _file->append(logline, len);
    ++_count;
    if(_count >= _flushEveryN) {
        _count = 0;
        _file->flush();
    }
}


