#include "PipEvent.h"
#include <unistd.h>
#include <fcntl.h>
#include "network/base/Network.h"
#include <iostream>
#include <errno.h>

using namespace fmps::network;

PipEvent::PipEvent(EventLoop *loop)
:Event(loop)
{
    int fd[2] = {0,};
    auto ret = ::pipe2(fd,O_NONBLOCK);
    if(ret < 0)
    {
        NETWORK_ERROR << "pipe open failed.";
        exit(-1);
    }
    fd_ = fd[0];
    write_fd_ = fd[1];

}
PipEvent::~PipEvent()
{
    if(write_fd_ > 0)
    {
        ::close(write_fd_);
        write_fd_ = -1;
    }
}

void PipEvent::OnRead()
{
    int64_t tmp = 0;
    auto ret = ::read(fd_,&tmp,sizeof(tmp));
    if(ret < 0)
    {
        NETWORK_ERROR << "pipe read error.error:" << errno;
        return;
    }
    std::cout << "pipe read tmp:" << tmp << std::endl;
}
void PipEvent::OnClose()
{
    if(write_fd_ > 0)
    {
        ::close(write_fd_);
        write_fd_ = -1;
    }
}
void PipEvent::onError(const std::string &msg)
{
    std::cout << "error:" << msg << std::endl;
}
void PipEvent::Write(const char *data, size_t len)
{
    ::write(write_fd_,data,len);
}