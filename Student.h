#pragma once
#include "lib.h"


    class Student {

        string name, surname;
        vector <int> SemPoints;
        int exam;

        public:

        Student();
        Student(const string &N,const string &SN,const vector<int> &SP, int E);
        Student(const Student &B);
        Student &operator=(const Student &A);
        Student(Student &&B) noexcept;              // v1.0: move constructor
        Student &operator=(Student &&A) noexcept;   // v1.0: move assignment
        ~Student();
        void clear();

        friend ostream &operator << (ostream &out, const Student &A);
        friend istream &operator >> (istream &in, Student &A);
        void print() const;

        double average() const;
        double median() const;
        double resultsAverage() const;
        double resultsMedian() const;

        // v1.0: return a const reference (no string copy). The sort comparator calls
        // these several times per comparison, i.e. millions of times.
        const string &getName() const {return name;}
        const string &getSurname() const {return surname;}
        size_t getSemPointsCount() const {return SemPoints.size();}
        int getPoint(size_t i) const;

        void readFromConsole();

    };
