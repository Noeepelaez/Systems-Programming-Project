#pragma once
#include "lib.h"
#include "Student.h"


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
