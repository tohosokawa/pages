# cpp-container

## コピーコンストラクタの実行タイミング

| container名 | メソッド | タイミング |
|---|---|:---|
|vector |emplace_back |capacityを超えてメモリの再確保が必要になったとき。 |
|vector |push_back | capacityを超えてメモリの再確保が必要になったとき。<br>メソッド実行時。 |
|deque |emplace_back | 発生しない。 |
|deque |push_back | メソッド実行時。 |

----------------------

Under construction.

## Add C++11

C++11 で追加されたもの

```cpp

#include <iostream>


int main(int argc, char* argv[]){
  std::cout << "Hello World" << std::endl;
  
  return 0;
}

```
