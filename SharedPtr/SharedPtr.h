#pragma once
namespace QND
{

// class template for a simple shared pointer
// requires C++11 features
template<typename T>
class SharedPtr final
{
public:
    SharedPtr(T* rawPtr = nullptr)
        :_ptr(rawPtr) {  _refCnt = new unsigned int{1}; }

    ~SharedPtr() noexcept
    {
        if(_ptr && (--(*_refCnt) == 0))
        {
            delete _ptr;
            _ptr = nullptr;
            delete _refCnt;
            _refCnt = nullptr;
        }
    }

    //copy ctor
    SharedPtr(const SharedPtr<T>& other)
    {
        if(other._ptr)
        {
            _ptr = other._ptr;
            _refCnt = other._refCnt;
            ++(*_refCnt);
        }
    }

    //assignment operator
    SharedPtr<T>& operator = (const SharedPtr<T>& other)
    {
        if(*this != other)
        {
            if(_ptr)
            {
                --(*_refCnt);
                _refCnt = nullptr;
                _ptr = nullptr;
            }
            if(other._ptr)
            {
                _ptr = other._ptr;
                _refCnt = other._refCnt;
                ++(*_refCnt);
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
    bool operator == (const SharedPtr<T>& other) const {return _ptr == other._ptr;}
    bool operator != (const SharedPtr<T>& other) const {return _ptr != other._ptr;}

    // get underlying pointer without giving up ownership
    T* get(void) const { return _ptr;}

    // return underlying pointer giving up ownership
    T* release(void) { T* temp=_ptr; _ptr=nullptr; --(*_refCnt); _refCnt=nullptr; return temp;}

    // reassign
    void reset(T* otherPtr=nullptr)
    {
        if(_ptr)
        {
            _ptr = nullptr;
            --(*_refCnt);
            _refCnt = nullptr;
        }

        if(otherPtr)
        {
            _ptr = otherPtr;
            _refCnt = new unsigned int {1};
        }
    }

    // get current reference count
    unsigned int getRefCount() { return _refCnt ? *_refCnt : 0;}

private:
    // raw pointer to be managed
    mutable T* _ptr; 
    mutable unsigned int* _refCnt;
};

}
