# 通用NelderMead解算器
##NelderMead方法是一种求解函数最值的数值方法，除了目标函数和启动参数外，不需要额外的参数。

    
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
        