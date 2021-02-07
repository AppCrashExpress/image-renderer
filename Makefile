TARGET = renderer

SRC_DIR = ./src
OBJ_DIR = ./obj

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
HEADERS := $(wildcard $(SRC_DIR)/*.h)

_OBJ = $(SOURCES:$(SRC_DIR)/%.cpp=%.cpp)
OBJ := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(_OBJ))

CXX = g++
CXXFLAGS =

DFLAGS = -std=c++11 -O0 -g
NOD_FLAGS = -std=c++11 -O2

WARNINGS = \
		   -Wall \
		   -Wextra \
		   -Wall \
		   -Werror \
		   -Wno-sign-compare \
		   -Wno-unused-result \
		   -pedantic

ifndef NO_ERROR
	CXXFLAGS += $(WARNINGS)
endif

ifndef DEBUG
	CXXFLAGS += $(NOD_FLAGS)
else
	CXXFLAGS += $(DFLAGS)
endif

# Always try to create dir
$(shell mkdir -p $(OBJ_DIR))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

imageclean:
	rm -f *.tga
