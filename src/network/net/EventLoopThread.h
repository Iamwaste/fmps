#pragma once

#include "base/NonCopyable.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include "EventLoop.h"
#include <future>

namespace fmps
{
    namespace network
    {
        class EventLoopThread : public base::NonCopyable
        {
        public:
            EventLoopThread();
            ~EventLoopThread();

            void Run();
            EventLoop *Loop() const;
            std::thread &Thread();
        private:
            void StartEventLoop();
            EventLoop * loop_{nullptr};
            std::thread thread_;
            bool running_{false};
            std::mutex lock_;
            std::condition_variable condition_;
            std::once_flag once_;
            std::promise<int> promise_loop_;
        };
    }
}