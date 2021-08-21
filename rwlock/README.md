# Simple RWLock implementation in C

Inspired by this excellent blog: https://eli.thegreenplace.net/2019/implementing-reader-writer-locks/

## Implementation details

- Two versions: `SimpleRWLocker` and `RWLocker`
- `SimpleRWLocker` is implemented using a simple `pthread_mutex_t`
- `RWLocker` use several techniques
  - two conditional variables - `reader_` & `writer_` - to notify the threads to start the execution
  - a bool `writer_entered_` to notify all threads that a write thread is ready to run
    - no read thread can execute after the toggle
- Compare the two versions with built-in read-write lock from pthread
- Test and benchmark are done in C++

## Compile command

```shell
make
```

## Requirements

- [googletest](https://github.com/google/googletest)
- [googlebenchmark](https://github.com/google/benchmark)

## Benchmark

### 4 threads

```shell
---------------------------------------------------------------------------
Benchmark                                 Time             CPU   Iterations
---------------------------------------------------------------------------
BM_RWLocker_ReadIntensive             49564 ns        38662 ns        16561
BM_SimpleRWLocker_ReadIntensive       49022 ns        38296 ns        18462
BM_PthreadRWLock_ReadIntensive        49147 ns        38199 ns        18382
BM_RWLocker_WriteIntensive            49334 ns        38489 ns        17897
BM_SimpleRWLocker_WriteIntensive      49113 ns        38201 ns        18293
BM_PthreadRWLock_WriteIntensive       52856 ns        41617 ns        18261
```

### 10 threads

```shell
---------------------------------------------------------------------------
Benchmark                                 Time             CPU   Iterations
---------------------------------------------------------------------------
BM_RWLocker_ReadIntensive            138886 ns       135857 ns         5088
BM_SimpleRWLocker_ReadIntensive      138438 ns       133544 ns         4984
BM_PthreadRWLock_ReadIntensive       140300 ns       135779 ns         5104
BM_RWLocker_WriteIntensive           139047 ns       134489 ns         5185
BM_SimpleRWLocker_WriteIntensive     151277 ns       147345 ns         4225
BM_PthreadRWLock_WriteIntensive      148807 ns       144064 ns         4882
```

### 100 threads

```shell
---------------------------------------------------------------------------
Benchmark                                 Time             CPU   Iterations
---------------------------------------------------------------------------
BM_RWLocker_ReadIntensive           1626717 ns      1606569 ns          434
BM_SimpleRWLocker_ReadIntensive     1714836 ns      1699793 ns          444
BM_PthreadRWLock_ReadIntensive      1612786 ns      1594235 ns          426
BM_RWLocker_WriteIntensive          1573097 ns      1561560 ns          444
BM_SimpleRWLocker_WriteIntensive    1584243 ns      1570668 ns          441
BM_PthreadRWLock_WriteIntensive     1604831 ns      1586904 ns          440
```

### 1000 threads

```shell
---------------------------------------------------------------------------
Benchmark                                 Time             CPU   Iterations
---------------------------------------------------------------------------
BM_RWLocker_ReadIntensive          17886476 ns     17675306 ns           40
BM_SimpleRWLocker_ReadIntensive    17983891 ns     17965447 ns           38
BM_PthreadRWLock_ReadIntensive     17807024 ns     17774874 ns           40
BM_RWLocker_WriteIntensive         18128548 ns     18086237 ns           39
BM_SimpleRWLocker_WriteIntensive   18245323 ns     18232817 ns           38
BM_PthreadRWLock_WriteIntensive    18478389 ns     18400528 ns           39
```