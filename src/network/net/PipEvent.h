#pragma once

#include "Event.h"
#include <memory>

namespace fmps
{
    namespace network
    {
        class PipEvent : public Event
        {
        public:
            PipEvent(EventLoop *loop);
            ~PipEvent();

            void OnRead() override;
            void OnClose() override;
            void onError(const std::string &msg) override;
            void Write(const char* data,size_t len);
        private:
            int write_fd_{-1};
        };
        using PipEventPtr = std::shared_ptr<PipEvent>;
    }
}