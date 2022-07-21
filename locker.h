#ifndef LOCKER_H
#define LOCKER_H

#include <pthread.h>
#include <exception>
#include <semaphore.h>

// 线程同步机制封装类

// 互斥锁类
class locker {
public:
    locker() { //  构造函数
        if (pthread_mutex_init(&m_mutex, NULL) != 0) {
            throw std::exception();
        }
    }
    ~locker() { // 析构函数
        pthread_mutex_destroy(&m_mutex);
    }

    bool lock() { // 上锁函数
        return pthread_mutex_lock(&m_mutex) == 0;
    }

    bool unlock() { // 解锁函数
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

    pthread_mutex_t* get() { // 获得互斥量
        return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};

// 条件变量类
class cond {
public:
    cond() { //  构造函数
        if (pthread_cond_init(&m_cond, NULL) != 0) {
            throw std::exception();
        }
    }

    ~cond() { // 析构函数
        pthread_cond_destroy(&m_cond);
    }

    bool wait(pthread_mutex_t* mutex) { // 阻塞等待
        return pthread_cond_wait(&m_cond, mutex) == 0;
    }

    bool timedwait(pthread_mutex_t* mutex, struct timespec t) { // 超时时间阻塞等待
        return pthread_cond_timedwait(&m_cond, mutex, &t) == 0;
    }

    bool signal() { // 让条件变量增加 让一个或多个线程唤醒
        return pthread_cond_signal(&m_cond) == 0;
    }

    bool broadcast() { // 唤醒所有线程
        return pthread_cond_broadcast(&m_cond) == 0;
    }

private:
    pthread_cond_t m_cond;
};


// 信号量类
class sem {
public:
    sem() { // 构造函数
        if (sem_init(&m_sem, 0, 0) != 0) {
            throw std::exception();
        }
    }

    sem(int num) { // 构造函数 带有初始值
        if (sem_init(&m_sem, 0, num) != 0) {
            throw std::exception();
        }
    }

    ~sem() { // 析构函数
        sem_destroy(&m_sem);
    }

    bool wait() { // 等待信号量
        return sem_wait(&m_sem) == 0;
    }

    bool post() { // 增加信号量
        return sem_post(&m_sem) == 0;
    }

private:
    sem_t m_sem;
};


#endif