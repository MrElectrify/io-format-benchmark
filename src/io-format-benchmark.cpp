#include <benchmark/benchmark.h>
#include <fmt/format.h>

#include <cstdio>
#include <format>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <vector>

class Data
{
public:
	Data() : m_ints(500000), m_floats(500000) 
	{
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_int_distribution iDist(
			std::numeric_limits<int>::min(),
			std::numeric_limits<int>::max());
		// gen 500k ints
		std::generate(m_ints.begin(), m_ints.end(), 
			[&] { return iDist(eng); });
		std::uniform_real_distribution<float> fDist(
			std::numeric_limits<float>::min(),
			std::numeric_limits<float>::max());
		// gen 500k floats
		std::generate(m_floats.begin(), m_floats.end(),
			[&] { return fDist(eng); });
	}

	const std::vector<float>& Floats() const noexcept { return m_floats; }
	const std::vector<int>& Ints() const noexcept { return m_ints; }
private:
	std::vector<int> m_ints;
	std::vector<float> m_floats;
};

Data g_data;

void StreamUnformatted(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		std::stringstream ss;
		ss << "Int: " << g_data.Ints()[i % g_data.Ints().size()] << ", float: " <<
			g_data.Floats()[i % g_data.Floats().size()] << '\n';
		benchmark::DoNotOptimize(ss.str());
	}
}
BENCHMARK(StreamUnformatted);

void StreamHexInt(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		std::stringstream ss;
		ss << "Int: " << std::hex << g_data.Ints()[i % g_data.Ints().size()] <<
			std::dec << ", float: " << g_data.Floats()[i % g_data.Floats().size()] << '\n';
		benchmark::DoNotOptimize(ss.str());
	}
}
BENCHMARK(StreamHexInt);

void StreamPaddedHexInt(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		std::stringstream ss;
		ss << "Int: " << std::hex << std::setw(8) << std::setfill('0') <<
			g_data.Ints()[i % g_data.Ints().size()] << 
			std::dec << ", float: " << 
			g_data.Floats()[i % g_data.Floats().size()] << '\n';
		benchmark::DoNotOptimize(ss.str());
	}
}
BENCHMARK(StreamPaddedHexInt);

void StdFormatUnformatted(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		benchmark::DoNotOptimize(std::format("Int: {}, float: {}\n", 
			g_data.Ints()[i % g_data.Ints().size()],
			g_data.Floats()[i % g_data.Floats().size()]));
	}
}
BENCHMARK(StdFormatUnformatted);

void StdFormatHexInt(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		benchmark::DoNotOptimize(std::format("Int: {:x}, float: {}\n",
			g_data.Ints()[i % g_data.Ints().size()],
			g_data.Floats()[i % g_data.Floats().size()]));
	}
}
BENCHMARK(StdFormatHexInt);

void StdFormatPaddedHexInt(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		benchmark::DoNotOptimize(std::format("Int: {:08x}, float: {}\n",
			g_data.Ints()[i % g_data.Ints().size()],
			g_data.Floats()[i % g_data.Floats().size()]));
	}
}
BENCHMARK(StdFormatPaddedHexInt);

void FmtUnformatted(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		benchmark::DoNotOptimize(fmt::format("Int: {}, float: {}\n",
			g_data.Ints()[i % g_data.Ints().size()],
			g_data.Floats()[i % g_data.Floats().size()]));
	}
}
BENCHMARK(FmtUnformatted);

void FmtHexInt(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		benchmark::DoNotOptimize(fmt::format("Int: {:x}, float: {}\n",
			g_data.Ints()[i % g_data.Ints().size()],
			g_data.Floats()[i % g_data.Floats().size()]));
	}
}
BENCHMARK(FmtHexInt);

void FmtPaddedHexInt(benchmark::State& state)
{
	for (size_t i = 0; state.KeepRunning() == true; ++i)
	{
		benchmark::DoNotOptimize(fmt::format("Int: {:08x}, float: {}\n",
			g_data.Ints()[i % g_data.Ints().size()],
			g_data.Floats()[i % g_data.Floats().size()]));
	}
}
BENCHMARK(FmtPaddedHexInt);

BENCHMARK_MAIN();