COMPILER = g++

FLAGS = -std=c++17 -Wall

INC_PATHS = -I$(INC_PATH)
INC_PATH  = include
SRC_PATH  = src
OBJ_PATH  = obj

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
OBJ_FILES = $(addprefix $(OBJ_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

EXEC = simulador

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(FLAGS)

dir:
	mkdir -p $(OBJ_PATH) $(INC_PATH) $(SRC_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | dir
	$(COMPILER) $(INC_PATHS) $< -c $(FLAGS) -o $@

clean:
	rm -rf obj $(EXEC)
