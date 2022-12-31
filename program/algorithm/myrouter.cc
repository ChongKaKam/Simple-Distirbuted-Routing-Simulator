#include "myrouter.h"

MyRouter::MyRouter(int ID):RouterBase(ID) {}
void MyRouter::AddLink(CostType cost, ptrToRouterBase pDst){
    links.push_back(Link(cost, pDst));
}
void MyRouter::init(){
    
    for(int i=0; i<links.size(); ++i){
        int DstID = links[i].pdst->GetId();
        Link* p = &links[i];
        pQueue->push(Event(0, id, DstID, (void*)p));
    }
}
bool MyRouter::update(Event message){
    // std::cout << "ID: " << id << " Links: ";
    // for(int i=0; i<links.size(); ++i){
    //     std::cout << "[ID:" << links[i].pdst->GetId() << ",Cost:" << links[i].cost << "] "; 
    // }
    // std::cout << std::endl;
    std::cout << message.Src << "-->" << message.Dst << std::endl;
    return false;
}
void MyRouter::ShowInfo(){
    std::cout << "id: " << id << std::endl;
}
