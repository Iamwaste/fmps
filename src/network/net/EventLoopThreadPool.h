#pragma once

#include "base/NonCopyable.h"
#include "EventLoop.h"
#include "EventLoopThread.h"
#include <vector>
#include <atomic>

namespace fmps
{
    namespace network
    {
        using EventLoopThreadPtr = std::shared_ptr<EventLoopThread>;

        class EventLoopThreadPool : public base::NonCopyable
        {
        public:
            EventLoopThreadPool(int thread_num,int start = 0,int cpus = 4);
            ~EventLoopThreadPool();

            std::vector<EventLoop *> GetLoops() const;
            EventLoop *GetNextLoop();
            size_t Size();
            void Start();
        private:
            std::vector<EventLoopThreadPtr> threads_;
            std::atomic_char32_t loop_index_{0};
        };
    }
}