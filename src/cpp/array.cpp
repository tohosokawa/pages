#include <algorithm>
#include <array>
#include <iostream>

int main() {
  // 3要素のint型配列を定義し、初期化子リストで初期化
  std::array<int, 3> ar = {3, 1, 4};

  // size()メンバ関数による要素数取得
  for (std::size_t i = 0; i < ar.size(); ++i) {
    ++ar[i];  // operator[]で任意の要素にランダムアクセス
  }

  // イテレータによる要素の横断
  std::for_each(ar.begin(), ar.end(),
                [](int x) { std::cout << x << std::endl; });
}