#ifndef _SIMULATOR_CORE_
#define _SIMULATOR_CORE_

#include <iostream>
#include <queue>
#include <vector>

#define END_TIME 999
#define COST_INF 999

using namespace std;

// some declarations
class Event;
class Link;
class RouterBase;
class Simulator;
typedef int CostType;
typedef vector<Link> LinkVector;
typedef RouterBase* ptrToRouterBase;
typedef vector<ptrToRouterBase> ptrToRouterBaseVector;
typedef priority_queue<Event> EventQueue;

// class definition
class Event
{
    public:
        Event();
        Event(uint32_t EventTime, int source, int destination, void *pData);
        bool operator<(const Event &a) const;
        bool operator>(const Event &a) const;
        bool operator==(const Event &a) const;
        Event& operator=(const Event &a);
    public:
        uint32_t time;
        int Src;
        int Dst;
        void* ptrToData;
};

class Link
{
    public:
        Link(CostType Cost, ptrToRouterBase pDst);
    public:
        CostType cost;
        ptrToRouterBase pdst;
};

class RouterBase
{
    public:
        RouterBase(int ID);
        // RouterBase(EventQueue *ptr);
        void SetpQueue(EventQueue* ptr);
        int GetId() const;
        virtual void AddLink(CostType cost, ptrToRouterBase pDst);
        virtual void init()=0;
        virtual bool update(Event message)=0;
    protected:
        int id;
        LinkVector links;
        EventQueue *pQueue;
};

// Simulator ( the manager of events and routers )
class Simulator
{
    public:
        // Constructure and Deconstructure
        Simulator(ptrToRouterBaseVector *ptr);
        Simulator(ptrToRouterBaseVector *ptr, int nodeNum, CostType **adjacentMatrix);
        ~Simulator();
        // Simulator(int nodeNum, int )
        void SetTime(uint32_t start, uint32_t end);
        EventQueue* GetpQueue() const;
        void Enqueue(uint32_t time, int Src, int Dst, void* pData);
        Event Dequeue();
        void Init();
        void Run();
        void Destroy();
    private:
        bool init_flag;
    private:
        // topology parameters
        int NodeNum;
        CostType **Matrix;
        ptrToRouterBaseVector *pRouters;
        // simulation parameters
        uint32_t _start_time;
        uint32_t _end_time;
        EventQueue *pQueue;

};

#endif