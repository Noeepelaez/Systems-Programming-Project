#include "lib.h"


    class Student {
        std::string name, surname;
        std:: vector <int> SemPoints;
        int exam;
        
        public:
        
        Student();
        Student(string N, string SN, vector<int> SP, int E);
        Student(const Student &B);
        void print();
        ~Student(); 
        void clear();
        double results();
    };   