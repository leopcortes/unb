# Makefile para compilacao da JVM

# Variaveis de Compilação
CC       = gcc
CFLAGS   = -Wextra -g -m32 -std=c99
NFLAGS   = 

SOURCESDIR  = src
INCLUDEDIR  = 
OBJETOSDIR  = objetos

SOURCESJAVA = $(wildcard *.java)
CLASSESJAVA = $(SOURCESJAVA:.java=.class)

SOURCESDIRS_C  = $(wildcard $(SOURCESDIR)/*.c)
OBJECTS_C  = $(patsubst $(SOURCESDIR)/%.c, $(OBJETOSDIR)/%.o, $(SOURCESDIRS_C))
OBJECTS    = $(OBJECTS_C)

TARGET   = main


# Sistemas Operacionais
ifeq ($(OS),Windows_NT)
	REMOVE = rm
	NFLAGS += -fwin32 --PREFIX _
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),MINGW32_NT-6.3)
		REMOVE = rm
	endif
else
	REMOVE = rm -f
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		NFLAGS += -felf32 
	endif
	ifeq ($(UNAME_S),Darwin)
		NFLAGS += -fmacho32 --PREFIX _
	endif
endif


# Compilacao JVM
all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -m32 -o $@ $^ -lm

$(OBJETOSDIR)/%.o: $(SOURCESDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $< 


# Compilacao JAVA
compile_java: $(CLASSESJAVA)

%.class: %.java
	javac $<


# Documentacao
doxygen: Doxyfile
	doxygen Doxyfile


# Limpeza dos arquivos .o e do target (main)
clean:
	rm -rf $(OBJECTS) $(TARGET)
