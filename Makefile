# Makefile (Unix / Linux / macOS / MSYS2) - Student grade calculator v1.0
#
#   make            builds the three programs (vector, list and deque versions)
#   make vector     builds only students_vector   (same for: list, deque)
#   make run        builds and runs the vector version
#   make clean      removes every generated file
#
# The container is chosen at compile time: the SAME sources are compiled with
# -DUSE_LIST or -DUSE_DEQUE (see container.h). -O2 matters: with -O0 the timings
# are not representative.

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra

SRC := main.cpp Student.cpp file.cpp process.cpp test.cpp
HDR := $(wildcard *.h)

OBJ_VECTOR := $(addprefix build/vector/,$(SRC:.cpp=.o))
OBJ_LIST   := $(addprefix build/list/,$(SRC:.cpp=.o))
OBJ_DEQUE  := $(addprefix build/deque/,$(SRC:.cpp=.o))

.PHONY: all vector list deque run clean

all: vector list deque

vector: students_vector
list:   students_list
deque:  students_deque

students_vector: $(OBJ_VECTOR)
	$(CXX) $(CXXFLAGS) $^ -o $@

students_list: $(OBJ_LIST)
	$(CXX) $(CXXFLAGS) -DUSE_LIST $^ -o $@

students_deque: $(OBJ_DEQUE)
	$(CXX) $(CXXFLAGS) -DUSE_DEQUE $^ -o $@

build/vector/%.o: %.cpp $(HDR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/list/%.o: %.cpp $(HDR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -DUSE_LIST -c $< -o $@

build/deque/%.o: %.cpp $(HDR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -DUSE_DEQUE -c $< -o $@

run: students_vector
	./students_vector

clean:
	rm -rf build students_vector students_list students_deque
