
#pragma once

#include <cstdarg>
#include <cstring>
#include <stdio.h>

extern "C" void skyline_tcp_send_raw(char* data, size_t size);

namespace skyline::TcpLogger {
    void SendRaw(const void*, size_t);
    void SendRaw(const char*);
    void SendRawFormat(const char*, ...);
};