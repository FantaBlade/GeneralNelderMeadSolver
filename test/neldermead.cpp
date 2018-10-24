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

TEST(NelderMead,1D_Function){
    Vector<1,float> v1(40);
    Vector<1,float> v2(20);
    
    Vector<1,float> ret;
    
    std::vector<Vector<1,float>> startVecs;
    startVecs.push_back(v1);
    startVecs.push_back(v2);

   // NelderMeadSolver<2,float,float> sovler;
    //2D抛物线 y=x^2
    float r= NelderMeadSolver<1, float, float>::evaluate(ret,startVecs,[&](const Vector<1,float>& n)->float{return n[0]*n[0];},500,0.001f);
    EXPECT_EQ(r,0);
    //指数函数 y=e^x
    float r2=NelderMeadSolver<1, float, float>::evaluate(ret,startVecs,[&](const Vector<1,float>& n)->float{return std::exp(n[0]);},500,0.001f);
    EXPECT_EQ(r2,0);
    //对数函数y=log_e(x)
    float r3=NelderMeadSolver<1, float, float>::evaluate(ret,startVecs,[&](const Vector<1,float>& n)->float{return std::log(n[0]);},500,0.001f);
	EXPECT_EQ(r3, -std::numeric_limits<float>::infinity());

}


TEST(NelderMead, 1D_Function_Native) {
	float v1 = 40;
	float v2 = 20;

	float ret;

	float inits[] = { v1,v2 };
	//2D抛物线 y=x^2
	float r = NelderMeadSolver<1,float, float>::evaluate(&ret,inits,[&](const float *n)->float{return n[0] * n[0]; },500,0.001f);
	EXPECT_EQ(r, 0);
	//指数函数 y=e^x
	float r2 = NelderMeadSolver<1, float, float>::evaluate(&ret, inits, [&](const float *n)->float {return std::exp(n[0]); }, 500, 0.001f);
	EXPECT_EQ(r2, 0);
	//对数函数y=log_e(x)
	float r3 = NelderMeadSolver<1, float, float>::evaluate(&ret, inits, [&](const float *n)->float {return std::log(n[0]); }, 500, 0.001f);
	EXPECT_EQ(r3, -std::numeric_limits<float>::infinity());
}

TEST(NelderMead, 2D_Function) {
	/*float v1[2] = {40,40};
	float v2[2] = { -40,80 };
	float v3[2] = { 2,-30 };*/
	float ret[2];
	float inits[6] = { 40,40/*v1*/,-40,80/*v2*/, 2,-30/*v3*/ };
	//3D抛物体 z=x^2+y^2
	float r = NelderMeadSolver<2, float, float>::evaluate(ret, inits, [&](const float *n)->float {return n[0] * n[0]+ n[1] * n[1]; }, 500, 0.001f);
	EXPECT_EQ(r, 0);
	//3D指数函数 y=e^(x+y）
	float r2 = NelderMeadSolver<2, float, float>::evaluate(ret, inits, [&](const float *n)->float {return std::exp(n[0] + n[1]); }, 500, 0.001f);
	EXPECT_EQ(r2, 0);
	//3D对数函数y=log_e(x+y)
	float r3 = NelderMeadSolver<2, float, float>::evaluate(ret, inits, [&](const float *n)->float {return std::log(n[0] + n[1]); }, 500, 0.001f);
	EXPECT_EQ(r3, -std::numeric_limits<float>::infinity());

}