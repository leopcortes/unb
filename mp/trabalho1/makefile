# compilador
CXX = g++ 
# flags
CXXFLAGS = -std=c++11 -Wall 

# diretório fonte
SRC_DIR = src 
# diretório objeto
OBJ_DIR = obj 

# arquivos fonte
SRCS = $(wildcard $(SRC_DIR)/*.cpp) 
# arquivos objeto
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS)) 

# arquivo executável
TARGET = romano 
all: $(TARGET)

# linkar arquivos objeto com executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# compilar arquivos fonte com arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# criar objetos se não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# limpar arquivos compilador
clean:
	rm -rf $(OBJ_DIR) $(TARGET) 

# limpar arquivos não associados
.PHONY: all clean 