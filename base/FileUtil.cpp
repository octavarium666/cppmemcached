#include "FileUtil.hpp"
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

using std::string;

AppendFile::AppendFile(string filename) 
: _fp(fopen(filename.c_str(), "ae")) {
    setbuffer(_fp, _buffer, sizeof(_buffer));
}

AppendFile::~AppendFile() {
    fclose(_fp);
}

void AppendFile::append(const char* logline, const size_t len) {
    size_t n = this->write(logline, len);
    size_t remain = len - n;
    while(remain > 0) {
        size_t last = this->write(logline + n, remain);
        if(last == 0) {
            int err = ferror(_fp);
            if(err)
                fprintf(stderr, "AppendFile::append() failed\n");
            break;
        }
        n += last;
        remain = len - n;
    }
}

void AppendFile::flush() {
    fflush(_fp);
}

//nonblocking write
size_t AppendFile::write(const char* logline, size_t len) {
    return fwrite_unlocked(logline, 1, len, _fp);
}