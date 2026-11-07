# Student Grade Calculator (C++)

This is a C++ program I wrote to manage the grades of a group of students. It reads students from a file or from the keyboard, calculates their final grades, sorts them, and splits them into those who passed and those who failed.

The final grade is 0.4 times the homework result plus 0.6 times the exam mark. For the homework part the program calculates both the average and the median of the marks, so every student gets two final grades. A student passes when the average-based final grade is 5.0 or more.

Version 1.0 is mostly about speed. I compared three containers (vector, list and deque) and several ways of splitting the students, to find out which combination is the fastest.

## Releases

v0.1 was the first version: a Student class with the Rule of Three, overloaded input and output operators, average and median final grades, random marks, reading Students.txt, and a sorted table.

v0.2 split the code into classes and several files and added exception handling. It can generate five test files (from 1 000 to 10 000 000 students), split the students into passed and failed (saved in two files) and time every step. Results can also be exported to a .csv file.

v0.25 is the same program using list and deque as well as vector, to see how the container affects the speed.

v1.0 adds two ways of splitting the students with a menu to choose between them, a rewrite of the splitting using the algorithm library, some speed-ups in the Student class, a Makefile and a CMakeLists.txt, and the final comparison you can read below.

## How to use it

### Building

You need a C++17 compiler (g++, clang or MSVC) and either make or cmake.

With make (Linux, macOS or MSYS2; on Windows with MinGW the command is mingw32-make):

```
make
```

That builds three programs. To build only one of them, use make vector, make list or make deque. To delete them, use make clean.

With CMake (any system):

```
cmake -S . -B build
cmake --build build
```

On Windows with MinGW, add -G "MinGW Makefiles" to the first command.

Either way you end up with three programs: students_vector, students_list and students_deque. They are built from exactly the same code, and the only difference is the container. The file container.h picks it using the -DUSE_LIST or -DUSE_DEQUE compiler flags. Always build with optimisation (-O2, or Release in CMake, which is the default here), because otherwise the times mean nothing.

### Running

Run the program from the project folder, because it looks for a folder called files:

```
./students_list
```

You will see a menu with four options.

Option 1 asks for the name of a file inside the files folder (you can try Students.txt), sorts the students and saves the results in files/results.csv, which you can open with Excel.

Option 2 lets you type the students in yourself and prints the sorted table.

Option 3 creates the test files, from files/students1000.txt up to files/students10000000.txt. The biggest one is around 370 MB.

Option 4 is the speed benchmark. It asks how to split the students (strategies 1 to 6, or 7 to run all of them) and times the process on every test file. For each run it prints the time of reading, sorting, splitting and writing, saves the passed and failed students in two files, and adds a line to a file called benchmark_ followed by the container name and .csv.

### The input file

The first line of the file (the header) is ignored. In every other row, the last number is the exam mark and all the numbers before it are homework marks between 0 and 10. For example:

```
Name        Surname    HW1   HW2   HW3   HW4   HW5   Exam
Ana         Garcia       8     9    10     6    10      9
```

### What is in the project

Student.h and Student.cpp hold the Student class and its grade calculations. container.h chooses between vector, list and deque. file.h and file.cpp take care of reading, writing, the .csv export and the generation of test files. process.h and process.cpp contain the sorting and the different ways of splitting the students. test.h and test.cpp contain the timer, the test files and the benchmark. exceptions.h handles errors and main.cpp has the menus. The results folder has the raw numbers behind the comparison below.

## The ways of splitting the students

Strategy 1 copies every student into either a passed or a failed container. The original container keeps everybody, so two new containers are needed.

Strategy 2 moves the failed students into a new failed container and erases them from the original container one by one. When it finishes, the original container only holds the students who passed, so only one new container is needed.

Strategy 3 is Strategy 1 written with the algorithm library, using remove_copy_if and copy_if.

Strategy 4 is Strategy 2 written with stable_partition, followed by a single erase.

Strategy 5 is Strategy 2 written with partition. The order is not kept, so the two smaller groups are sorted afterwards.

Strategy 6 is Strategy 2 for list only. It uses find_if to find each failed student and splice to move it over to the other list without copying anything.

All the combinations produce exactly the same output files, which was checked with md5sum, so comparing their times is fair.

## Results

These numbers were measured on my Windows PC with g++ 16.1 (MSYS2) and -O2. Every test was run once, except Strategies 1 and 2 with vector, which were run twice and averaged. Those two runs differed by 3 to 6 percent, so differences of a few percent are just noise. All the raw data is in the results folder. Peak memory can't be read on Windows, so the memory figures further down come from a separate run on Linux.

### One million students

The fastest combination was list with Strategy 6 (find_if and splice), which took 1.22 seconds in total. Very close behind was list with the plain erase loop of Strategy 2, at 1.26 seconds. The best results for the other two containers were 1.36 seconds for vector and 1.46 seconds for deque, both with Strategy 5. These are the total times for every strategy:

- vector: Strategy 1 took 1.54 s, Strategy 3 took 1.51 s, Strategy 4 took 1.49 s and Strategy 5 took 1.36 s.
- list: Strategy 1 took 1.37 s, Strategy 2 took 1.26 s, Strategy 3 took 1.36 s, Strategy 4 took 1.31 s, Strategy 5 took 1.32 s and Strategy 6 took 1.22 s.
- deque: Strategy 1 took 1.67 s, Strategy 3 took 1.60 s, Strategy 4 took 1.63 s and Strategy 5 took 1.46 s.

Strategy 2 was not run for vector and deque at this size, because it would take well over ten minutes. The next section explains why.

### Why Strategy 2 is a problem for vector and deque

Erasing from the middle of a vector or a deque forces every student after it to shift one place. Doing that once for every failed student is very slow. Splitting only 100 000 students took 14.9 seconds with a vector and 7.6 seconds with a deque. With a list it took 0.003 seconds, because erasing from a list is instant.

### Ten million students

With ten million students the order was the same. List with Strategy 6 took 12.8 seconds, list with Strategy 2 took 13.0 and list with Strategy 1 took 13.5. Vector needed 17.0 seconds with Strategy 1 and 14.6 with Strategy 5, and deque needed 17.8 seconds with Strategy 1 and 15.4 with Strategy 5.

### Memory

Memory was measured on Linux with a million students. Strategy 1 really does waste memory, because it keeps the original students and also a copy of all of them. Vector used 283 MB with Strategy 1 and 164 MB with Strategy 5, list used 309 MB against 157 MB, and deque used 257 MB against 170 MB. That is roughly 1.5 to 2 times more memory. With ten million students the list needed 3 056 MB with Strategy 1 but only 1 530 MB with Strategy 2.

## What I learned

1. The fastest option is list. With Strategy 2 it needs 1.26 seconds for a million students, and 1.22 seconds when the split is written with find_if and splice. Compared with Strategy 1 on the same container it is about 8 percent faster with a million students and 3 to 4 percent faster with ten million. That is a small gain in time, but it uses half the memory.

2. A lot of the difference between containers comes from sorting, not from splitting. A list just re-links its nodes, so sorting a million students takes about 0.17 seconds. Vector and deque have to move whole students around, which takes between 0.34 and 0.54 seconds.

3. Strategy 2 is only a good idea when erasing is cheap. It is the fastest option with list and a disaster with vector and deque.

4. The algorithms rescue vector and deque. Replacing the erase loop with stable_partition brought the split of 100 000 students from 14.9 seconds down to 0.006 seconds with a vector, and from 7.6 seconds down to 0.007 with a deque. Using partition and sorting the two groups afterwards, both containers finish a million students about 12 percent faster than with Strategy 1, and about 14 percent faster with ten million.

5. For the winner, list, the algorithms barely matter. Using find_if and splice made the split step 31 percent faster, going from 0.038 to 0.026 seconds. But that step was only about 3 percent of the whole program, so the total improved by about 3 percent, which is within the noise. What takes the time now is reading the file (43 percent), writing the results (40 percent) and sorting (13 percent).

6. Using remove_copy_if and copy_if (Strategy 3) did not help. The split step was a bit slower than the plain copy loop in every container, for example 0.142 seconds against 0.109 with list, and the small differences in the total time are just noise. Not every algorithm is faster than the loop it replaces.

