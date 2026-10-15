#pragma once
#include "lib.h"
#include "Student.h"

constexpr double PASS_MARK = 5.0;

void sortStudents(vector<Student> &Group);
void splitStudents(vector<Student> &all, vector<Student> &passed, vector<Student> &failed);