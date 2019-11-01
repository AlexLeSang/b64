#include <b64.hpp>
#include <benchmark/benchmark.h>

#include <cstdlib>

using namespace std;

string gen_random(const size_t len) {
  static const char alphanum[] = "0123456788"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";

  string result(len, '\n');

  for (size_t i = 0; i < len - 1; ++i) {
    const size_t value = static_cast<size_t>(rand()) % (sizeof(alphanum) - 1);
    result[i] = alphanum[value];
  }

  return result;
}

static void BM_Decode(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    const auto range = static_cast<size_t>(state.range());
    const auto input = gen_random(range);
    state.ResumeTiming();
    const auto decoded = b64::decode(input);
    benchmark::DoNotOptimize(decoded);
  }
}
BENCHMARK(BM_Decode)->RangeMultiplier(2)->Range(8, 12 << 10)->UseRealTime();

static void BM_Encode(benchmark::State &state) {
  for (auto _ : state) {
    state.PauseTiming();
    const auto range = static_cast<size_t>(state.range());
    const auto input = gen_random(range);
    state.ResumeTiming();
    const auto encoded = b64::encode(input);
    benchmark::DoNotOptimize(encoded);
  }
}
BENCHMARK(BM_Encode)->RangeMultiplier(2)->Range(8, 12 << 10)->UseRealTime();

BENCHMARK_MAIN();
