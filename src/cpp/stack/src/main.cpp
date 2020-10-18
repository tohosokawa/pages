#include <array>
#include <cassert>
#include <iostream>
#include <vector>

///////////////////////////////////////////////////////////////
/// Array
class MyArrayClass {
 public:
  void UseVariableLenMethod(int size) {
    std::cout << "Start UseVariableLenMethod(): " << size << std::endl;
    // This is Stack Memory
    uint8_t array[size];
    std::cout << "Finish UseVariableLenMethod(): " << size << std::endl;
    return;
  }
  void Use7MArrayMethod() {
    std::cout << "Start Use7MArrayMethod()" << std::endl;
    // This is Stack Memory
    std::array<uint8_t, 7 * 1024 * 1024> array;
    std::cout << "Finish Use7MArrayMethod()" << std::endl;
    return;
  }
  void Use8MArrayMethod() {
    std::cout << "Start Use8MArrayMethod()" << std::endl;
    // This is Stack Memory
    std::array<uint8_t, 8 * 1024 * 1024> array;
    std::cout << "Finish Use8MArrayMethod()" << std::endl;
    return;
  }

  void Use4MArrayMethod() {
    std::cout << "Start public Use4MArrayMethod()" << std::endl;
    // This is Stack Memory
    std::array<uint8_t, 4 * 1024 * 1024> array;
    use4MArrayMethod();
    std::cout << "Finish public Use4MArrayMethod()" << std::endl;
    return;
  }

 private:
  void use4MArrayMethod() {
    std::cout << "Start private use4MArrayMethod()" << std::endl;
    // This is Stack Memory
    std::array<uint8_t, 4 * 1024 * 1024> array;
    std::cout << "Finish private use4MArrayMethod()" << std::endl;
    return;
  }

  // Depends on construction way
  std::array<uint8_t, 8 * 1024 * 1024> array;
};

struct MyArrayStruct {
  // Depends on construction way
  std::array<uint8_t, 8 * 1024 * 1024> array;
};
///////////////////////////////////////////////////////////////
/// Vector
class MyVectorClass {
 public:
  MyVectorClass() : myVector(8 * 1024 * 1024){};
  void Use7MVectorMethod() {
    std::cout << "Start Use7MVectorMethod()" << std::endl;
    // This is Heap Memory
    std::vector<uint8_t> vector(7 * 1024 * 1024);
    std::cout << "Finish Use7MVectorMethod()" << std::endl;
    return;
  }
  void Use8MVectorMethod() {
    std::cout << "Start Use8MVectorMethod()" << std::endl;
    // This is Heap Memory
    std::vector<uint8_t> vector(8 * 1024 * 1024);
    std::cout << "Finish Use8MVectorMethod()" << std::endl;
    return;
  }

 private:
  // This is Heap memory
  std::vector<uint8_t> myVector;
};
///////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  std::cout << "Start" << std::endl;
  // It should be shown the following message when use stack memory over 8MB
  // Segmentation fault (core dumped)

  // This is Stack memory
  // std::array<uint8_t, 8 * 1024 * 1024> array8M;

  // This is Stack memory
  // MyArrayStruct myStruct;

  // This is Heap memory
  MyArrayStruct* myArrayStructPtr = new MyArrayStruct;
  delete myArrayStructPtr;

  // This is Stack memory
  // MyArrayClass myArrayClass;
  // This is Heap memory
  MyArrayClass* myArrayClassPtr = new MyArrayClass();
  std::cout << "Call myArrayClassPtr->Use7MArrayMethod()" << std::endl;
  myArrayClassPtr->Use7MArrayMethod();
  // std::cout << "Call myArrayClassPtr->Use8MArrayMethod()" << std::endl;
  // myArrayClassPtr->Use8MArrayMethod();
  // std::cout << "Call myArrayClassPtr->Use4MArrayMethod()" << std::endl;
  // myArrayClassPtr->Use4MArrayMethod();
  std::cout << "Call myArrayClassPtr->UseVariableLenMethod(7*1024*1024)"
            << std::endl;
  myArrayClassPtr->UseVariableLenMethod(7 * 1024 * 1024);
  std::cout << "Call myArrayClassPtr->UseVariableLenMethod(8*1024*1024)"
            << std::endl;
  myArrayClassPtr->UseVariableLenMethod(8 * 1024 * 1024);
  delete myArrayClassPtr;

  // This is Stack memory
  // MyVectorClass myVectorClass;
  // myVectorClass.Use7MVectorMethod();
  // myVectorClass.Use8MVectorMethod();

  // This is Heap memory
  // MyVectorClass* myVectorClassPtr = new MyVectorClass();
  // std::cout << "Call myVectorClassPtr->Use7MVectorMethod()" << std::endl;
  // myVectorClassPtr->Use7MVectorMethod();
  // std::cout << "Call myVectorClassPtr->Use8MVectorMethod()" << std::endl;
  // myVectorClassPtr->Use8MVectorMethod();
  // delete myVectorClassPtr;

  std::cout << "Finish" << std::endl;
  return 0;
}