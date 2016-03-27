#pragma once
namespace QND
{

// class template for a simple unique pointer
// requires C++11 features
template<typename T>
class UniquePtr final
{
public:
    UniquePtr(T* rawPtr = nullptr)
        :_ptr(rawPtr) {  }

    ~UniquePtr() noexcept
    {
        if(_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }

    //copy ctor
    UniquePtr(const UniquePtr<T>& other)
    {
        if(other._ptr)
        {
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
    }

    //assignment operator
    UniquePtr<T>& operator = (const UniquePtr<T>& other)
    {
        if(*this != other)
        {
            if(_ptr)
            {
                delete _ptr;
                _ptr = nullptr;
            }
            if(other._ptr)
            {
                _ptr = other._ptr;
                other._ptr = nullptr;
            }
        }
        return *this;
    }

    // transparently forward address of underlying pointer
    T* operator &() const {return _ptr;}

    // deref operator
    T& operator *()  const {return *_ptr;}

    // arrow (member func/var access) operator
    T* operator ->() const {return _ptr;}

    // conversion operator to boolean
    operator bool() const {return _ptr != nullptr;} 

    // equality operator
    bool operator == (const UniquePtr<T>& other) const {return _ptr == other._ptr;}
    bool operator != (const UniquePtr<T>& other) const {return _ptr != other._ptr;}

    // get underlying pointer without giving up ownership
    T* get(void) const { return _ptr;}

    // return underlying pointer giving up ownership
    T* release(void) { T* temp=_ptr; _ptr=nullptr; return temp;}

    // reassign
    void reset(T* otherPtr=nullptr)
    {
        if(_ptr) delete _ptr; 
        _ptr = otherPtr;
    }

private:
    // raw pointer to be managed
    mutable T* _ptr; 
};

}
