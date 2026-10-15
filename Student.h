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
        ~Student(); 
        void clear();

        friend ostream &operator << (ostream &out, const Student &A);
        friend istream &operator >> (istream &in, Student &A);
        void print() const;
        
        double average() const;
        double median() const;
        double resultsAverage() const;
        double resultsMedian() const;

        string getName() const {return name;}
        string getSurname() const {return surname;}
        size_t getSemPointsCount() const {return SemPoints.size();}
        int getPoint(size_t i) const;

        void readFromConsole();
        
    };   