# Makefile - Student grade calculator v1.0 (Unix / Linux / macOS; also works with
# mingw32-make on Windows)
#
#   make            builds the three programs (vector, list and deque versions)
#   make vector     builds only students_vector   (same for: list, deque)
#   make run        builds and runs the vector version
#   make clean      removes the generated programs
#
# The container is chosen at compile time: the SAME sources are compiled with
# -DUSE_LIST or -DUSE_DEQUE (see container.h). -O2 matters: with -O0 the timings
# are not representative.

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra

SRC := main.cpp Student.cpp file.cpp process.cpp test.cpp
HDR := $(wildcard *.h)

ifeq ($(OS),Windows_NT)
    EXE := .exe
endif

.PHONY: all vector list deque run clean

all: vector list deque

vector: students_vector$(EXE)
list:   students_list$(EXE)
deque:  students_deque$(EXE)

# One command per program: no object folders and no Unix-only commands (mkdir -p, rm),
# so it works the same from sh, PowerShell or cmd.
students_vector$(EXE): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o students_vector$(EXE)

students_list$(EXE): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -DUSE_LIST $(SRC) -o students_list$(EXE)

students_deque$(EXE): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -DUSE_DEQUE $(SRC) -o students_deque$(EXE)

run: students_vector$(EXE)
ifeq ($(OS),Windows_NT)
	students_vector$(EXE)
else
	./students_vector
endif

clean:
ifeq ($(OS),Windows_NT)
	-del /Q students_vector.exe students_list.exe students_deque.exe
	-rm -f students_vector.exe students_list.exe students_deque.exe
else
	rm -f students_vector students_list students_deque
endif
