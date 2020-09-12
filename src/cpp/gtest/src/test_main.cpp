#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstddef>

#include "gtest/gtest.h"
using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

namespace {
// We will track memory used by this class.
class Water {
 public:
  // Normal Water declarations go here.

  // operator new and operator delete help us control water allocation.
  void* operator new(size_t allocation_size) {
    allocated_++;
    return malloc(allocation_size);
  }

  void operator delete(void* block, size_t /* allocation_size */) {
    allocated_--;
    free(block);
  }

  static int allocated() { return allocated_; }

 private:
  static int allocated_;
};

int Water::allocated_ = 0;

// This event listener monitors how many Water objects are created and
// destroyed by each test, and reports a failure if a test leaks some Water
// objects. It does this by comparing the number of live Water objects at
// the beginning of a test and at the end of a test.
class LeakChecker : public EmptyTestEventListener {
 private:
  // Called before a test starts.
  void OnTestStart(const TestInfo& /* test_info */) override {
    initially_allocated_ = Water::allocated();
    printf("OnTestStart\n");
  }

  // Called after a test ends.
  void OnTestEnd(const TestInfo& /* test_info */) override {
    int difference = Water::allocated() - initially_allocated_;

    // You can generate a failure in any event handler except
    // OnTestPartResult. Just use an appropriate Google Test assertion to do
    // it.
    EXPECT_LE(difference, 0) << "Leaked " << difference << " unit(s) of Water!";
    printf("OnTestEnd\n");
  }

  int initially_allocated_;
};

void showMallInfo(struct mallinfo info) {
  printf("-----------------------------------------\n");
  printf("Total non-mmapped bytes (arena):       %d\n", info.arena);
  printf("# of free chunks (ordblks):            %d\n", info.ordblks);
  printf("# of free fastbin blocks (smblks):     %d\n", info.smblks);
  printf("# of mapped regions (hblks):           %d\n", info.hblks);
  printf("Bytes in mapped regions (hblkhd):      %d\n", info.hblkhd);
  printf("Max. total allocated space (usmblks):  %d\n", info.usmblks);
  printf("Free bytes held in fastbins (fsmblks): %d\n", info.fsmblks);
  printf("Total allocated space (uordblks):      %d\n", info.uordblks);
  printf("Total free space (fordblks):           %d\n", info.fordblks);
  printf("Topmost releasable block (keepcost):   %d\n", info.keepcost);
  printf("-----------------------------------------\n");
}

class MallChecker : public EmptyTestEventListener {
 private:
  // Called before a test starts.
  void OnTestStart(const TestInfo& /* test_info */) override {
    printf("OnTestStart\n");
    ini_info_ = mallinfo();
    // showMallInfo(ini_info_);
  }
  // Called after a test ends.
  void OnTestEnd(const TestInfo& /* test_info */) override {
    auto end_info = mallinfo();
    showMallInfo(end_info);
    // printf("OnTestEnd\n");
  }

  struct mallinfo ini_info_;
};

TEST(ListenersTest, DoesNotLeak) {
  showMallInfo(mallinfo());
  Water* water = new Water;
  delete water;
  showMallInfo(mallinfo());
}

// This should fail when the --check_for_leaks command line flag is
// specified.
TEST(ListenersTest, LeaksWater) {
  showMallInfo(mallinfo());
  Water* water = new Water;
  //   EXPECT_TRUE(water != nullptr);
  showMallInfo(mallinfo());
  delete water;
  showMallInfo(mallinfo());
}

TEST(ListenersTest, LeaksMalloc) {
  showMallInfo(mallinfo());
  //   malloc_stats();
  char* mem = nullptr;
  mem = static_cast<char*>(malloc(1024));
  //   EXPECT_TRUE(water != nullptr);
  showMallInfo(mallinfo());
  //   malloc_stats();
  free(mem);
  mem = nullptr;
  //   malloc_stats();
  showMallInfo(mallinfo());
}

TEST(ListenersTest, LeaksMalloc2) {
  //   size_t s = 1024 * 1;
  //   size_t s = 1024 + 9;
  size_t s = 1024 - 7;
  auto ini = mallinfo();
  showMallInfo(ini);

  char* mem = nullptr;
  mem = static_cast<char*>(malloc(s));
  memset(mem, 0, s * 1);
  //   free(mem);

  auto end = mallinfo();
  showMallInfo(end);
  auto mused = (end.uordblks - ini.uordblks) + (end.hblkhd - ini.hblkhd);

  printf("Requested size %zu, used space %d, overhead %zu\n", s, mused,
         mused - s);
}

TEST(ListenersTest, LeaksNew) {
  //   size_t s = 1024 * 1;
  //   size_t s = 8 * 8;
  size_t s = 32 * 3;
  auto ini = mallinfo();
  showMallInfo(ini);

  char* mem = new char[s];
  memset(mem, 0, s * 1);
  //   delete[] mem;

  auto end = mallinfo();
  showMallInfo(end);
  auto mused = (end.uordblks - ini.uordblks) + (end.hblkhd - ini.hblkhd);

  printf("Requested size %zu, used space %d, overhead %zu\n", s, mused,
         mused - s);
}

}  // namespace

int main(int argc, char** argv) {
  InitGoogleTest(&argc, argv);

  bool check_for_leaks = false;
  if (argc > 1 && strcmp(argv[1], "--check_for_leaks") == 0)
    check_for_leaks = true;
  else
    printf("%s\n",
           "Run this program with --check_for_leaks to enable "
           "custom leak checking in the tests.");

  // If we are given the --check_for_leaks command line flag, installs the
  // leak checker.
  if (check_for_leaks) {
    TestEventListeners& listeners = UnitTest::GetInstance()->listeners();

    listeners.Append(new LeakChecker);
    listeners.Append(new MallChecker);
  }
  return RUN_ALL_TESTS();
}