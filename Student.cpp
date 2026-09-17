#include "Student.h"
#include "lib.h"
        
        Student::Student(){
            cout<<"Input name: "; cin >> name;
            cout<<"Input surname: "; cin >> surname;
            int n;
            cout << "Input Semester points";
            while(true){
                cin >>n;
                SemPoints.push_back(n);
                cout<<"want to input another point? yY/nN ";
                char answ; cin >> answ;
                if(answ == 'n' || answ == 'N') break;
            }
            cout << "Input final exam point: ";
            cin >> exam;
        }
        
        Student::Student(string N, string SN, vector<int> SP, int E){
            name = N;
            surname = SN;
            SemPoints = SP;
            exam = E;
        }

        Student::Student(const Student &B){
            name = B.name;
            surname = B.surname;
            SemPoints = B.SemPoints;
            exam = B.exam;
        }

        Student &Student::operator=(const Student &A)
        {
            if (this != &A){
                name = A.name;
                surname = A.surname;
                SemPoints = A.SemPoints;
                exam = A.exam;
            } 
            return *this;
        }

        void Student::print(){
            cout<<name<<"|"<<surname<<"|";
            cout <<"[";
            for(int a : SemPoints) cout <<a<<"|";
            cout<<"] ";
            cout<<"|"<<exam<<"\n";
        }
        
        Student::~Student(){
            clear();
        } 
        
        void Student::clear(){
            name.clear();
            surname.clear();
            SemPoints.clear();
            exam = 0;
        }

        double Student:: results(){
            if(SemPoints.size() == 0) return exam;
            return 0.4 * accumulate(SemPoints.begin(), SemPoints.end(), 0.0) / (double)SemPoints.size() + 0.6 * exam;
        }

        ostream& operator << (ostream& out, const Student &A){
            out << A.name << "|" << A.surname << "|" << A.exam << "|       |" << A.results() << "\n";
            return out;
        }

        istream& operator >> (istream&, Student &A){

        }