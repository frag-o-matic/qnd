#include <iostream>
#include "SharedPtr.h"

namespace QND {
struct SPTestDummy
{
    int _x;
    SPTestDummy() : _x{0} { }
    int getX() { return _x;}
};
}
int main(void)
{
    std::cout<< "Demo Start"<< std::endl;

    QND::SharedPtr<int> u1 = new int{42};
    if(u1)
        std::cout<<"U1 Val: "<< *u1 << std::endl << "U1 Addr: "<< &u1 <<"Ref Cnt: "<< u1.getRefCount()<< std::endl;

    QND::SharedPtr<int> u2 = u1;
    QND::SharedPtr<int> u3;

    if(u1)
        std::cout<<"U1 Val: "<< *u1 << std::endl << "U2 Addr: "<< &u1 <<"Ref Cnt: "<< u1.getRefCount()<<std::endl;
    else
        std::cout<<"U1 is now null!"<<std::endl;

    if (u2)
        std::cout<<"U2 Val: "<< *u2 << std::endl << "U2 Addr: "<< &u2 <<"Ref Cnt: "<< u2.getRefCount()<< std::endl;
   
    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 <<"Ref Cnt: "<< u3.getRefCount()<< std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;

    u3 = u2;

    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 <<"Ref Cnt: "<< u3.getRefCount()<< std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;

    if(!u2)
        std::cout<<"U2 is null!"<<std::endl;

    std::cout<<"get()"<<std::endl;
    int *p = u3.get();
    if(p)
        std::cout<<"p Val: "<< *p << std::endl << "p Addr: "<< p << std::endl;
    if(!u3)
        std::cout<<"U3 is null!"<<std::endl;
    p = nullptr;

    std::cout<<"U1 Reset"<<std::endl;
    u1.reset();

    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 <<"Ref Cnt: "<< u3.getRefCount()<< std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;
    
    std::cout<<"U3 release()"<<std::endl;
    int *p2 = u3.release();
    
    if(p2)
        std::cout<<"p2 Val: "<< *p2 << std::endl << "p2 Addr: "<< p2 << std::endl;
    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 <<"Ref Cnt: "<< u3.getRefCount()<< std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;
    if (u2)
        std::cout<<"u2 Val: "<< *u2 << std::endl << "u2 Addr: "<< &u2 <<"Ref Cnt: "<< u2.getRefCount()<< std::endl;
    else
        std::cout<<"u2 is null!"<<std::endl;


    std::cout<<"reset()"<<std::endl;
    u3.reset(new int{100});
    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 <<"Ref Cnt: "<< u3.getRefCount()<< std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;

    delete p2;
    p2 = nullptr;
    if(p2)
        std::cout<<"p2 Val: "<< *p2 << std::endl << "p2 Addr: "<< p2 << std::endl;
    else
        std::cout<<"p2 is NULL"<<std::endl;

    QND::SharedPtr<QND::SPTestDummy> spTD = new QND::SPTestDummy{};
    if(spTD)
        std::cout<<"TD Val: " << spTD->_x <<"TD FuncResult: "<< spTD->getX() <<"TD Addr: "<< &spTD <<" RefCnt: "<< spTD.getRefCount() <<std::endl;
    std::cout<< "Demo End"<< std::endl;
    return 0;
}
