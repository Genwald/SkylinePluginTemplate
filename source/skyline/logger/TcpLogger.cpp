#include "skyline/logger/TcpLogger.hpp"

namespace skyline::TcpLogger {
    void SendRaw(const void* data, size_t size)
    {
        skyline_tcp_send_raw((char*)data, size);
    }
    void SendRaw(const char* data)
    {
        SendRaw((void*)data, strlen(data));
    }

    void SendRawFormat(const char* format, ...)
    {
        va_list args;
        char buff[0x1000] = {0};
        va_start(args, format);

        int len = vsnprintf(buff, sizeof(buff), format, args);

        SendRaw(buff, len);

        va_end (args);
    }
};
