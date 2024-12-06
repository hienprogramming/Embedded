# Compiler settings
CC = gcc
CFLAGS = -Wall -g

# File paths
SRC = C:/Working/FPT/Autosar/SimulateCan/CanDriver_PB.c
OBJ = CanDriver_PB.o
EXE = CanDriver_PB.exe

# Build rules
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	del $(OBJ) $(EXE)

