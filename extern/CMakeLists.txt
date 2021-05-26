# avoid the gtest dependency
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests.")
set(FMT_TEST OFF CACHE BOOL "Disable formatlib tests.")

add_subdirectory(benchmark)
add_subdirectory(fmt)