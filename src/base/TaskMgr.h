#pragma once

#include "Task.h"
#include "Singleton.h"
#include <unordered_set>
#include <mutex>

namespace fmps
{
    namespace base
    {
        class TaskMgr:public NonCopyable
        {
        public:
            TaskMgr()=default;
            ~TaskMgr()=default;

            void OnWork();
            bool Add(TaskPtr &task);
            bool Del(TaskPtr &task);
        private:
            std::unordered_set<TaskPtr> tasks_;
            std::mutex lock_;
        };

    }
    #define sTaskMgr fmps::base::Singleton<fmps::base::TaskMgr>::Instance()
}