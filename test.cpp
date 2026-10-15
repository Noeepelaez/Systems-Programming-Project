#include "test.h"
#include "Student.h"
#include "file.h"
#include "process.h"
#include "exceptions.h"

static const vector<size_t> SIZES = {1000, 10000, 100000, 1000000, 10000000};

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

void Test::benchmark(size_t n) {
    string path = pathFor(n);
    string base = path.substr(0, path.size() - 4);          

    Timer total, t;

    vector<Student> all = readStudentsFromPath(path);            
    double tRead = t.elapsed();

    t.reset();
    sortStudents(all);
    double tSort = t.elapsed();

    t.reset();
    vector<Student> passed, failed;
    splitStudents(all, passed, failed);
    double tSplit = t.elapsed();

    t.reset();
    writeStudentsToFile(base + "_passed.txt", passed);
    writeStudentsToFile(base + "_failed.txt", failed);
    double tWrite = t.elapsed();

    double tTotal = total.elapsed();

    cout << fixed << setprecision(4);
    cout << "["  << n << " records  (passed " << passed.size()
         << ", failed " << failed.size() << ")\n"
         << "   read  : " << tRead  << " s\n"
         << "   sort  : " << tSort  << " s\n"
         << "   split : " << tSplit << " s\n"
         << "   write : " << tWrite << " s\n"
         << "   TOTAL : " << tTotal << " s\n";

    string csvName = string("benchmark_vector.csv");
    bool newFile = !ifstream(csvName).good();
    ofstream csv(csvName, std::ios::app);
    if (newFile) csv << "container,records,read_s,sort_s,split_s,write_s,total_s\n";
    csv << "vector" << ',' << n << ',' << tRead << ',' << tSort << ','
        << tSplit << ',' << tWrite << ',' << tTotal << '\n';
}

void Test::benchmarkAll() {
    for (size_t n : SIZES) {
        try {
            benchmark(n);
        } catch (const runtime_error& e) {
            cerr << "Skipping " << n << ": " << e.what()
                 << " (use option 3 first)\n";
        }
    }
}
