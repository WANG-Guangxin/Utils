/******************************************************************************

epoller

*******************************************************************************/

#ifndef _EPOLLER_
#define _EPOLLER_

#include <sys/epoll.h> // epoll_ctl
#include <fcntl.h>     // fcntl()
#include <unistd.h>    // close()
#include <assert.h> 
#include <vector>
#include <errno.h>


class Epoller{
public:
    explicit Epoller(int maxEvent = 1024);
    
    ~Epoller();
    
    bool addFd(int fd,uint32_t events);
    
    bool modFd(int fd,uint32_t events);
    
    bool delFd(int fd);
    
    int wait(int timeoutMs = -1);
    
    int getEventFd(size_t i) const;
    
    uint32_t getEvents(size_t i) const;
    
private:
    
    int epollFd_;
    
    std::vector<struct epoll_event> events_;
    
};



Epoller::Epoller(int maxEvent = 1024):epollFd_(epoll_create(512)),events_(maxEvent){
    assert(epollFd_ >= 0 && events_.size() > 0);
}


Epoller::~Epoller(){
    close(epollFd_);
}


bool Epoller::addFd(int fd,uint32_t events){
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return 0 == epoll_ctl(epollFd_, EPOLL_CTL_ADD,fd,&ev);
}
    
bool Epoller::modFd(int fd,uint32_t events){
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return 0 == epoll_ctl(epollFd_,EPOLL_CTL_MOD,fd,&ev);
}
    
bool Epoller::delFd(int fd){
    if( fd < 0) return false;
    epoll_event ev = {0};
    return 0 == epoll_ctl(epollFd_,EPOLL_CTL_DEL,fd,&ev);
}
    
int Epoller::wait(int timeoutMs = -1){
    return epoll_wait(epollFd_, &events_[0] , static_cast<int>(events_.size()), timeoutMs);
}
    
int Epoller::getEventFd(size_t i) const{
    assert(i < events_.size() && i >= 0);
    return events_[i].data.fd;
}

uint32_t Epoller::getEvents(size_t i) const{
    assert(i < events_.size() && i >= 0);
    return events_[i].events;
}

#endif
