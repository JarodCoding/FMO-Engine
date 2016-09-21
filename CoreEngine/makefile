compile=g++ -c -Wall -std=c++14
link=g++
seperator=\\

bin=bin$(seperator);
OBJS=bin$(seperator)Data$(seperator)Data.o bin$(seperator)Data$(seperator)Syncable.o bin$(seperator)Data$(seperator)ExtensionType.o bin$(seperator)Data$(seperator)Property.o
TestOBJS=bin$(seperator)Test$(seperator)DataTest.o

all: debug;
release: compile += -Ofast
release: link += -Ofast
release: CoreEngine
	$(link) -o bin$(seperator)CoreEngine.dll $(OBJS) //TODO implement proper dll creation and entry functions

debug: compile += -Og -g3
debug: link += -Og -g3
debug: CoreEngine $(TestOBJS)
	$(link) -o bin$(seperator)Test.exe $(OBJS) $(TestOBJS)

CoreEngine: $(OBJS)

$(OBJS): bin$(seperator)%.o:src$(seperator)$(seperator_src)%.cpp
	-mkdir $(@D)
	$(compile) -o $@ $<
	
$(TestOBJS): bin$(seperator)%.o:src$(seperator)$(seperator_src)%.cpp
	-mkdir $(@D)
	$(compile) -o $@ $<
