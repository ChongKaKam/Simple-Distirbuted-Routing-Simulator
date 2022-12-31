#include <iostream>
#include <string>
#include "../core/core.h"
#include "../algorithm/myrouter.h"

#define MAXSIZE 6

int main(){
    CostType M[MAXSIZE][MAXSIZE]=
    {
        0,6,1,COST_INF,COST_INF,COST_INF,
        6,0,5,COST_INF,3,COST_INF,
        1,5,0,5,COST_INF,4,
        COST_INF,COST_INF,5,0,COST_INF,2,
        COST_INF, 3, COST_INF, COST_INF, 0, 6,
        COST_INF, COST_INF, 4, 2, 6, 0
    };
    CostType *p[MAXSIZE];
    for(int i=0; i<MAXSIZE; ++i){ p[i]=M[i]; }

    vector<RouterBase*> *RQueue = new vector<RouterBase*>;
    for(int i=0; i<MAXSIZE; ++i){
        MyRouter* temp = new MyRouter(i);
        RQueue->push_back(temp);
    }    

    Simulator sys(RQueue, MAXSIZE, p);

    sys.SetTime(0, 1);
    sys.Run();
    sys.Destroy();
    return 0;
}