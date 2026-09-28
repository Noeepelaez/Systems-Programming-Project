#include "Student.h"
#include "lib.h"
        
        Student::Student(){
            cout<<"Input name: "; cin >> name;
            cout<<"Input surname: "; cin >> surname;
            SemPoints.clear();
            
            cout << "Input a Semester point";
            while(true){
                int n;
                cin >>n;
                SemPoints.push_back(n);
                cout<<"want to input another point? yY/nN ";
                char answ;
                 cin >> answ;
                if(answ == 'n' || answ == 'N') break;
                cout << "Input a Semester point: ";
            }
            cout << "Input final exam point: ";
            cin >> exam;
        }
        
        Student::Student(string &N, string &SN, vector<int> &SP, int &E){
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

        void Student::print() const{
            cout << *this << "\n";
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

        ostream &operator << (ostream &out, const Student &A) {
           out << left << setw(15) << A.name << setw(15) << A.surname << right << setw(15) << A.results();
            return out;
        }

        istream &operator >> (istream &in, Student &A){
            in >> A.name >> A.surname;
            int n;
            cout << "Input a Semester point: ";
            while (cin >> n){
                A.SemPoints.push_back(n);   
            }
            cin.clear();
            cin.ignore(100,'\n');
            return in;
        }

        double Student:: results() const{
          if(SemPoints.size() == 0) return 0.6 * exam;
          
          return 0.4 * accumulate(SemPoints.begin(), SemPoints.end(),0.0) / (double) SemPoints.size() + 0.6 * exam;
        };

       



        