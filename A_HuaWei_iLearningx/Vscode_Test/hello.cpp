#include<iostream>
#include<vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <string.h>
#include <array>
using namespace std;

class Shape{
public:
    Shape(){}
    Shape(int w,int h):weight(w),hight(h){}
    ~Shape(){
        cout<<"~Shape  析构"<<endl;
    }
    void GetShape(){
        cout<<"weight="<<weight<<endl;
        cout<<"hight="<<hight<<endl;
    }
private:
    int weight;
    int hight;
};


template <typename T>
class smart_ptr{
public:
    //构造函数
    explicit smart_ptr(T* ptr = nullptr):ptr_(ptr){}
    //禁用拷贝和赋值
    smart_ptr(const smart_ptr&) = delete;
    smart_ptr& operator=(const smart_ptr&) = delete;

    // smart_ptr(smart_ptr& other){
    //     ptr_=other.release();
    //     cout<<"smart_ptr(smart_ptr& other)"<<endl;
    // }
    // smart_ptr& operator=(smart_ptr& rhs){
    //     //构造新的smart_ptr对象与this对象交换，
    //     smart_ptr(rhs).swap(*this);    //拷贝(移动)+交换 的惯用 ，是一种标准的、能够保证异常安全的惯用方法
    //     cout<<"smart_ptr& operator=(smart_ptr& rhs)"<<endl;
    //     return *this;
    // }
    //移动构造函数
    smart_ptr(smart_ptr&& other){
        ptr_=other.release();
        cout<<"smart_ptr(smart_ptr&& other)"<<endl;
    }
    smart_ptr& operator=(smart_ptr rhs){
        //构造新的smart_ptr对象与this对象交换，
        rhs.swap(*this);    //拷贝(移动)+交换 的惯用 ，是一种标准的、能够保证异常安全的惯用方法
        cout<<"smart_ptr& operator=(smart_ptr rhs)"<<endl;
        return *this;
    }

    template <typename U>
    smart_ptr(smart_ptr<U>&& other){
        ptr_ = other.release();
    }

    T& operator*() const {return *ptr_;}
    T* operator->() const {return ptr_;}
    operator bool() const {return ptr_;}
    ~smart_ptr(){
        delete ptr_;
    }
    T* get() const{
        return ptr_;
    }
private:
    T* ptr_;
    //u.release()   u 放弃对指针的控制权，返回指针，并将 u 置为空
    T* release(){
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& rhs){
        using std::swap;
        swap(ptr_,rhs.ptr_);
    }
};


class shared_count{
public:
    long use_count_;
public:
    shared_count(long count = 1):use_count_(count){}
    long add_count(){
        ++use_count_;
        return use_count_;
    }
    long reduce_count(){
        --use_count_;
        return use_count_;
    }
};


template <typename T>
class shared_smart_ptr:public shared_count{
public:
    explicit shared_smart_ptr(T*ptr = nullptr): ptr_(ptr){
        if(ptr)
            share_count_ = new shared_count();
    }

    /**
    除了要提供模板化的"拷贝构造"以外，还要提供一个非模板的拷贝构造
    原因：C++认为模板化的"拷贝构造"不是真正的拷贝构造函数，因此会默认提供一个拷贝构造函数，但这个函数是错的，不会进行引用计数的修改
    因此，必须实现一个非模板的拷贝构造函数
    但，并不需要提供一个非模板的移动构造
    原因：C++规则，如果提供了拷贝构造函数，编译器便默认不会提供移动构造，这时候，模板化的移动构造便成为提供右值引用的最佳匹配
     */
    shared_smart_ptr(const shared_smart_ptr &other){
        ptr_ = other.ptr_;
        if(ptr_){
            other.share_count_->add_count();
            share_count_ = other.share_count_;
        }
    }

    //模板化的"拷贝构造"
    template <typename U>
    shared_smart_ptr(const shared_smart_ptr<U> &other){
        ptr_ = other.ptr_;
        if(ptr_){
            other.share_count_->add_count();
            share_count_ = other.share_count_;
        }
    }

    //模板化的移动构造函数
    template <typename U>
    shared_smart_ptr(shared_smart_ptr<U> && other) noexcept{
        ptr_ = other.ptr_;
        if(ptr_){
            share_count_ = other.share_count_; //先把引用计数的指针先拿过来
            other.ptr_=nullptr;
        }
    }

    T& operator*() const {return *ptr_;}
    T* operator->() const {return ptr_;}
    operator bool() const {return ptr_;}

    ~shared_smart_ptr(){
        if(ptr_ && !share_count_->reduce_count()){
            delete ptr_;
            delete share_count_;
        }
    }

public:
    shared_count* share_count_;
private:
    T* ptr_;
    void relese(){
        if((--share_count_->use_count_)==0){
            delete ptr_;
            delete share_count_;
        }
    }
};

template<typename T, typename... Args>
shared_smart_ptr<T> make_shared_wmy(Args&&... args){
    shared_smart_ptr<T> ret(new T(forward<Args>(args)...));
    return ret;
}

int main0()
{
    shared_smart_ptr<Shape> s(new Shape(1,2));
    s->GetShape();
    cout<<"s.use_count_ = "<<s.share_count_->use_count_<<endl;

    {
        shared_smart_ptr<Shape> s2 = s;
        s2->GetShape();
        cout<<"s2.use_count_ = "<<s2.share_count_->use_count_<<endl;
    }
    
    cout<<"s.use_count_ = "<<s.share_count_->use_count_<<endl;

    auto a = make_shared_wmy<Shape>(3,4);

    return 0;
}

int main()
{
    int a[5];
    cout<<size(a)<<endl;
}