#pragma once
#include "lib.h"
#include "Student.h"
#include "container.h"

constexpr double PASS_MARK = 5.0;

// Ways of splitting the students into "passed" and "failed" (v1.0).
//   Copy          : Strategy 1 - two new containers, students are COPIED, "all" is kept.
//   Move          : Strategy 2 - one new container (failed); failed students are moved out
//                   and erased from "all" one by one, so "all" ends up holding the passed.
//   CopyAlgo      : Strategy 1 written with <algorithm> (remove_copy_if + copy_if).
//   MoveAlgo      : Strategy 2 written with <algorithm> (stable_partition + ONE erase).
//   PartitionSort : Strategy 2 with std::partition (order not kept); the two smaller
//                   groups are sorted afterwards instead of sorting everybody first.
//   FindIfSplice  : Strategy 2 for std::list only: std::find_if locates each failed student
//                   and list::splice relinks its node into "failed" (nothing is copied/moved).
enum class Strategy { Copy = 1, Move = 2, CopyAlgo = 3, MoveAlgo = 4, PartitionSort = 5, FindIfSplice = 6 };

const char *strategyName(Strategy s);

void sortStudents(Container &Group);

// "passed" and "failed" must be empty. After the call both hold their group.
// Copy strategies leave "all" untouched; Move strategies leave it empty.
void splitStudents(Strategy s, Container &all, Container &passed, Container &failed);
