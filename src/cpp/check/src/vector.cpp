#include <bits/stdint-uintn.h>
#include <iostream>
#include <vector>

class SampleClass {
 public:
  SampleClass(uint8_t in) : val(in), ival(1), fval(1), dval(1) {}
  SampleClass(int in) : val(1), ival(in), fval(1), dval(1) {}
  SampleClass(float in) : val(1), ival(1), fval(in), dval(1) {}
  SampleClass(double in) : val(1), ival(1), fval(1), dval(in) {}
  void print() {
    std::cout << "val: " << static_cast<unsigned int>(val) << ", ival: " << ival
              << ", fval: " << fval << ", dval: " << dval << std::endl;
  }

 private:
  uint8_t val;
  int ival;
  float fval;
  double dval;
};

struct SampleStruct {
  int foo;
  int bar;
  SampleStruct(int f, int b) : foo(f), bar(b) {}
};

int main(int argc, char** argv) {
  std::vector<SampleClass> SampleClassVector;
  SampleClassVector.push_back(0);
  SampleClassVector.emplace_back(0);
  for (auto itr = SampleClassVector.begin(); itr != SampleClassVector.end();
       ++itr) {
    itr->print();
  }

  std::vector<SampleClass> SampleClassVector2;
  SampleClassVector2.push_back(0);
  SampleClassVector2.emplace_back(SampleClassVector2[0]);
  for (auto itr = SampleClassVector2.begin(); itr != SampleClassVector2.end();
       ++itr) {
    itr->print();
  }

  std::vector<SampleClass> SampleClassVector3;
  SampleClassVector3.emplace_back(0);
  SampleClassVector3.push_back(SampleClassVector3[0]);
  for (auto itr = SampleClassVector3.begin(); itr != SampleClassVector3.end();
       ++itr) {
    itr->print();
  }

  std::vector<SampleStruct> SampleStructVector;
  SampleStructVector.push_back({123, 33});
  SampleStructVector.emplace_back(123, 33);

  return 0;
}