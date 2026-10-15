#include "lib.h"
#include "Student.h"
#include "file.h"
#include "process.h"
#include "test.h"
#include "exceptions.h"

 int main(){
    try{
        vector <Student> Group;

        int choice;
        cout << "Choose input method:\n";
        cout << "1. Read from file\n";
        cout << "2. Input manually\n";
        cout << "3. Generate the 5 test files(1k to 10M records)\n";
        cout << "4. Speed benchmark on the 5 test files\n";
        cout << "Choice: ";
        if(!(cin >> choice)) throw runtime_error("Invalid menu choice");

        switch(choice){
            case 1: 
                readStudentsFromFile(Group); 
                sortStudents(Group);
                exportCSV("files/results.csv",Group);
                cout << "Exported " << Group.size() << " students to " << "files/results.csv\n";
                return 0;
            case 2:
                while(true){
                    cout << "Do you want to add a student? yY/nN ";
                    char answ;
                    cin >> answ;
                    if(answ == 'n' || answ == 'N') break;
                    
                    Student A;
                    A.readFromConsole(); 
                    Group.push_back(A);
                    A.clear();
                }
                break;
            case 3:
                Test::generateFiles();
                return 0;
            case 4:
                Test::benchmarkAll();
                return 0;
            default:
                cout << "Invalid option selected.\n";
                return 1;
        }

        sortStudents(Group);

        cout << "\n" << left << setw(15) << "Name" << setw(15) << "Surname" << right << setw(15) << "Final (Avg.)" 
        << " | " << left << "Final (Med.)\n";

        cout << string(60, '-') << "\n";

        for(const Student& i : Group){
            i.print();
        }

    }catch(...){
       processException(); 
       return 1;
    }
    return 0;   
 }