# b64

Implementation of base64 encoding/decoding.

## Tributes

Many thanks to the authors of [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64).

## Performance benchmark

### First version of the algorithm
```
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
```

### First attempts on optimization
```
Run on (8 X 3500 MHz CPU s)
CPU Caches:
  L1 Data 32K (x4)
  L1 Instruction 32K (x4)
  L2 Unified 256K (x4)
  L3 Unified 6144K (x1)
Load Average: 2.38, 1.82, 1.67
--------------------------------------------------------------------
Benchmark                          Time             CPU   Iterations
--------------------------------------------------------------------
BM_Encode/8/real_time            531 ns          534 ns      1326270
BM_Encode/16/real_time           612 ns          613 ns      1129405
BM_Encode/32/real_time           686 ns          689 ns      1029036
BM_Encode/64/real_time           863 ns          862 ns       809919
BM_Encode/128/real_time         1125 ns         1120 ns       594116
BM_Encode/256/real_time         1732 ns         1723 ns       382608
BM_Encode/512/real_time         2472 ns         2463 ns       274787
BM_Encode/1024/real_time        4217 ns         4190 ns       167072
BM_Encode/2048/real_time        7791 ns         7713 ns        90153
BM_Encode/4096/real_time       16233 ns        16004 ns        38930
BM_Encode/8192/real_time       28504 ns        28333 ns        24512
BM_Encode/14336/real_time      49458 ns        49187 ns        14221

BM_Decode/8/real_time            628 ns          629 ns      1090785
BM_Decode/16/real_time           781 ns          782 ns       900344
BM_Decode/32/real_time          1103 ns         1104 ns       627812
BM_Decode/64/real_time          1779 ns         1780 ns       393160
BM_Decode/128/real_time         2979 ns         2980 ns       235286
BM_Decode/256/real_time         5155 ns         5153 ns       135955
BM_Decode/512/real_time         9619 ns         9617 ns        74471
BM_Decode/1024/real_time       18412 ns        18381 ns        37881
BM_Decode/2048/real_time       35666 ns        35582 ns        19914
BM_Decode/4096/real_time       69920 ns        69726 ns        10106
BM_Decode/8192/real_time      136653 ns       136250 ns         4797
BM_Decode/12288/real_time     203440 ns       202864 ns         3473
```

## License

[GPL-3.0](./LICENSE)
