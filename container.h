#pragma once
#include "lib.h"
#include "Student.h"

// Container used by the whole program. Chosen at COMPILE time (same code, 3 builds):
//   g++ ...               -> vector
//   g++ ... -DUSE_LIST    -> list
//   g++ ... -DUSE_DEQUE   -> deque
#if defined(USE_LIST)
    using Container = list<Student>;
    inline const char *CONTAINER_NAME = "list";
#elif defined(USE_DEQUE)
    using Container = deque<Student>;
    inline const char *CONTAINER_NAME = "deque";
#else
    using Container = vector<Student>;
    inline const char *CONTAINER_NAME = "vector";
#endif
