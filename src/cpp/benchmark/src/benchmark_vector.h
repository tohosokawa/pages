#ifndef __BENCHMARK_VECTOR_H__
#define __BENCHMARK_VECTOR_H__

#include <vector>  // ベクタ配列

#include <benchmark/benchmark.h>

#include "param.h"
#include "sampledata.h"

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

#endif  // __BENCHMARK_VECTOR_H__