# io-format-benchmark
Benchmarking various sane methods of formatted IO in C++20

Okay, I admit, it doesn't actually test IO. I was so surprised by the results that I took IO completely out of the equation to show raw string formatting speed. And, WOW. `std::format` needs some time.

The benchmark simply generates 500k integers and 500k floats, and formats as many as it can in the time allotted by `benchmark`, returning a `std::string`.

```
2021-05-26T16:22:11-04:00
Running C:\Users\Andrew\Source\Repos\io-format-benchmark\out\build\x64-Release\src\io-format-benchmark.exe
Run on (12 X 4008 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
----------------------------------------------------------------
Benchmark                      Time             CPU   Iterations
----------------------------------------------------------------
StreamUnformatted           1564 ns         1569 ns       448000
StreamHexInt                1668 ns         1674 ns       448000
StreamPaddedHexInt          1505 ns         1500 ns       448000
StdFormatUnformatted        1936 ns         1925 ns       373333
StdFormatHexInt             3395 ns         3376 ns       203636
StdFormatPaddedHexInt       3375 ns         3376 ns       203636
FmtUnformatted               208 ns          209 ns      3733333
FmtHexInt                    231 ns          230 ns      2986667
FmtPaddedHexInt              241 ns          246 ns      2800000
```
