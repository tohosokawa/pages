#include <cstring>
#include <memory>

#ifdef SAMPLE_DATA_SHARED
class Data {
 public:
  Data(int size) {
    mem = new char[size];
    std::memset(mem, 'x', size);
  };
  ~Data() { delete[] mem; }

 private:
  int size;
  char* mem;
};

class SampleData {
 public:
  SampleData(int size) { data = std::make_shared<Data>(size); };

 private:
  std::shared_ptr<Data> data;
};

#else   // not SAMPLE_DATA_SHARED
class SampleData {
 public:
  SampleData(int size) : size(size) {
    mem = new char[size];
    std::memset(mem, 'x', size);
  };
  SampleData(const SampleData& src) : size(src.size) {
    mem = new char[size];
    std::memcpy(mem, src.mem, size);
  }

  ~SampleData() { delete[] mem; }

 private:
  int size;
  char* mem;
};
#endif  // SAMPLE_DATA_SHARED