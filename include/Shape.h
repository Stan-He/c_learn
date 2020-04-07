#ifndef INCLUDE_SHAPE_H
#define INCLUDE_SHAPE_H
#include <iostream>
using namespace std;

class shape {

public:
    //shape();
    virtual ~shape(){};
};


class circle : public shape {
public: 
    ~circle() {
        puts("~circle()"); 
    }
};



class shape_wrapper{
    public:
        explicit shape_wrapper (shape* ptr=nullptr):ptr_(ptr){}
    
    ~shape_wrapper(){
        delete ptr_;
    }
    shape* get() const {return ptr_;}

    private:
        shape* ptr_;
        
};

/*进化，做一个智能指针，不止绑定在shape类上
1、指针行为
2、拷贝对象将引发异常
*/

//引用计数
class shared_count {
public: 
    shared_count():count_(1){}; 
    void add_count(){
        ++count_;
    }; 
    long reduce_count(){
        return --count_;
    }; 
    long get_count() const{
        return count_;
    };

private:
    long count_;
};



template <typename T>
class smart_ptr{
public:
    template<typename U>
    friend class smart_ptr;

    explicit smart_ptr (T* ptr=nullptr):ptr_(ptr){
        //引用计数的功能
        if (ptr){
            shared_count_ = new shared_count();
        }
    }

    //拷贝构造函数
    smart_ptr(const smart_ptr& other){
        ptr_=other.ptr_;
        if (ptr_){
            other.shared_count_->add_count();
            shared_count_=other.get_count();
        }
    }

    //拷贝子对象的情况
    template<typename U>
    smart_ptr(const smart_ptr<U>& other) noexcept{
        ptr_=other.ptr_;
        if (ptr_){
            other.shared_count_->add_count();
            shared_count_=other.shared_count_;
        }
    }

    
    //shared ptr之后就不需要了
    //smart_ptr(smart_ptr&& other){
    //    ptr_=other.release();
    //}
    

    //移动构造函数
    template <typename U>
    smart_ptr(smart_ptr<U>&& other) noexcept{
        ptr_=other.ptr_;
        if(ptr_){
            shared_count_ = other.shared_count_;
            other.ptr_=nullptr;
        }
        //ptr_=other.release();
    }

    template <typename U>
    smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept{
        ptr_=ptr;
        if(ptr_){
            other.shared_count_->add_count();
            shared_count_=other.get_count();
        }
    }

    ~smart_ptr(){
        if(ptr_ && !shared_count_->reduce_count()){
            delete ptr_;
            delete shared_count_;
        }
        
    }

    T* get() const noexcept {return ptr_;}
    T& operator*() const noexcept { return *ptr_;}
    T* operator->() const noexcept{ return ptr_;}
    operator bool() const noexcept{ return ptr_;}



    //重新定义等于，用等于传递之后，就不在拥有这个对象了
    smart_ptr& operator=(smart_ptr rhs) noexcept {
        rhs.swap(*this);
        return *this;
    }

    long use_count() const noexcept { 
        if (ptr_) { 
            return shared_count_ ->get_count(); 
        } else { 
            return 0; 
        } 
    }

    void swap(smart_ptr& rhs) noexcept { 
        using std::swap; 
        swap(ptr_, rhs.ptr_); 
        swap(shared_count_,rhs.shared_count_);
    }


private:
    T* ptr_;
    shared_count* shared_count_;

};

template <typename T,typename U> 
smart_ptr<T> static_pointer_cast( const smart_ptr<U>& other) noexcept{ 
    T* ptr = static_cast<T*>(other.get()); 
    return smart_ptr<T>(other, ptr);
}

template <typename T,typename U> 
smart_ptr<T> reinterpret_pointer_cast( const smart_ptr<U>& other) noexcept{
    T* ptr = reinterpret_cast<T*>(other.get()); 
    return smart_ptr<T>(other, ptr);
}

template <typename T,typename U> 
smart_ptr<T> const_pointer_cast( const smart_ptr<U>& other) noexcept{ 
    T* ptr = const_cast<T*>(other.get()); 
    return smart_ptr<T>(other, ptr);
}

template <typename T,typename U> 
smart_ptr<T> dynamic_pointer_cast( const smart_ptr<U>& other) noexcept{ 
    T* ptr = dynamic_cast<T*>(other.get()); 
    return smart_ptr<T>(other, ptr);
}






#endif
