#----------------------------------------------------------
# Variables

POCO=../../../thirdParty/libs/poco-1.3.6p2

CXX = g++
CC = gcc

INCLUDES = -I. -I$(POCO)/include
CXXFLAGS = -g $(INCLUDES) -O4
LIBS=-L$(POCO)/lib -lPocoFoundation -lrt
LINKOPTS=-Wl,-rpath=$(POCO)/lib

SRC = \
	DataflowGraph.cpp \
	DataflowNode.cpp \
	NodeQueueBlocking.cpp \
	NodeQueueSimple.cpp \
	PoolNode.cpp \
	PriorityWorkQueue.cpp \
	ReadConfiguration.cpp \
	Source.cpp \
	Target.cpp \
	ThreadNode.cpp \
	Timing.cpp \
	WorkThread.cpp \
	main.cpp

OBJ = $(addsuffix .o, $(basename $(SRC)))
TARGET = dataflow

SRC_TOOL = processLatency.cpp
OBJ_TOOL = processLatency.o
TARGET_TOOL = processLatency

#----------------------------------------------------------
# Rules

.SUFFIXES: .cpp

all: $(TARGET) $(TARGET_TOOL)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) $(LIBS) $(LINKOPTS) -o $@ $(OBJ)

$(TARGET_TOOL): $(OBJ_TOOL)
	$(CC) $(CXXFLAGS) $(LIBS) $(LINKOPTS) -o $@ $<


#----------------------------------------------------------
# Other

#depend:
#	makedepend $(CXXFLAGS) -Y $(SRC)

clean:
	rm -f $(OBJ) $(TARGET) $(OBJ_TOOL) $(TARGET_TOOL)
