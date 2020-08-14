// #include <array>          // 配列 C++11
// #include <deque>          // 両端キュー
// #include <forward_list>   // 単方向リスト C++11
// #include <list>           // 双方向リスト
// #include <map>            // 連想配列
// #include <queue>          // FIFOキュー
// #include <set>            // 集合
// #include <stack>          // LIFOスタック
// #include <unordered_map>  // 非順序連想配列 C++11
// #include <unordered_set>  // 非順序集合 C++11
// #include <vector>         // ベクタ配列
// #include <span>           // 部分シーケンスの参照 C++20

#include <benchmark/benchmark.h>

#define SAMPLE_DATA_SHARED
#define DO_RESERVE

#include "benchmark_deque.h"
#include "benchmark_vector.h"

BENCHMARK_MAIN();
