# Student Grade Calculator (C++)

A C++ program that manages and calculates the final grades of a group of students,
splits them into **passed** and **failed**, and measures how fast that can be done with
different containers (`std::vector`, `std::list`, `std::deque`) and different strategies.

Final grade: `Final = 0.4 * (Average of HW | Median of HW) + 0.6 * Exam`
(both the average-based and the median-based result are calculated).
A student **passes** when the average-based final grade is `>= 5.0`.

---

## Releases

| Release | What it contains |
|---|---|
| **v0.1** | `Student` class with the Rule of Three, overloaded `>>` / `<<`, average and median final grade, homework stored in a `std::vector`, random generation of marks, reading `Students.txt`, students sorted and printed in a formatted table. |
| **v0.2** | Code split into classes and several `.h` / `.cpp` files, exception handling (`processException`), generator of 5 test files (1 000 to 10 000 000 records), students split into *passed* / *failed* (written to two files) and timing of every phase (read, sort, split, write). Results can be exported to `.csv`. |
| **v0.25** | The same code compiled with `std::list` and `std::deque` besides `std::vector` (`container.h`, `-DUSE_LIST`, `-DUSE_DEQUE`) and benchmarked. |
| **v1.0** | Two split strategies with a menu, refactor with `<algorithm>`, performance optimisations in `Student`, `Makefile` and `CMakeLists.txt`, full comparison of containers and strategies (this document). |

---

## Usage guide

### 1. Requirements
A C++17 compiler (g++ / clang++ / MSVC) and either `make` (Unix, MSYS2) or `cmake` >= 3.10 (any OS).

### 2. Build

**With make (Unix / Linux / macOS / MSYS2):**
```bash
make            # builds students_vector, students_list and students_deque
make list       # or only one of them: vector | list | deque
make clean
```

**With CMake (any OS):**
```bash
cmake -S . -B build
cmake --build build --config Release
```
The executables are `students_vector`, `students_list` and `students_deque`
(inside `build/` or `build/Release/` depending on the generator).
Always build in **Release / -O2**: with `-O0` (a Debug build) the timings are not representative.

The three programs are built from the **same source files**; only the container changes
(`container.h` picks it from the `-DUSE_LIST` / `-DUSE_DEQUE` compile flags).

### 3. Run
Run the program **from the project root**, because it reads and writes the `files/` folder:
```bash
./students_list
```
```
Choose input method:
1. Read from file
2. Input manually
3. Generate the 5 test files(1k to 10M records)
4. Speed benchmark on the 5 test files (choose split strategy)
```

| Option | What it does |
|---|---|
| **1** | Asks for a file name inside `files/` (for example `Students.txt`), sorts the students and exports the results to `files/results.csv` (open it with Excel / LibreOffice). |
| **2** | Lets you type students by hand and prints the sorted table. |
| **3** | Generates `files/students1000.txt` ... `files/students10000000.txt` (the 10M file is about 370 MB). |
| **4** | Benchmark. Asks for the split strategy (1-6, or 7 = all) and runs it on every generated file. |

Benchmark output: a summary on screen, the two result files (`files/studentsN_passed.txt`,
`files/studentsN_failed.txt`) and a `benchmark_<container>.csv` with one line per run
(read / sort / split / write / total time and peak memory).

### 4. Input file format
The first line (header) is skipped. In every row the **last** number is the exam mark and
all the previous ones are homework marks (0-10):
```
Name        Surname    HW1   HW2   HW3   HW4   HW5   Exam
Ana         Garcia       8     9    10     6    10      9
```

### 5. Source files

| File | Purpose |
|---|---|
| `Student.h/.cpp` | `Student` class (Rule of Five, average, median, final grades). |
| `container.h` | Chooses `Container` = `vector` / `list` / `deque` at compile time. |
| `file.h/.cpp` | Reading, writing, CSV export and test-file generation. |
| `process.h/.cpp` | Sorting and the split strategies. |
| `test.h/.cpp` | Timer, test-file generation and the benchmark. |
| `exceptions.h` | Central exception handling. |
| `main.cpp` | Menus. |

---

## The split strategies (v1.0)

| # | Strategy | New containers |
|---|---|---|
| 1 | **Copy**: every student is copied into `passed` or `failed`; the base container keeps everybody. | 2 |
| 2 | **Move**: failed students are moved to `failed` and erased from the base container one by one; the base container ends up holding the passed. | 1 |
| 3 | Strategy 1 with `<algorithm>`: `remove_copy_if` + `copy_if`. | 2 |
| 4 | Strategy 2 with `<algorithm>`: `stable_partition` and a single `erase` of the tail. | 1 |
| 5 | Strategy 2 with `std::partition`; the two smaller groups are sorted **after** the split. | 1 |
| 6 | Strategy 2 for `std::list`: `std::find_if` + `list::splice` (nodes are relinked, nothing is copied). | 1 |

All 16 applicable combinations (6 strategies x 3 containers, minus strategy 6 on `vector` and `deque`)
produce **byte-identical output files** (checked with `md5sum`), so the timings are comparable.

---

## Results

Measured on Linux (virtual machine, 2 vCPU, 8 GB RAM), g++ 13.3, `-O2`, `std::chrono::steady_clock`.
Times are the **median of 3 runs** (1 000 000 and 100 000 records) or a single run (10 000 000).
Run-to-run variation is about 10-15 %, so differences smaller than that are noise.
Your numbers will differ with your machine; the conclusions should not.
Raw data: [`results/`](results/).

### 1 000 000 records - total time in seconds (split phase in brackets)

| Strategy | vector | list | deque |
|---|---|---|---|
| 1 copy (loop) | 1.570 (0.214) | 1.136 (0.167) | 1.613 (0.149) |
| 2 move + erase (loop) | not run (O(n^2)) | **0.861 (0.038)** | not run (O(n^2)) |
| 3 `remove_copy_if` / `copy_if` | 1.843 (0.244) | 0.973 (0.106) | 1.653 (0.202) |
| 4 `stable_partition` | 1.576 (0.136) | 1.033 (0.178) | 1.659 (0.173) |
| 5 `partition` + sort | **1.289 (0.056)** | 1.083 (0.048) | **1.403 (0.079)** |
| 6 `find_if` + `splice` | n/a | 0.911 (0.033) | n/a |

### Strategy 2 written as "erase one by one" (100 000 records, split phase)

| vector | list | deque |
|---|---|---|
| 19.9 s | 0.003 s | 9.7 s |

Every `erase` in the middle of a `vector` or `deque` shifts all the following students, so the
cost grows with the square of the size (10x more records = about 100x more time). For 1 000 000
records it would take roughly half an hour, so it was **not run** for those two containers.
`std::list` erases in O(1) and has no problem.

### Peak memory, 1 000 000 records (MB)

| Strategy | vector | list | deque |
|---|---|---|---|
| 1 / 3 (two copies) | 283 | 309 | 257 |
| 2 / 5 / 6 (one new container) | 164 (5) | 157 | 170 (5) |

Strategy 1 really is the memory-hungry one: it holds the original students **plus** a copy of each of
them (about 1.5x - 2x the memory of Strategy 2). The same happens with 10 000 000 records:
`list` 3 056 MB with Strategy 1 vs 1 530 MB with Strategy 2.

### 10 000 000 records (single run)

| Container + strategy | Total | Peak memory |
|---|---|---|
| **list, strategy 2 (loop)** | **10.4 s** | 1 530 MB |
| list, strategy 6 (`find_if` + `splice`) | 11.2 s | 1 530 MB |
| list, strategy 1 | 12.5 s | 3 056 MB |
| vector, strategy 5 | 15.0 s | 1 796 MB |
| vector, strategy 1 | 19.7 s | 2 481 MB |
| deque, strategy 5 | 16.3 s | 1 668 MB |
| deque, strategy 1 | 21.2 s | 2 537 MB |

### Conclusions

1. **Fastest container + strategy: `std::list` with Strategy 2.** It is 1.3x faster than Strategy 1
   on the same container (0.86 s vs 1.14 s at 1M) and uses half the memory. Its split phase is only
   0.04 s, because erasing from a list is O(1).
2. **A big part of the container difference comes from sorting**, not from splitting:
   `list::sort` relinks nodes (0.16 s for 1M) while `std::sort` on a `vector` / `deque` moves whole
   `Student` objects (0.58 s for `vector`, 0.73 - 0.76 s for `deque`).
3. **Strategy 2 is only a good idea if erasing is cheap.** With a naive loop it is fastest on `list`
   and a disaster on `vector` / `deque` (20 s and 10 s for 100 000 records).
4. **`<algorithm>` rescues `vector` and `deque`.** Replacing the erase loop by `stable_partition`
   (100 000 records, split phase) goes from 19.9 s to 0.008 s on `vector` (about 2 500x) and from
   9.7 s to 0.013 s on `deque`. With `partition` + sorting the two smaller groups afterwards, `vector`
   reaches 1.29 s total for 1M records (vs 1.57 s with Strategy 1).
5. **For the winner (`list`, Strategy 2) the algorithms bring almost nothing:** `find_if` + `splice` makes
   the split phase 14 % faster (0.0325 s vs 0.0378 s), but that phase is only about 4 % of the whole
   program, and the total time is the same within the noise (0.91 s vs 0.86 s). `stable_partition`
   (4.7x slower split) and `partition` + sort are slower than the plain loop on a list, because a list
   does not suffer from the cost the algorithms avoid. After the split is optimised, what remains is
   reading (about 43 %), writing (about 33 %) and sorting (about 19 %).
6. **Strategy 1 written with algorithms** (`remove_copy_if` + `copy_if`) is 37 % faster in the split phase
   on `list` (0.106 s vs 0.167 s) but not on `vector` (within noise).

### Other optimisations made in v1.0

Measured at 1 000 000 records, 3 runs each, changing only one thing at a time:

| Change | Effect |
|---|---|
| `getName()` / `getSurname()` return `const string &` instead of a copy (the sort comparator calls them millions of times) | Sorting 3x faster: `vector` 1.79 s -> 0.57 s, `list` 0.48 s -> 0.16 s. Total time -46 % (vector) / -27 % (list). |
| `Student` has a move constructor and move assignment (a user-declared destructor disables the implicit ones, so every `move` was a full copy) | `vector`: sorting 0.98 s -> 0.57 s, total -28 %. `list`: split phase 0.048 s -> 0.037 s. |
| File reading reuses one `istringstream` and one `vector<int>`, and builds each `Student` in place (`emplace_back`) | Fewer allocations while reading. |
| Fixed a bug: the parameterised `Student` constructor validated the (still unset) member `exam` instead of the parameter | Correctness. |
