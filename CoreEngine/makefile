compile=g++ -c -Wall -O3 -std=c++14 -o
link=g++ -o
seperator=\\

bin=bin$(seperator);
OBJS=bin$(seperator)Data$(seperator)Data.o bin$(seperator)Data$(seperator)Syncable.o bin$(seperator)Data$(seperator)ExtensionType.o bin$(seperator)Data$(seperator)Property.o
TestOBJS=bin$(seperator)Test$(seperator)DataTest.o

all: CoreEngine;

debug: compile += -g
debug: link += -g
debug: CoreEngine $(TestOBJS)
	$(link) bin$(seperator)Test.exe $(OBJS) $(TestOBJS)

CoreEngine: $(OBJS)

$(OBJS): bin$(seperator)%.o:src$(seperator)$(seperator_src)%.cpp
	-mkdir $(@D)
	$(compile) $@ $<
	
$(TestOBJS): bin$(seperator)%.o:src$(seperator)$(seperator_src)%.cpp
	-mkdir $(@D)
	$(compile) $@ $<
