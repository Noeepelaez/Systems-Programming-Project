#pragma once
#include "lib.h"
#include "Student.h"

constexpr double PASS_MARK = 5.0;

void sortStudents(list<Student> &Group);
void splitStudents(list<Student> &all, list<Student> &passed, list<Student> &failed);