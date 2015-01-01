compile=g++ -c -Wall -O3 -std=c++11 -o /bin
objects=bin/CoreEngine/Managers/TaskManager.o bin/CoreEngine/Framework/Universal.o bin/CoreEngine/BaseTypes/Data.o bin/Interface/System.o bin/Interface/Registry.o


all: CoreEngine Interface;g++ -o bin/RealTimeStars $(objects)
CoreEngine: Managers Framework BaseTypes;
    
Managers:CoreEngine/Managers/TaskManager;

Framework:CoreEngine/Framework/Universal;
  
BaseTypes:CoreEngine/BaseTypes/Data;
    
Interface:Interface/System Interface/Registry;

%:;$(compile)$*.o $*.cpp