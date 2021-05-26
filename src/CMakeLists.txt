add_executable(io-format-benchmark "io-format-benchmark.cpp")

target_link_libraries(io-format-benchmark
	PUBLIC benchmark::benchmark
	PUBLIC fmt::fmt)