seperator=\\
compile=g++ -c -Wall -O3 -std=c++11 -o

all: Data Execution;

Data:Data$(seperator)Data Data$(seperator)Syncable Data$(seperator)ExtensionType;
  
Execution:Execution$(seperator)TaskManager Executione$(seperator)Task Execution$(seperator)StateManager Executione$(seperator)Module;
    
%:; -mkdir bin$(seperator)$(@D)
	$(compile) bin'$(seperator)'$*.o src'$(seperator)'$*.cpp