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

/*��������һ������ָ�룬��ֹ����shape����
1��ָ����Ϊ
2���������������쳣
*/

//���ü���
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
        //���ü����Ĺ���
        if (ptr){
            shared_count_ = new shared_count();
        }
    }

    //�������캯��
    smart_ptr(const smart_ptr& other){
        ptr_=other.ptr_;
        if (ptr_){
            other.shared_count_->add_count();
            shared_count_=other.get_count();
        }
    }

    //�����Ӷ�������
    template<typename U>
    smart_ptr(const smart_ptr<U>& other) noexcept{
        ptr_=other.ptr_;
        if (ptr_){
            other.shared_count_->add_count();
            shared_count_=other.shared_count_;
        }
    }

    
    //shared ptr֮��Ͳ���Ҫ��
    //smart_ptr(smart_ptr&& other){
    //    ptr_=other.release();
    //}
    

    //�ƶ����캯��
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



    //���¶�����ڣ��õ��ڴ���֮�󣬾Ͳ���ӵ�����������
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
