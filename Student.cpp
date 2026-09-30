#include "Student.h"
#include "lib.h"
        
        static int randomInt(int from, int to){
            static mt19937P gen(random_device{}());
            uniform_int_distribution<int> dist(from,to);
            return dist(gen);
        }

        Student::Student(){
            cout<<"Input name: "; cin >> name;
            cout<<"Input surname: "; cin >> surname;
            SemPoints.clear();

            cout<< "Do you want to generate homework and exam points randomly? yY/nN ";
            char rnd;
            cin>> rnd;

            if(rnd == 'y' || rnd == 'Y'){
                int count;
                cout<< "How many homework results? ";
                cin>>count;
                for(int i = 0; i < count; i++){
                    SemPoints.push_back(randomInt(1,10));
                }
                exam = randomInt(1,10);

                cout<< "Generated random work: ";
                for(int point : SemPoints){
                    cout<< point << " ";
                }
                cout<< "| exam: " << exam << "\n";
            }else{
                cout << "Input a Semester point: ";
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
           out << left << setw(15) << A.name << setw(15) << A.surname << right << setw(15) << A.resultsAverage();
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

        double Student:: average() const {
            if (SemPoints.size() == 0 ) return 0;

            return accumulate(SemPoints.begin(), SemPoints.end(),0.0) / (double) SemPoints.size();
        }

        double Student:: median() const {
             if (SemPoints.size() == 0 ) return 0;

             vector<int> points = SemPoints;
             sort(points.begin(),points.end());

             if(points.size() % 2 == 1) return points[points.size()/2];
             
             return (points[points.size() / 2 - 1] + points[points.size() / 2]) / 2;
        }

        double Student:: resultsAverage() const{
          return 0.4 * average() + 0.6 * exam;
        };

        double Student:: resultsMedian()const{
          return 0.4 * median() + 0.6 * exam;  
        }

       



        