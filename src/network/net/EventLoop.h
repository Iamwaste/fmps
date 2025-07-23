#pragma once

#include "Event.h"
#include "PipEvent.h"
#include <vector>
#include <sys/epoll.h>
#include <memory>
#include <unordered_map>
#include <functional>
#include <queue>
#include <mutex>


namespace fmps
{
    namespace network
    {
        using EventPtr = std::shared_ptr<Event>;
        using Func = std::function<void()>;
        class EventLoop
        {
        public:
            EventLoop();
            ~EventLoop();

            void Loop();
            void Quit();

            void AddEvent(const EventPtr &event);
            void DelEvent(const EventPtr &event);
            bool EnableEventWriting(const EventPtr &event,bool enable);
            bool EnableEventReading(const EventPtr &event,bool enable);
            void AssertInLoopThread();
            bool IsInLoopThread() const;
            void RunInLoop(const Func &f);
            void RunInLoop(Func &&f);
        private:
            void RunFuctions();
            void WakeUp();
            bool looping_{false};
            int epoll_fd_{-1};
            std::vector<struct epoll_event> epoll_events_;
            std::unordered_map<int,EventPtr> events_;
            std::queue<Func> functions_;
            std::mutex lock_;
            PipEventPtr pipe_event_;
        };
    }
}