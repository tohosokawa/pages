#include <iostream>
#include <valarray>

template <class T>
void print(const char* name, const std::valarray<T>& v) {
  std::cout << name << " : {";
  bool first = true;

  // 範囲for文で全要素を走査する
  for (const T& x : v) {
    if (first) {
      first = false;
    } else {
      std::cout << ',';
    }
    std::cout << x;
  }
  std::cout << "}" << std::endl;
}

int main() {
  // 四則演算
  // 全ての要素同士に同じ演算子を適用する
  {
    std::valarray<int> a = {3, 6, 9};
    std::valarray<int> b = {4, 5, 6};

    std::valarray<int> plus = a + b;
    print("add", plus);

    std::valarray<int> minus = a - b;
    print("minus", minus);

    std::valarray<int> multiply = a * b;
    print("multiply", multiply);

    std::valarray<int> divide = a / b;
    print("divide", divide);

    std::valarray<int> modulo = a % b;
    print("modulo", modulo);
  }
  std::cout << std::endl;

  // 数学関数
  // 全ての要素に同じ関数を適用する
  {
    std::valarray<float> a = {0.1f, 0.2f, 0.3f};

    std::valarray<float> sin = std::sin(a);
    print("sin", sin);

    std::valarray<float> cos = std::cos(a);
    print("cos", cos);
  }
  std::cout << std::endl;

  // 配列の一部に対して操作を行う
  {
    std::valarray<int> a = {1, 2, 3, 4, 5, 6};

    const std::size_t start = 1u;   // 開始位置
    const std::size_t length = 3u;  // 要素数
    const std::size_t stride = 2u;  // 何個置きに処理するか

    // {2, 4, 6}を抽出し、その全要素を* 2する
    a[std::slice(start, length, stride)] *= std::valarray<int>{2, 2, 2};

    print("slice + multiply", a);
  }
}