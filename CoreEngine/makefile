compile=g++ -c -Wall -O3 -std=c++14
link=g++
seperator=\\

bin=bin$(seperator);
OBJS=bin$(seperator)Data$(seperator)Data.o bin$(seperator)Data$(seperator)Syncable.o bin$(seperator)Data$(seperator)ExtensionType.o bin$(seperator)Data$(seperator)Property.o
TestOBJS=bin$(seperator)Test$(seperator)DataTest.o

all: debug;

debug: compile += -g3
debug: link += -g3
debug: CoreEngine $(TestOBJS)
	$(link) -o bin$(seperator)Test.exe $(OBJS) $(TestOBJS)

CoreEngine: $(OBJS)

$(OBJS): bin$(seperator)%.o:src$(seperator)$(seperator_src)%.cpp
	-mkdir $(@D)
	$(compile) -o $@ $<
	
$(TestOBJS): bin$(seperator)%.o:src$(seperator)$(seperator_src)%.cpp
	-mkdir $(@D)
	$(compile) -o $@ $<
