#pragma once
#include "Student.h"
#include "lib.h"
#include "container.h"

void readStudentsFromFile(Container& Group);
void exportCSV(const string &filepath, const Container &Group);
void generateStudentsFile(const string &filepath, size_t count, int numSemPoints = 5);
void writeStudentsToFile(const string &filepath, const Container &Group);
Container readStudentsFromPath(const string &filepath);
