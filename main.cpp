#include "lib.h"
#include "Student.h"
#include "file.h"

 int main(){
    vector <Student> Group;

    int choice;
    cout << "Choose input method:\n";
    cout << "1. Read from file\n";
    cout << "2. Input manually\n";
    cout << "Choice: ";
    cin >> choice;

    switch(choice){
        case 1: 
            readStudentsFromFile(Group);
            break;
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
        default:
            cout << "Invalid option selected.\n";
            return 1;
    }

    sort(Group.begin(), Group.end(), [](const Student& a, const Student& b) {
        if (a.getName() == b.getName()) {
            return a.getSurname() < b.getSurname();
        }
        return a.getName() < b.getName();
    });

    cout << "\n" << left << setw(15) << "Name" << setw(15) << "Surname" << right << setw(15) << "Final (Avg.)" 
    << " | " << left << "Final (Med.)\n";

    cout << string(60, '-') << "\n";

    for(const Student& i : Group){
        i.print();
    }      
 }