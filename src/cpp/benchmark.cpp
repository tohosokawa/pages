#include <benchmark/benchmark.h>
#include <cstring>
#include <deque>
#include <iostream>
#include <list>
#include <vector>

class LargeData {
  char mem[1000 * 1000];
};

static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state) std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state) std::string copy(x);
}
BENCHMARK(BM_StringCopy);

static void BM_VectorAdd(benchmark::State& state) {
  std::vector<LargeData> container;
  for (auto _ : state) container.emplace_back(LargeData());
}
BENCHMARK(BM_VectorAdd);

static void BM_DequeAdd(benchmark::State& state) {
  std::deque<LargeData> container;
  for (auto _ : state) container.emplace_back(LargeData());
}
BENCHMARK(BM_DequeAdd);

static void BM_ListAdd(benchmark::State& state) {
  std::list<LargeData> container;
  for (auto _ : state) container.emplace_back(LargeData());
}
BENCHMARK(BM_ListAdd);

class MyFixture : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State& state) {}

  void TearDown(const ::benchmark::State& state) {}
};

BENCHMARK_F(MyFixture, FooTest)(benchmark::State& st) {
  for (auto _ : st) {
  }
}

BENCHMARK_DEFINE_F(MyFixture, BarTest)(benchmark::State& st) {
  for (auto _ : st) {
  }
}
/* BarTest is NOT registered */
BENCHMARK_REGISTER_F(MyFixture, BarTest)->Threads(2);
/* BarTest is now registered */

template <class Q>
void BM_Sequential(benchmark::State& state) {
  Q q;
  typename Q::value_type v;
  for (auto _ : state) {
    for (int i = state.range(0); i--;) q.emplace_back(v);
    for (int e = state.range(0); e--;) q.pop_back();
  }
  // actually messages, not bytes:
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) *
                          state.range(0));
}
BENCHMARK_TEMPLATE(BM_Sequential, std::vector<int>)->Range(1 << 0, 1 << 10);

static void BM_memcpy(benchmark::State& state) {
  char* src = new char[state.range(0)];
  char* dst = new char[state.range(0)];
  std::memset(src, 'x', state.range(0));
  for (auto _ : state) std::memcpy(dst, src, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] src;
  delete[] dst;
}
BENCHMARK(BM_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(8 << 10);

BENCHMARK_MAIN();