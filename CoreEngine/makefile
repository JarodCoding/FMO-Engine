compile=g++ -c -Wall -O3 -std=c++14 -o
link=g++ -o
seperator=\\

bin=bin$(seperator);
OBJS=bin$(seperator)Data$(seperator)Data.o bin$(seperator)Data$(seperator)Syncable.o bin$(seperator)Data$(seperator)ExtensionType.o bin$(seperator)Data$(seperator)Property.o bin$(seperator)Test$(seperator)DataTest.o

all: CoreEngine;

CoreEngine: $(OBJS)
	$(link) bin$(seperator)Test.exe $(OBJS)	


$(OBJS): bin$(seperator)%.o:src$(seperator)$(seperator_src)%.cpp
	-mkdir $(@D)
	$(compile) $@ $<
