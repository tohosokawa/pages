#ifndef __BENCHMARK_DEQUE_H__
#define __BENCHMARK_DEQUE_H__

#include <deque>  // 両端キュー

#include <benchmark/benchmark.h>

#include "param.h"
#include "sampledata.h"

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

#endif  // __BENCHMARK_DEQUE_H__