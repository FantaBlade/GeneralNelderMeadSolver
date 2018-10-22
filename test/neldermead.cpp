#include "gtest.h"
#include "../src/neldermead/neldermead.h"


TEST(NelderMead,Vector){
    Vector<2,float> v1;
    EXPECT_EQ(v1[0],0);
    EXPECT_EQ(v1[1],0);

    Vector<2,float> v2(1);
    EXPECT_EQ(v2[0],1);
    EXPECT_EQ(v2[1],1);

    v2[0]=2;
    EXPECT_EQ(v2[0],2);

    Vector<2,float> v3(v2);
     EXPECT_EQ(v3[0],2);
}

TEST(NelderMead,Solver){
    Vector<2,float> v1(1);
    Vector<2,float> v2(2);
    Vector<2,float> v3(3);
    Vector<2,float> ret;
    
    std::vector<Vector<2,float>> startVecs;
    startVecs.push_back(v1);
    startVecs.push_back(v2);
    startVecs.push_back(v3);

   // NelderMeadSolver<2,float,float> sovler;
    float r= NelderMeadSolver<2, float, float>::evaluate(ret,startVecs,[&](const Vector<2,float>& n)->float{return n[0]+n[1];},1,0.001f);
    EXPECT_EQ(r,10);
}