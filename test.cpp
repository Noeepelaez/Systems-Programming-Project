#include "test.h"
#include "Student.h"
#include "file.h"
#include "process.h"
#include "container.h"
#include "exceptions.h"

static const vector<size_t> SIZES = {1000, 10000, 100000, 1000000, 10000000};

// Strategy 2 written as "erase every failed student" is O(n^2) for vector and deque.
// Above this size it is skipped for them (it would take hours); list has no such problem.
static const size_t NAIVE_ERASE_LIMIT = 100000;

// Peak memory of the whole process in MB (Linux only; -1 when it cannot be read).
static double peakMemoryMB() {
    ifstream f("/proc/self/status");
    string line;
    while (getline(f, line)) {
        if (line.rfind("VmHWM:", 0) == 0) {
            istringstream is(line.substr(6));
            double kb = 0;
            is >> kb;
            return kb / 1024.0;
        }
    }
    return -1;
}

string Test::pathFor(size_t n) {
    return  "files/students" + to_string(n) + ".txt";
}

void Test::generateFiles() {
    for (size_t n : SIZES) {
        Timer t;
        generateStudentsFile(pathFor(n), n);
        cout << "Generated " << pathFor(n) << " in " << t.elapsed() << " s\n";
    }
}

void Test::benchmark(size_t n, Strategy s) {
    string path = pathFor(n);
    string base = path.substr(0, path.size() - 4);

    bool isList = string(CONTAINER_NAME) == "list";
    if (s == Strategy::FindIfSplice && !isList) {
        cout << "[" << CONTAINER_NAME << " | " << strategyName(s)
             << "] not available: splice only exists in std::list\n";
        return;
    }
    if (s == Strategy::Move && !isList && n > NAIVE_ERASE_LIMIT) {
        cout << "[" << CONTAINER_NAME << " | " << strategyName(s) << "] " << n
             << " records: skipped (erasing one by one from a " << CONTAINER_NAME
             << " is O(n^2) and would take hours)\n";
        return;
    }

    Timer total, t;

    Container all = readStudentsFromPath(path);
    double tRead = t.elapsed();

    // Strategy "partition+sort" sorts AFTER splitting (two smaller sorts).
    bool sortAfter = (s == Strategy::PartitionSort);

    double tSort = 0;
    if (!sortAfter) {
        t.reset();
        sortStudents(all);
        tSort = t.elapsed();
    }

    t.reset();
    Container passed, failed;
    splitStudents(s, all, passed, failed);
    double tSplit = t.elapsed();

    if (sortAfter) {
        t.reset();
        sortStudents(passed);
        sortStudents(failed);
        tSort = t.elapsed();
    }

    t.reset();
    writeStudentsToFile(base + "_passed.txt", passed);
    writeStudentsToFile(base + "_failed.txt", failed);
    double tWrite = t.elapsed();

    double tTotal = total.elapsed();
    double peak = peakMemoryMB();

    cout << fixed << setprecision(4);
    cout << "[" << CONTAINER_NAME << " | " << strategyName(s) << "] " << n
         << " records  (passed " << passed.size() << ", failed " << failed.size() << ")\n"
         << "   read  : " << tRead  << " s\n"
         << "   sort  : " << tSort  << " s\n"
         << "   split : " << tSplit << " s\n"
         << "   write : " << tWrite << " s\n"
         << "   TOTAL : " << tTotal << " s\n";
    if (peak >= 0) cout << "   peak memory of the process: " << setprecision(1) << peak << " MB\n";

    string csvName = string("benchmark_") + CONTAINER_NAME + ".csv";
    bool newFile = !ifstream(csvName).good();
    ofstream csv(csvName, std::ios::app);
    if (newFile) csv << "container,strategy,records,read_s,sort_s,split_s,write_s,total_s,peak_mem_MB\n";
    csv << fixed << setprecision(4)
        << CONTAINER_NAME << ',' << strategyName(s) << ',' << n << ',' << tRead << ',' << tSort << ','
        << tSplit << ',' << tWrite << ',' << tTotal << ',' << setprecision(1) << peak << '\n';
}

void Test::benchmarkAll(Strategy s) {
    for (size_t n : SIZES) {
        try {
            benchmark(n, s);
        } catch (const runtime_error& e) {
            cerr << "Skipping " << n << ": " << e.what()
                 << " (use option 3 first)\n";
        }
    }
}
