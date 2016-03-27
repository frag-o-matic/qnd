#include <iostream>
#include "UniquePtr.h"

int main(void)
{
    std::cout<< "Demo Start"<< std::endl;

    QND::UniquePtr<int> u1 = new int{42};
    if(u1)
        std::cout<<"Val: "<< *u1 << std::endl << "Addr: "<< &u1 << std::endl;

    QND::UniquePtr<int> u2 = u1;
    QND::UniquePtr<int> u3;

    if(u1)
        std::cout<<"Val: "<< *u1 << std::endl << "Addr: "<< &u1 << std::endl;
    else
        std::cout<<"U1 is now null!"<<std::endl;

    if (u2)
        std::cout<<"U2 Val: "<< *u2 << std::endl << "U2 Addr: "<< &u2 << std::endl;
   
    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 << std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;

    u3 = u2;

    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 << std::endl;
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

    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 << std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;
    
    std::cout<<"release()"<<std::endl;
    int *p2 = u3.release();
    
    if(p2)
        std::cout<<"p2 Val: "<< *p2 << std::endl << "p2 Addr: "<< p2 << std::endl;
    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 << std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;

    std::cout<<"reset()"<<std::endl;
    u3.reset(new int{100});
    if (u3)
        std::cout<<"U3 Val: "<< *u3 << std::endl << "U3 Addr: "<< &u3 << std::endl;
    else
        std::cout<<"U3 is null!"<<std::endl;

    delete p2;
    p2 = nullptr;
    if(p2)
        std::cout<<"p2 Val: "<< *p2 << std::endl << "p2 Addr: "<< p2 << std::endl;
    else
        std::cout<<"p2 is NULL"<<std::endl;
    std::cout<< "Demo End"<< std::endl;
    return 0;
}
