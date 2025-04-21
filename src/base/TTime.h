#pragma once
#include <cstdint>
#include <string>

namespace fmps
{
    namespace base
    {
        class TTime
        {
        public:
            static int64_t NowMs();
            static int64_t Now();
            static int64_t Now(int &year,int &month,int &day,int &hour,int &minute,int &second);
            static std::string ISOTime();
        };
    } 
    
}