#include <array>          // 配列 C++11
#include <deque>          // 両端キュー
#include <forward_list>   // 単方向リスト C++11
#include <list>           // 双方向リスト
#include <map>            // 連想配列
#include <queue>          // FIFOキュー
#include <set>            // 集合
#include <stack>          // LIFOスタック
#include <unordered_map>  // 非順序連想配列 C++11
#include <unordered_set>  // 非順序集合 C++11
#include <vector>         // ベクタ配列
// #include <span>           // 部分シーケンスの参照 C++20

#include <benchmark/benchmark.h>

// #define SAMPLE_DATA_SHARED
#include "sampledata.h"

#define DO_RESERVE

constexpr int elem_size_start = 1024 * 1;
constexpr int elem_size_end = 1024 * 1;

static void VectorEmplaceBack(benchmark::State& state) {
  std::vector<SampleData> ctr;
  for (auto _ : state) {
#ifdef DO_RESERVE
    ctr.reserve(state.range(0));
#endif
    for (int i = 0; i < state.range(0); ++i) {
      ctr.emplace_back(state.range(1));
    }
  }
  state.SetBytesProcessed(int64_t(state.iterations()) * state.range(0) *
                          state.range(1));
}
// BENCHMARK(VectorEmplaceBack)->Arg(8)->Arg(64)->Arg(512)->Arg(1 << 10)->Arg(8
// << 10);
// BENCHMARK(VectorEmplaceBack)->Ranges({{8, 8 << 10}, {1024, 1024*4}});
BENCHMARK(VectorEmplaceBack)
    ->Ranges({{8, 8 << 10}, {elem_size_start, elem_size_end}});

static void VectorPushBack(benchmark::State& state) {
  std::vector<SampleData> ctr;
  for (auto _ : state) {
#ifdef DO_RESERVE
    ctr.reserve(state.range(0));
#endif
    for (int i = 0; i < state.range(0); ++i) {
      ctr.push_back(state.range(1));
    }
  }
  state.SetBytesProcessed(int64_t(state.iterations()) * state.range(0) *
                          state.range(1));
}
BENCHMARK(VectorPushBack)
    ->Ranges({{8, 8 << 10}, {elem_size_start, elem_size_end}});

static void DequeEmplaceBack(benchmark::State& state) {
  std::deque<SampleData> ctr;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      ctr.emplace_back(state.range(1));
    }
  }
  state.SetBytesProcessed(int64_t(state.iterations()) * state.range(0) *
                          state.range(1));
}
BENCHMARK(DequeEmplaceBack)
    ->Ranges({{8, 8 << 10}, {elem_size_start, elem_size_end}});

static void DequePushBack(benchmark::State& state) {
  std::deque<SampleData> ctr;
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      ctr.push_back(state.range(1));
    }
  }
  state.SetBytesProcessed(int64_t(state.iterations()) * state.range(0) *
                          state.range(1));
}
BENCHMARK(DequePushBack)
    ->Ranges({{8, 8 << 10}, {elem_size_start, elem_size_end}});

BENCHMARK_MAIN();