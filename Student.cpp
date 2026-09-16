#include "Student.h"
#include "lib.h"
        
        Student::Student(){
            cout<<"Input name: "; cin >> name;
            cout<<"Input surname: "; cin >> surname;
            int n;
            cout << "Input a point ";
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
        
        void Student::print(){
            cout<<name<<"|"<<surname<<"|";
            cout <<"[";
            for(int a : SemPoints) cout <<a<<"|";
            cout<<"] ";
            cout<<"|"<<exam<<"\n";
        }
        
        Student::~Student(){
            name.clear();
            surname.clear();
            SemPoints.clear();
            exam = 0;
        } 
        
        void Student::clear(){
            name.clear();
            surname.clear();
            SemPoints.clear();
            exam = 0;
        }

        double Student:: results(){
            return 0.4 * accumulate(SemPoints.begin(), SemPoints.end(), 0.0) / SemPoints.size() + 0.6 * exam;
        }