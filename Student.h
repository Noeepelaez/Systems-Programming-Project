#include "lib.h"


    class Student {
        std::string name, surname;
        std:: vector <int> SemPoints;
        int exam;
        
        public:
        
        Student();
        Student(string N, string SN, vector<int> SP, int E);
        Student(const Student &B);
        Student &operator=(const Student &A);
        ~Student(); 

        void print();
        void clear();
        double results();
        double results() const;

        friend ostream& operator << (ostream& out, const Student &A);
    };   