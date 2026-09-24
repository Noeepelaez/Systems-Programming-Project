#pragma once
#include "lib.h"


    class Student {

        string name, surname;
        vector <int> SemPoints;
        int exam;
        
        public:
        
        Student();
        Student(string &N, string &SN, vector<int> &SP, int &E);
        Student(const Student &B);
        Student &operator=(const Student &A);
        ~Student(); 
        void clear();

        friend ostream &operator << (ostream &out, const Student &A);
        friend istream &operator >> (istream &in, Student &A);
        void print() const;
        
        double results() const;
  


        
    };   