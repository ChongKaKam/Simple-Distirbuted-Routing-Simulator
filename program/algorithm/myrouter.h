#ifndef _SIMULATOR_MY_ROUTER_
#define _SIMULATOR_MY_ROUTER_

#include <iostream>
#include "core.h"

// Delcaration
class Table;
class MyRouter;

// RouterBase:
// Member Variables: 
//  - int id; 
//  - LinkVector links; 
//  - EventQueue *pQueue;
// Virtual Functions: 
//  - AddLink(CostType cost, ptrToRouterBase pDst);
//  - update(Event message)=0;
//  - init()=0;
class MyRouter: public RouterBase
{
    public:
        MyRouter(int ID);
        void AddLink(CostType cost, ptrToRouterBase pDst);
        void init();
        bool update(Event message);
        void ShowInfo();
    public:
        
    private:
        
};

class Table
{
    public:
        
    public:    

};

#endif