#pragma once
#ifndef NELDER_MEAD_H_
#define NELDER_MEAD_H_
#include <assert.h>
#include <functional>
#include <vector>
//#include <iostream>
namespace gnms {
	//通用向量
	template<size_t dim, typename T>
	class Vector {
	private:
		T _data[dim];
	public:
		explicit Vector(T nn = 0) {
			for (auto& n : _data)
			{
				n = nn;
			}
		}

		explicit Vector(const T* data, size_t start) {
			memcpy(_data, data + start, dim * sizeof(T));
		}

		Vector(const Vector& v) {
			memcpy(_data, v._data, dim * sizeof(T));
		}

		Vector& operator =(const Vector& v) {
			memcpy(_data, v._data, dim * sizeof(T));
			return (*this);
		}

		T operator[](int index) const {
			assert(index >= 0 && index < dim);
			return _data[index];
		}

		T& operator[](int index) {
			assert(index >= 0 && index < dim);
			return _data[index];
		}
        friend Vector operator+(const Vector& v1,const Vector& v2){
            Vector v;
             for(int i=0;i<dim;++i){
                v._data[i]=v1._data[i]+v2._data[i];
            }
            return v;
        }
        Vector& operator+=(const Vector& v){
            for(int i=0;i<dim;++i){
                _data[i]+=v._data[i];
            }
            return (*this);
        }
        friend Vector operator-(const Vector& v1,const Vector& v2){
            Vector v;
             for(int i=0;i<dim;++i){
                v._data[i]=v1._data[i]-v2._data[i];
            }
            return v;
        }
        friend Vector operator*(const Vector& v1,T f){
            Vector v;
             for(int i=0;i<dim;++i){
                v._data[i]=v1._data[i]*f;
            }
            return v;
        }
        friend Vector operator*(T f,const Vector& v1){
            return v1*f;
        }

        Vector& operator/=(T f){
             for(int i=0;i<dim;++i){
                _data[i]/=f;
            }
            return (*this);
        }
        
        friend std::ostream& operator <<(std::ostream& out,const Vector& v){
            out<<"[";
            for (auto& n : v._data)
			{
				 out<<n<<" ";
			}
            out<<"]";
            return out;
        }

        const T* c_ptr() const{
            return _data;
        } 

        void copy(T *ptr) const{
            std::memcpy(ptr,_data,dim*sizeof(T));
        }
	};

	//常用基本类型
	template <size_t dim>
	using Vectorf = Vector<dim, float>;
	template <size_t dim>
	using Vectord = Vector<dim, double>;
	template <size_t dim>
	using Vectori = Vector<dim, int>;


	//通用NelderMead解算器
	//dim : 目标函数的参数维度
	//T :   目标函数的参数类型，只能为基本类型[float ,double ,int等]
	//U :   目标函数的返回值类型，只能为基本类型[float ,double ,int等]
	template<size_t dim, typename T, typename U>
	class NelderMeadSolver {
	private:

	public:
		static U evaluate(Vector<dim, T>& result, const std::vector<Vector<dim, T>>& startVecs, const std::function<U(const Vector<dim, T>&)>& func, size_t iterationCount, U tolerance,float reflect=1,float expand=2,float contract=0.5f,float shrink=0.5f);
		static U evaluate(T*  result, const T*  startVecs, const std::function<U(const T *)>& func, size_t iterationCount, U tolerance,float reflect=1,float expand=2,float contract=0.5f,float shrink=0.5f);
	};


	template<size_t dim, typename T, typename U>
	U NelderMeadSolver<dim, T, U>::evaluate(Vector<dim, T>& result, const std::vector<Vector<dim, T>>& startVecs, const std::function<U(const Vector<dim, T>&)>& func, size_t iterationCount, U tolerance,float reflect,float expand,float contract,float shrink) {
		assert(startVecs.size() == (dim + 1));
        //复制一份向量拷贝
        auto vectors= std::vector<Vector<dim, T>>(startVecs);

		size_t VecNum = dim + 1;
		//存放函数值
		std::vector<U> funcValues(VecNum);
		for (size_t i = 0; i < VecNum; ++i) {
			funcValues[i] = func(vectors[i]);
		}

		int low=0;//当前最小值
		int high=0;//当前最大值
		int subHigh=0;//当前次最大值

		for (size_t i = 0; i < iterationCount; ++i) {
            //计算当前的最大值，最小值以及次最大值
            for(int j=0;j<VecNum;++j){
                if(funcValues[j]<funcValues[low]){
                    low=j;
                }
                else if(funcValues[j]>funcValues[high]){
                    subHigh=high;
                    high=j;
                }
                else if(funcValues[j]>funcValues[subHigh]){
                    subHigh=j;
                }
            }
            //计算阈值
            //这里使用abs的原因是U可能是int类型之类的整形
            U a=std::abs(funcValues[low]);
            U b=std::abs(funcValues[high]);
            // if(2*std::abs(a-b)<tolerance*(a+b)){
            //     break;
            // }
            //计算除了最大向量外，其他向量的中心向量
            Vector<dim, T> o(0);
            for(int j=0;j<VecNum;++j){
                if(j==high){
                    //跳过最大
                    continue;
                }
                o+=vectors[j];
            }
            o/=dim;

            //反射 reflection
           auto r=o+reflect*(o-vectors[high]);
           U r_fv=func(r);

           if(r_fv<funcValues[subHigh]){
               if(r_fv<funcValues[low]){
                   //扩张 expansion
                    auto e=o+expand*(r-o);
                    U e_fv=func(e);
                    if(e_fv<r_fv){
                        funcValues[high]=e_fv;
                        vectors[high]=e;
                        continue;
                    }
                   
               }
                //反射(这里包括了(r_fv<funcValues[low])以及(r_fv>funcValues[low])两种情况
                funcValues[high]=r_fv;
                vectors[high]=r;
                continue;
           }
           //r_fv>funcValues[subHigh]
           //收缩
           auto c=o+contract*(vectors[high]-o);
           U c_fv=func(c);
           if(c_fv< funcValues[high]){
                funcValues[high]=c_fv;
                vectors[high]=c;
                continue;
           }

           //shrink
           for(int j=0;j<VecNum;++j){
               if(j==low){
                   continue;
               }
               vectors[j]=o+shrink*(vectors[j]-o);
               funcValues[j]=func(vectors[j]);
           }
		}

        result=vectors[low];
		return funcValues[low];
	}

    template<size_t dim, typename T, typename U>
    U NelderMeadSolver<dim, T, U>::evaluate(T*  result, const T*  startVecs, const std::function<U(const T *)>& func, size_t iterationCount, U tolerance,float reflect=1,float expand=2,float contract=0.5f,float shrink=0.5f){
        Vector<dim, T> r;
        std::vector< Vector<dim, T> > s;
        for(int i=0;i<dim+1;++i){
			Vector<dim, T>  v(startVecs, i*dim);
            s.push_back(v);
        }
		U rr = evaluate(r, s, [&](const Vector<dim, T>& a) -> U{ return func(a.c_ptr()); }, iterationCount, tolerance, reflect, expand, contract, shrink);
        r.copy(result);
        return rr;
    }
    
    

	template <size_t dim>
	using NelderMeadSolverf = NelderMeadSolver<dim, float, float>;
	template <size_t dim>
	using NelderMeadSolverd = NelderMeadSolver<dim, double, double>;
	template <size_t dim>
	using NelderMeadSolveri = NelderMeadSolver<dim, int, int>;
};



#endif//NELDER_MEAD_H_