#include <gtest/gtest.h>
#include <matrix.hpp>
#include <test_utility.hpp>

using ::testing::Combine;
using ::testing::Test;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

// FIXME: MinGW-GCC v12.0.1 x64 doesn't work with these parametrized tests by some reason
// Update: WSL-GCC v11.2.0 x64 works just fine

#if (!__MINGW64__ || __clang__)

class GeneratorUnitTest: public TestWithParam<std::tuple<uint32_t, uint32_t>> {
public:
    uint32_t Columns = 8;
    uint32_t Rows = 8;
    GeneratorUnitTest() = default;

    ~GeneratorUnitTest() override = default;

    void SetUp() override {
        auto Pair = GetParam();
        Rows = std::get<0>(Pair);
        Columns = std::get<1>(Pair);
    };

    void TearDown() override {};
};

TEST_P(GeneratorUnitTest, A) {
    matrix MyMatrix(Rows, Columns);
    matrix::generator::A(MyMatrix);

    ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
            << " Matrix is: " << Rows << "x" << Columns;
}

TEST_P(GeneratorUnitTest, B) {
    matrix MyMatrix(Rows, Columns);
    matrix::generator::B(MyMatrix);

    ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
            << " Matrix is: " << Rows << "x" << Columns;
}

TEST_P(GeneratorUnitTest, C) {
    matrix MyMatrix(Rows, Columns);
    matrix::generator::C(MyMatrix);

    ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
            << " Matrix is: " << Rows << "x" << Columns;
}

TEST_P(GeneratorUnitTest, Default) {
    matrix MyMatrix(Rows, Columns);

    ASSERT_TRUE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
            << " Matrix is: " << Rows << "x" << Columns;
}

TEST_P(GeneratorUnitTest, WrongMatrix) {
    matrix MyMatrix(Rows, Columns);
    MyMatrix[0][0] = 1000;

    ASSERT_FALSE(MatrixIsInCorrectOrder(MyMatrix, Rows, Columns))
            << " Matrix is: " << Rows << "x" << Columns;
}

constexpr uint32_t RowsSet[] = {2, 9, 10, 11, 49, 50, 51, 99, 100, 101, 249, 250, 251};
constexpr uint32_t ColumnsSet[] = {2, 9, 10, 11, 49, 50, 51, 99, 100, 101, 249, 250, 251};

INSTANTIATE_TEST_SUITE_P(Generator,
                         GeneratorUnitTest,
                         Combine(ValuesIn(RowsSet),
                                 ValuesIn(ColumnsSet)),
                         [](const testing::TestParamInfo<GeneratorUnitTest::ParamType>& info) -> std::string {
                             std::string TestCaseName;
                             TestCaseName.reserve(16);

                             TestCaseName.append(std::to_string(std::get<0>(info.param)));
                             TestCaseName.append("x");
                             TestCaseName.append(std::to_string(std::get<1>(info.param)));

                             TestCaseName.shrink_to_fit();
                             return TestCaseName;
                         });

#endif