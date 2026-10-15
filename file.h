#pragma once
#include <vector>
#include "Student.h"
#include "lib.h"

void readStudentsFromFile(deque<Student>& Group);
void exportCSV(const string &filepath, const deque<Student> &Group);
void generateStudentsFile(const string &filepath, size_t count, int numSemPoints = 5);
void writeStudentsToFile(const string &filepath, const deque<Student> &Group);
deque<Student> readStudentsFromPath(const string &filepath);