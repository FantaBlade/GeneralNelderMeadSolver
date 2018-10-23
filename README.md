# 通用NelderMead解算器
## NelderMead方法是一种求解函数最值的数值方法，除了目标函数和启动参数外，不需要额外的参数。
# 使用方法
## 头文件
#### neldermead.h
### 命名空间
#### ```using namespace gnms;```
#### ```gnms::Vector<...>```
### 初始化一个1维float数据向量
#### ```gnms::Vector<1,float> v;```
#### ```v[0]=1.0f;```
### 初始化一个3维float数据向量
#### ```gnms::Vector<3,float> v;```
#### ```v[0]=1.0f;```
#### ```v[1]=1.0f;```
#### ```v[2]=1.0f;```
### 初始化一个N维float数据向量
#### ```gnms::Vector<N,float> v;```
#### ```v[0]=1.0f;```
#### ```v[1]=1.0f;```
#### ```v[2]=1.0f;```
#### ```...```
#### ```v[N-1]=1.0f;```
### 还可以使用内置类型版本 
#### ```gnms::Vectorf<3> v;//float 类型```
#### ```gnms::Vectord<3> v;//double 类型```
#### ```gnms::Vectori<3> v;//int 类型```