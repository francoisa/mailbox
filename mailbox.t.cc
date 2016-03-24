#include <map>
#include <memory>
#include "task.h"
#include "gtest/gtest.h"

using namespace std;

namespace {

class PrimeNumberGeneratorTest : public ::testing::Test {
  protected:

    PrimeNumberGeneratorTest() {
        // You can do set-up work for each test here.
    }

    virtual ~PrimeNumberGeneratorTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    virtual void SetUp() {
        // Code here will be called right before each test.
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test.
    }
};

TEST_F(PrimeNumberGeneratorTest, DoWork_0_Returns_1) {
    PrimeNumberGenerator png(0);
    EXPECT_EQ(1, png.do_work());
}

TEST_F(PrimeNumberGeneratorTest, DoWork_1_Returns_2) {
    PrimeNumberGenerator png(1);
    EXPECT_EQ(2, png.do_work());
}

TEST_F(PrimeNumberGeneratorTest, DoWork_2_Returns_3) {
    PrimeNumberGenerator png(2);
    EXPECT_EQ(3, png.do_work());
}

TEST_F(PrimeNumberGeneratorTest, DoWorkReturnsPrimes) {
    map<int, long long> primeMap;
    //primeMap[3] = 5;
    primeMap[4] = 7;
    primeMap[5] = 11;
    primeMap[6] = 13;
    primeMap[7] = 17;
    primeMap[8] = 19;
    primeMap[9] = 23;
    primeMap[10] = 29;
    for (auto p : primeMap) {
        unique_ptr<PrimeNumberGenerator> png(new PrimeNumberGenerator(p.first));
        EXPECT_EQ(p.second, png->do_work());
    }
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
