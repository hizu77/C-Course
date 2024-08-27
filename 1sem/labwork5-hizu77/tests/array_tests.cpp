#include <lib/ThreeDArray.h>
#include <gtest/gtest.h>

TEST(ArrayTestSuite, DefaultTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    array[0][0][0] = 5;
    ASSERT_EQ(array[0][0][0], 5);
}

TEST(ArrayTestSuite, DefaultMultiTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    array[0][0][0] = 5;
    array[0][0][0] = 2;
    array[1][1][1] = 3;
    ASSERT_EQ(array[0][0][0], 2);
    ASSERT_EQ(array[1][1][1], 3);
}

TEST(ArrayTestSuite, DefaultValidTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    array[0][0][0] = 2;
    array[1][1][1] = 3;
    ASSERT_THROW(array[0][0][0] = -1, std::runtime_error);
}

TEST(ArrayTestSuite, DefaultValidMaxTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    array[0][0][0] = 2;
    array[1][1][1] = 3;
    ASSERT_THROW(array[0][0][0] = 10000000, std::runtime_error);
}

TEST(ArrayTestSuite, DefaultMultiArrayTest) {
    ThreeDArray array = ThreeDArray::make_array(2,2,2);
    int answers[8];
    int index = 0;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            for (size_t k = 0; k < 2; ++k) {
                array[i][j][k] = rand() % 100;
                answers[++index] = array[i][j][k];
            }
        }
    }
    index = 0;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            for (size_t k = 0; k < 2; ++k) {
                ASSERT_EQ(array[i][j][k], answers[++index]);
            }
        }
    }
}

TEST(ArrayTestSuite, DefaulMultiplierTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    ThreeDArray array2 = ThreeDArray::make_array(5, 5, 5);
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                int value = rand() % 10000;
                array[i][j][k] = value;
                array2[i][j][k] = 2 * value;
            }
        }
    }
    array = array * 2;
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                ASSERT_EQ(array[i][j][k], array2[i][j][k]);
            }
        }
    }
}

TEST(ArrayTestSuite, DefaulValidMultiplierTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    ThreeDArray array2 = ThreeDArray::make_array(5, 5, 5);
    ASSERT_THROW(array * (-2), std::runtime_error);
}

TEST(ArrayTestSuite, DefaultSumTest) {
    ThreeDArray array = ThreeDArray::make_array(5, 5, 5);
    ThreeDArray array2 = ThreeDArray::make_array(5, 5, 5);
    ThreeDArray array3 = ThreeDArray::make_array(5, 5, 5);
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                int value1 = rand() % 10000;
                int value2 = rand() % 10000;
                array[i][j][k] = value1;
                array2[i][j][k] = value2;
                array3[i][j][k] = value1 + value2;
            }
        }
    }
    ThreeDArray array_ans = array + array2;
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                ASSERT_EQ(array_ans[i][j][k], array3[i][j][k]);
            }
        }
    }
}

TEST(ArrayTestSuite, DefaultDifferenceTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    ThreeDArray array2 = ThreeDArray::make_array(5, 5, 5);
    ThreeDArray array3 = ThreeDArray::make_array(5, 5, 5);
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                int value1 = rand() % 10000;
                int value2 = rand() % 10000;
                if (value1 < value2) {
                    std::swap(value1, value2);
                }
                array[i][j][k] = value1;
                array2[i][j][k] = value2;
                array3[i][j][k] = value1 - value2;
            }
        }
    }
    ThreeDArray array_ans = array - array2;
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                ASSERT_EQ(array_ans[i][j][k], array3[i][j][k]);
            }
        }
    }
}

TEST(ArrayTestSuite, DefaultValidSumTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    ThreeDArray array2 = ThreeDArray::make_array(1, 1, 1);
    ASSERT_THROW(array2 + array, std::runtime_error);
}

TEST(ArrayTestSuite, DefaultValidDifferenceTest1) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    ThreeDArray array2 = ThreeDArray::make_array(1, 1, 1);
    ASSERT_THROW(array - array2, std::runtime_error);
}

TEST(ArrayTestSuite, DefaultValidDifferenceTest2) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    ThreeDArray array2 = ThreeDArray::make_array(5, 5, 5);
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            for (size_t k = 0; k < 5; ++k) {
                array2[i][j][k] = 5;
            }
        }
    }
    ASSERT_THROW(array - array2, std::runtime_error);
}

TEST(ArrayTestSuite, InputTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    std::istringstream input("32");
    auto input_ = array[0][0][0];
    input >> input_;
    ASSERT_EQ(array[0][0][0], 32);
}

TEST(ArrayTestSuite, OutputTest) {
    ThreeDArray array = ThreeDArray::make_array(5,5,5);
    std::stringstream output;
    array[0][0][0] = 1;
    output << array[0][0][0];
    ASSERT_EQ(output.str(), "1");
}

TEST(ArrayTestSuite, FullOutputTest) {
    ThreeDArray array = ThreeDArray::make_array(2,2,2);
    for (uint32_t x = 0; x < 2; ++x) {
        for (uint32_t y = 0; y < 2; ++y) {
            for (uint32_t z = 0; z < 2; ++z) {
                array[x][y][z] = 1;
            }
        }
    }
    std::stringstream output;
    output << array;
    ASSERT_EQ(output.str(), "1 1 \n1 1 \n\n1 1 \n1 1 \n\n");
}

TEST(ArrayTestSuite, FullInputTest) {
    ThreeDArray array = ThreeDArray::make_array(2,2,2);
    std::istringstream istream("1 1 1 1 1 1 1 1");
    std::stringstream output;
    istream >> array;
    output << array;
    ASSERT_EQ(output.str(), "1 1 \n1 1 \n\n1 1 \n1 1 \n\n");
}





