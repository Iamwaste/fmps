#pragma once
#include "Logger.h"
#include <sstream>

namespace fmps
{
    namespace base
    {
        extern Logger * g_logger;
        class LogStream
        {
        public:
            LogStream(Logger *loger,const char* file, int line, LogLevel l, const char *func=nullptr);
            ~LogStream();

            template<class T> LogStream & operator<<(const T& value) 
            {
                stream_ << value;
                return *this;
            }
        private:
            std::ostringstream stream_;
            Logger *logger_{nullptr};
        };
    }
}

#define LOG_TRACE   \
    if(g_logger&&fmps::base::g_logger->GetLogLevel() <= fmps::base::kTrace)   \
        fmps::base::LogStream(fmps::base::g_logger,__FILE__,__LINE__,fmps::base::kTrace,__func__)
#define LOG_DEBUG  \
    if(g_logger&&fmps::base::g_logger->GetLogLevel() <= fmps::base::kDebug)   \
        fmps::base::LogStream(fmps::base::g_logger,__FILE__,__LINE__,fmps::base::kDebug,__func__)
#define LOG_INFO   \
    if(g_logger&&fmps::base::g_logger->GetLogLevel() <= fmps::base::kInfo)   \
        fmps::base::LogStream(fmps::base::g_logger,__FILE__,__LINE__,fmps::base::kInfo)
#define LOG_WARN   \
    fmps::base::LogStream(fmps::base::g_logger,__FILE__,__LINE__,fmps::base::kWarn)
#define LOG_ERROR  fmps::base::LogStream(fmps::base::g_logger,__FILE__,__LINE__,fmps::base::kError)