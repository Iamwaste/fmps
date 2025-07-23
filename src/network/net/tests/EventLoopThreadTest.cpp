#include "network/net/EventLoop.h"
#include "network/net/EventLoopThread.h"
#include "network/net/EventLoopThreadPool.h"
#include "network/net/PipEvent.h"
#include "base/TTime.h"
#include <iostream>
#include <thread>

using namespace fmps::network;

EventLoopThread eventloop_thread;
std::thread th;

void TestEventLoopThread()
{
    eventloop_thread.Run();
    EventLoop *loop = eventloop_thread.Loop();

    if(loop)
    {
        std::cout << "loop:" << loop << std::endl;
        PipEventPtr pipe = std::make_shared<PipEvent>(loop);
        loop->AddEvent(pipe);
        int64_t test = 12345;
        pipe->Write((const char*)&test,sizeof(test));
        th = std::thread([&pipe](){
            while (1)
        {
             int64_t now = fmps::base::TTime::NowMs();
            pipe->Write((const char*)&now,sizeof(now));
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        });
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
    }
}

void TestEventLoopThreadPool()
{
    EventLoopThreadPool pool(2,0,2);
    pool.Start();

    std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
    std::vector<EventLoop *> list = pool.GetLoops();
    for(auto &e:list)
    {
        e->RunInLoop([&e](){
            std::cout << "loop:" << e << "thread id:" << std::this_thread::get_id() << std::endl;
        });
    }
//    EventLoop * loop = pool.GetNextLoop();
//    std::cout << "loop :" << loop <<std::endl;
//    loop = pool.GetNextLoop();
//    std::cout << "loop :" << loop <<std::endl;
   
}
int main(int argc, char ** argv)
{
    TestEventLoopThreadPool();
    while (1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    return 0;
}