#include "gtest.h"
#include "../src/neldermead/neldermead.h"
using namespace gnms;

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

    v3/=2;
    EXPECT_EQ(v3[0],1);
    v3+=v2;
    EXPECT_EQ(v3[0],3);

    auto v4=v3-v2;
    EXPECT_EQ(v4[0],1);

    v4=v4*4;
    EXPECT_EQ(v4[0],4);

    //std::cout<<v4<<std::endl;
}

TEST(NelderMead,Solver){
    Vector<1,float> v1(-20);
    Vector<1,float> v2(20);
    
    Vector<1,float> ret;
    
    std::vector<Vector<1,float>> startVecs;
    startVecs.push_back(v1);
    startVecs.push_back(v2);

   // NelderMeadSolver<2,float,float> sovler;
    float r= NelderMeadSolver<1, float, float>::evaluate(ret,startVecs,[&](const Vector<1,float>& n)->float{return n[0]*n[0];},500,0.001f);
    EXPECT_EQ(r,10);
}