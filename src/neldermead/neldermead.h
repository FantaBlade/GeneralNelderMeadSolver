#pragma once
#ifndef NELDER_MEAD_H_
#define NELDER_MEAD_H_
#include <assert.h>
#include <functional>
#include <vector>

//通用向量
template<size_t dim,typename T>
class Vector{
private:
    T _data[dim];
public:
   explicit Vector(T nn=0){
        for(auto& n : _data)
        {
            n=nn;
        }
    }

    explicit Vector(T* data,size_t start){
       memcpy(_data,data+start,dim*sizeof(T));
    }

    explicit Vector(const Vector& v){
         memcpy(_data,v._data,dim*sizeof(T));
    }
    
    Vector& operator =(const Vector& v){
         memcpy(_data,v._data,dim*sizeof(T));
         return (*this);
    }
    
    T operator[](int index) const{
       assert(index>=0&&index<dim);
       return _data[index];
    }

    T& operator[](int index){
        assert(index>=0&&index<dim);
       return _data[index];
    }
};

//常用基本类型
template <size_t dim>
using Vectorf = Vector<dim,float>;
template <size_t dim>
using Vectord = Vector<dim,double>;
template <size_t dim>
using Vectori = Vector<dim,int>;


//通用NelderMead解算器
//dim : 目标函数的参数维度
//T :   目标函数的参数类型，只能为基本类型[float ,double ,int等]
//U :   目标函数的返回值类型，只能为基本类型[float ,double ,int等]
template<size_t dim,typename T,typename U>
class NelderMeadSolver{
private:
    
public:
    static U evaluate(Vector<dim,T>& result,const std::vector<Vector<dim,T>>& startVecs,const std::function<U(const Vector<dim,T>&)>& func,size_t iterationCount,U tolerance);
};


template<size_t dim,typename T,typename U>
U NelderMeadSolver<dim,T,U>::evaluate(Vector<dim,T>& result,const std::vector<Vector<dim,T>>& startVecs,const std::function<U(const Vector<dim,T>&)>& func,size_t iterationCount,U tolerance){
        assert(startVecs.size()==(dim+1));
        
        size_t VecNum=dim+1;
        //存放函数值
        std::vector<U> funcValues(VecNum);
        for(size_t i=0;i<startVecs.size();++i){
            funcValues[i]=func(startVecs[i]);
        }

        T low;//当前最小值
        T high;//当前最大值
        T subHigh;//当前次最大值

        for(size_t i=0;i<iterationCount;++i){
          
        }

        return func(startVecs[0]);
}


template <size_t dim>
using NelderMeadSolverf = NelderMeadSolver<dim,float,float>;
template <size_t dim>
using NelderMeadSolverd = NelderMeadSolver<dim,double,double>;
template <size_t dim>
using NelderMeadSolveri = NelderMeadSolver<dim,int,int>;

#endif//NELDER_MEAD_H_