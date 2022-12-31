# Simple-Distirbuted-Routing-Simulator
SDRS(Simple Distributed Routing Simulator) is a simple platform in which allow to test some distributed routing algorithms.

## 1 Motivation

Recently, I am researching the routing algorithm. Once I read a new paper, and want to try the core idea of the algorithm, I have to be face with the complicated "Simulator" like `MiniNet` or `NS-3`. It is hard to deploy the algorithm since the large and complicated architecture of these apps. Therefore, I want to try to develop a simple application to help me deploy algorithms easily. It is `SDRS`.

## 2 Basic Introduction

So far, I divided the app into two parts, one is the **core** which is shown in `core.h`  and `core.cc` and the other part is **MyRouter** which is shown in `myrouter.cc` and `myrouter.h`. I manage the program in `makefile`. The commands of `makefile` are shown later.

The main architecture can be shown as below

<img src="https://s2.loli.net/2022/12/07/wDndhUAciE8SCGr.png" alt="image.png" style="zoom:30%;" />



### 2.1 Core

The **Core** contains `Event`, `Link`, `RouterBase` and `Simulator`. 

##### Event Class

The `Event` is the ADT of the simulation events. We use the priority queue to manage simulation events. These events are sorted in time increasing order. The content of an event includes time, source_id, destination_id and a pointer which points to the data. 

```c++
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
```

##### Link Class

The `Link` is the ADT of the connectivity of nodes (routers). This class is mainly responsible for the link information in DSRS. It has two values: `cost` and `pdst`. The `cost` shows the cost of this link and the `pdst` is the pointer which points to the `RouterBase`.

```c++
class Link
{
    public:
        Link(CostType Cost, ptrToRouterBase pDst);
    public:
        CostType cost;
        ptrToRouterBase pdst;
};
```

##### RouterBase Class

The `RouterBase` is the base class of the router, it has some virtual function which you should complete before you start simulating. You can customize your algorithm in the derived class of `RouterBase`. There are three function you should implement: `AddLink()`，`init()` and `update()`. 

+ The `AddLink()` will be called when you set up the links between nodes in `Simulator`. However, it is fine to call this function manually to add links to your network.
+ The `init()` is responsible for initialization of a router. The initialization includes setting the informations and enqueue events to the `EventQueue`. It will be called at the beginning of the simulation. When the `Simulator` calls its member function `Simulator::Init()` , the function will traversal all routers and call their function `RouterBase::init()`. 
+ The `update()` is where you can customize your algorithm. Every time the `Simulator` dequeue an event and take relative actions will call the relative routers' `RouterBase::update()` functions to process this event.

##### Simulator Class

All components are assembled in this class: `Event` and `EventQueue` , `RouterBase`, Adjacent Matrix of its topology and tims. Therefore, the `Simulator` can be considered as the **Brain** which schedules all events and manages all components.

There are some constructer in the `Simulator`:

```c++
// empty
Simulator(ptrToRouterBaseVector *ptr);
// recommand the way below:
// initialized by the adjacent matrix
Simulator(ptrToRouterBaseVector *ptr, int nodeNum, CostType **adjacentMatrix);
```

As you can see, the simulator need a `ptrToRouterBaseVector` . It is defined as:

```c++
typedef vector<ptrToRouterBase> ptrToRouterBaseVector;
```

This vector contains the pointer which points to the `RouterBase` like class. So it is fine to add pointers which point to your class which is inherited from the `RouterBase` class. 

Once you have generated a `Simulator`, you can call `Simulator::SetTime()` to set the start time and the end time. If everything is ready, you can just call `Simulator::Run()` to start the simulation. After the simulation finished, you can call `Simulator::Destroy()` to destroy all items.

##### More Details

In this README, I just show some key informations and functions that are important for you to use this program. More details are shown in the source code. If you have some questions, you can try to read codes for help or hand up issues. 

### 2.2 MyRouter

The codes are shown in  `myrouter.cc` and `myrouter.h`. This part is where you can inherit `RouterBase` class and customize your class.

### 2.3 Makefile

This program is compiled by **g++-12**. You can change the compiler in `makefile` and the tarfget name of this program.

```makefile
# compiler
CC = g++
LD = g++
# the name of this target
target = Router
# sources and objects and the configuration of build path
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, build/%.o, $(SRC))
BUILD_PATH = $(patsubst ./%, build/%, ./)
...
```



## 3 Customize Your Algorithm

The structure of the files is shown below:

```shell
program
├── algorithm (A lib of some algorithms)
├── core (The core of this program)
└── main
```

There are three directories:

+ `algrithm` : It is supposed to place algorithms. If you want to custmize your algorithm, it is better to create files in this directory.
+ `core` : The core source file is in this directory.
+ `main` : You can finish the main project in this directory.

Since we know the structure of `SDRS`, it is easy to customize your algorithm.

+ First, you finish your algorithm in the `algorithm` directory. (more details are show above)
+ Second, create a main file in the `main` directory and finish your project.
  (Since the rule of C++ compiler which only allows a file to have `main()` function, if there are many `main()` functions, you should enable the one you want. I will develop a tool to make it easy and convenient to select the mian file later.)
+ Last, use `make` to compile project and check your algorithm.

## 4 Future Works

Although this program can run, there is a long way to go to implement all my ideas. I will try to implement it in the future. The works includes more than:

+ add more operations in SDRS
+ add some methods to mature the algorithm
+ add log systems to track the information of simulation
+ add a tool to help user to select their projects.
+ ...
