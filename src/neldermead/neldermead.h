#pragma once
#ifndef NELDER_MEAD_H_
#define NELDER_MEAD_H_
#include <assert.h>
#include <stdio.h>

//通用向量
template<size_t dim,typename T>
class Vector{
private:
    T _data[dim];
public:
    Vector(T nn=0){
        for(T& n : _data)
        {
            n=nn;
        }
    }

    explicit Vector(T* data){
       memcpy(_data,data,dim);
    }

    explicit Vector(const Vector& v){
         memcpy(_data,v._data,dim);
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

#endif//NELDER_MEAD_H_