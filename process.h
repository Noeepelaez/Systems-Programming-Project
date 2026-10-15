#pragma once
#include "lib.h"
#include "Student.h"

constexpr double PASS_MARK = 5.0;

void sortStudents(deque<Student> &Group);
void splitStudents(deque<Student> &all, deque<Student> &passed, deque<Student> &failed);