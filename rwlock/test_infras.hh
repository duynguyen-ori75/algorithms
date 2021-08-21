extern "C" {
#include "simple_rwlock.h"
#include "rwlock.h"
#include "pthread.h"
}

#include <memory>

#define NO_THREADS 10

#define TEST_PACKAGE(locker_type, RLockFunc, RUnlockFunc, WLockFunc, WUnlockFunc) \
  class Counter_##locker_type { \
    public: \
    locker_type   *lk; \
    int           counter_; \
    Counter_##locker_type(int default_counter) : counter_(default_counter), lk(new locker_type()) {}\
    ~Counter_##locker_type() { delete lk; } \
    void RLock() { RLockFunc(lk); } \
    void RUnlock() { RUnlockFunc(lk); } \
    void WLock() { WLockFunc(lk); } \
    void WUnlock() { WUnlockFunc(lk); } \
  } \

TEST_PACKAGE(SimpleRWLocker, SimpleRLock, SimpleRUnlock, SimpleWLock, SimpleWUnlock);
TEST_PACKAGE(RWLocker, ReadLock, ReadUnlock, WriteLock, WriteUnlock);
TEST_PACKAGE(pthread_rwlock_t, pthread_rwlock_rdlock, pthread_rwlock_unlock, pthread_rwlock_wrlock, pthread_rwlock_unlock);

template <class locker_T>
void *atomicAdd(void *arg) {
  auto *data = (locker_T*) arg;
  data->WLock();
  data->counter_ ++;
  data->WUnlock();
  pthread_exit(NULL);
}

template <class locker_T>
void *atomicRead(void *arg) {
  auto *data = (locker_T*) arg;
  data->RLock();
  auto _ = data->counter_;
  data->RUnlock();
  pthread_exit(NULL);
}