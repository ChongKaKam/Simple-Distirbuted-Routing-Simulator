#include "core.h"

// Event
Event::Event():time(0),ptrToData(NULL) {}
Event::Event(uint32_t EventTime, int source, int destination, void *pData):
    time(EventTime), Src(source), Dst(destination), ptrToData(pData) {}
bool Event::operator<(const Event &a) const { return time < a.time; }
bool Event::operator>(const Event &a) const { return time > a.time; }
bool Event::operator==(const Event &a) const {return time == a.time; }
Event& Event::operator=(const Event &a) {
    if(this==&a) return *this;
    time = a.time;
    Src = a.Src;
    Dst = a.Dst;
    ptrToData = a.ptrToData;
    return *this;
}
// Link
Link::Link(CostType Cost, ptrToRouterBase pDst):cost(Cost), pdst(pDst) {}

// RouterBase
RouterBase::RouterBase(int ID):id(ID), pQueue(NULL){}
// RouterBase::RouterBase(EventQueue *ptr):pQueue(ptr){}
int RouterBase::GetId() const { return id; }
void RouterBase::SetpQueue(EventQueue *ptr){
    pQueue = ptr;
}
void RouterBase::AddLink(CostType cost, ptrToRouterBase pDst){
    links.push_back(Link(cost, pDst));
}

// Simulator
Simulator::Simulator(ptrToRouterBaseVector *ptr):
    _start_time(0),_end_time(0),NodeNum(0),Matrix(NULL), pRouters(ptr), init_flag(false)
{ 
    pQueue = new EventQueue; 
    for(int i=0; i<pRouters->size(); ++i){ pRouters->at(i)->SetpQueue(pQueue); }
}

Simulator::Simulator(ptrToRouterBaseVector *ptr, int nodeNum, CostType **adjacentMatrix):
    NodeNum(nodeNum), _start_time(0), _end_time(0), pRouters(ptr), init_flag(false)
{
    pQueue = new EventQueue;
    for(int i=0; i<pRouters->size(); ++i){ pRouters->at(i)->SetpQueue(pQueue); }
    Matrix = new CostType*[nodeNum];
    for(int i=0; i<nodeNum; ++i){
        Matrix[i] = new CostType[nodeNum];
    }
    for(int i=0; i<nodeNum; ++i){
        for(int j=i; j<nodeNum; ++j){
            if(adjacentMatrix[i][j]!=adjacentMatrix[j][i])
            {
                std::cout << "it is not a symmetric matrix" << std::endl;
                return;
            }
            CostType cost_ij=adjacentMatrix[i][j];
            Matrix[i][j] = cost_ij;
            Matrix[j][i] = cost_ij;
            // if(i==j) { std::cout << "i==j:" << cost_ij << std::endl;}
            if(cost_ij != 0 && cost_ij != COST_INF){
                // add links
                pRouters->at(i)->AddLink(cost_ij, pRouters->at(j));
                pRouters->at(j)->AddLink(cost_ij, pRouters->at(i));
            }
        }
    }
}

Simulator::~Simulator(){
    Destroy();
}

void Simulator::SetTime(uint32_t start, uint32_t end){
    if(end < start) {
        std::cout << "end must be greater than start" << std::endl;
        _start_time = 0;
        _end_time = 0;
        return; 
    }
    _start_time = start;
    _end_time = end;
}

EventQueue* Simulator::GetpQueue() const{
    return pQueue;
}

void Simulator::Enqueue(uint32_t time, int Src, int Dst, void* pData){
    pQueue->push(Event(time, Src, Dst, pData));
}
Event Simulator::Dequeue(){
    Event temp = pQueue->top();
    pQueue->pop();
    return temp;
}
void Simulator::Run(){
    if(!init_flag) { Init(); }
    std::cout << "Simulator: start running" << std::endl;
    if(_end_time<=_start_time){
        std::cout << "ERR: _end_time is less than _start_time." << std::endl;
        std::cout << "start:" << _start_time << " end: " << _end_time << std::endl;
        return;
    }
    uint32_t current_time = _start_time;
    Event event;
    while(!pQueue->empty()&& current_time < _end_time)
    {
        event = Dequeue();
        current_time = event.time;
        pRouters->at(event.Dst)->update(event);
    }
    // clean all left events
    while(!pQueue->empty()){ pQueue->pop(); }
    std::cout << "Simulator: simulation terminated" << std::endl;
}
void Simulator::Destroy(){
    // if(pRouters != NULL)
    // {
    //     std::cout << "clean pRouter" << std::endl;
    //     for(int i=0; i<pRouters->size(); ++i){
    //         ptrToRouterBase temp = (pRouters->at(i));
    //         delete temp;
    //     }
    //     pRouters->clear();
    //     delete pRouters;
    //     pRouters = NULL;
    // }
    if(Matrix != NULL){
        // std::cout << "clean Matrix" << std::endl;
        for(int i=0; i<NodeNum; ++i){
            delete []Matrix[i];
        }
        delete []Matrix;
        Matrix = NULL;
    }
    if(pQueue != NULL ){
        // std::cout << "clean pQueue" << std::endl;
        while(!pQueue->empty()) { pQueue->pop(); }
        delete pQueue;
        pQueue = NULL;
    }
}

void Simulator::Init(){
    if(init_flag) return;
    std::cout << "start initializing..." << std::endl;
    if(pQueue->empty()){
        // no tasks in the queue
        for(int i=0; i<pRouters->size(); ++i){
            pRouters->at(i)->init();
        }
    }
    init_flag = true;
}