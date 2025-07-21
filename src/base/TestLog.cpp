#include "base/LogStream.h"
#include "base/Logger.h"
#include "FileLog.h"
#include "FileMgr.h"
#include "TTime.h"
#include "TaskMgr.h"
#include <thread>

using namespace fmps::base;
std::thread t;
void TestLog()
{
    t = std::thread([](){
        while(true) 
        {
            LOG_INFO << " test info!!!now:" << TTime::NowMs();
            LOG_DEBUG << " test debug!!! now:" << TTime::NowMs(); 
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });    
}

// int main(int argc,const char ** argv)
// {
//     FileLogPtr log = sFileMgr->GetFileLog("test.log");
//     log->SetRotate(kRotateMinute);
//     fmps::base::g_logger = new Logger(log);
//     fmps::base::g_logger->SetLogLevel(kTrace);
//     TaskPtr task4 = std::make_shared<Task>([](const TaskPtr &task)
//                                             {
//                                                 sFileMgr->OnCheck();
//                                                 task->Restart();
//                                             },
//                                             1000);      
//     sTaskMgr->Add(task4);      
//     TestLog(); 
//     while(1)
//     {
//         sTaskMgr->OnWork();
//         std::this_thread::sleep_for(std::chrono::milliseconds(50));
//     }    
//     return 0;
// }