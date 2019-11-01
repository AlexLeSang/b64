# b64

Implementation for base64 encoding.

## Tributes

Many thanks to the authors of [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64).

## Performance benchmark

2019-11-02 00:25:48
Running ./build/bin/b64_performance
Run on (8 X 3500 MHz CPU s)
CPU Caches:
L1 Data 32K (x4)
L1 Instruction 32K (x4)
L2 Unified 256K (x4)
L3 Unified 6144K (x1)
Load Average: 6.41, 4.98, 4.05
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
BM_Decode/8/real_time            737 ns          737 ns       869816
BM_Decode/16/real_time          1010 ns         1011 ns       674121
BM_Decode/32/real_time          1537 ns         1538 ns       454340
BM_Decode/64/real_time          2735 ns         2735 ns       253353
BM_Decode/128/real_time         4869 ns         4864 ns       136293
BM_Decode/256/real_time         9105 ns         9093 ns        77162
BM_Decode/512/real_time        17502 ns        17487 ns        40071
BM_Decode/1024/real_time       34260 ns        34222 ns        20368
BM_Decode/2048/real_time       68726 ns        68595 ns        10207
BM_Decode/4096/real_time      135330 ns       135066 ns         5152
BM_Decode/8192/real_time      273256 ns       272626 ns         2629
BM_Decode/12288/real_time     409869 ns       408939 ns         1644
BM_Encode/8/real_time            524 ns          527 ns      1308210
BM_Encode/16/real_time           595 ns          596 ns      1188499
BM_Encode/32/real_time           658 ns          660 ns      1057761
BM_Encode/64/real_time           793 ns          795 ns       901931
BM_Encode/128/real_time         1077 ns         1078 ns       650073
BM_Encode/256/real_time         1584 ns         1582 ns       442178
BM_Encode/512/real_time         2458 ns         2452 ns       285136
BM_Encode/1024/real_time        4243 ns         4219 ns       159327
BM_Encode/2048/real_time        7886 ns         7819 ns        90299
BM_Encode/4096/real_time       14712 ns        14619 ns        46713
BM_Encode/8192/real_time       28210 ns        28082 ns        24602
BM_Encode/12288/real_time      41755 ns        41639 ns        16372


## License

[GPL-3.0](./LICENSE)
