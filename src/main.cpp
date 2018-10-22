#include<iostream>
#include "neldermead/neldermead.h"

#include "gtest.h"

int main(int argc,char* argv[]){
    testing::InitGoogleTest(&argc,argv);
    int ret= RUN_ALL_TESTS();
    return 0;
}