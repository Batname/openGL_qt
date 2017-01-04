#include <gtest/gtest.h>
#include <iostream>

struct StructTestArray {
    int a;
    int b;
};

TEST(StructTest, StructTestArraySize) {
    StructTestArray s[] = {
        1, 2,
        3, 4,
        5, 6
    };
    
    EXPECT_EQ(4, *((int*)((StructTestArray*)s + 1) + 1));
}
