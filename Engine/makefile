seperator=\\
compile=g++ -c -Wall -O3 -std=c++11 -o

all: CoreEngine Interface;

CoreEngine: Managers Framework BaseTypes;

Managers:CoreEngine$(seperator)Managers$(seperator)TaskManager;

Framework:CoreEngine$(seperator)Framework$(seperator)Universal;
  
BaseTypes:CoreEngine$(seperator)BaseTypes$(seperator)Data;
    
Interface:Interface$(seperator)System Interface$(seperator)Registry;

%:; -mkdir bin$(seperator)$(@D)
	$(compile) bin'$(seperator)'$*.o src'$(seperator)'$*.cpp