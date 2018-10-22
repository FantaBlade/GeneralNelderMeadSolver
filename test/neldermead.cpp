#include "gtest.h"
#include "../src/neldermead/neldermead.h"


TEST(NelderMead,Vector){
    Vector<2,float> v1;
    EXPECT_EQ(v1[0],0);
    EXPECT_EQ(v1[1],0);

    Vector<2,float> v2(1);
    EXPECT_EQ(v2[0],1);
    EXPECT_EQ(v2[1],1);
}
