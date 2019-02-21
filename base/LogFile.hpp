#pragma once

#include "FileUtil.hpp"
#include "Mutex.hpp"
#include "noncopyable.hpp"
#include <string>
#include <memory>

class LogFile : noncopyable
{
public:
    LogFile(const std::string& basename, int flushEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    bool rollFile();
private:
    void append_unlock(const char* logline, int len);

    const std::string _basename;
    const int _flushEveryN;

    int _count;
    std::unique_ptr<MutexLock> _mutex;
    std::unique_ptr<AppendFile> _file;
 
};

