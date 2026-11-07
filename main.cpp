#include "lib.h"
#include "Student.h"
#include "container.h"
#include "file.h"
#include "process.h"
#include "test.h"
#include "exceptions.h"

 int main(){
    try{
        Container Group;

        int choice;
        cout << "Container: " << CONTAINER_NAME << "\n";
        cout << "Choose input method:\n";
        cout << "1. Read from file\n";
        cout << "2. Input manually\n";
        cout << "3. Generate the 5 test files(1k to 10M records)\n";
        cout << "4. Speed benchmark on the 5 test files (choose split strategy)\n";
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
                    Group.push_back(move(A));
                }
                break;
            case 3:
                Test::generateFiles();
                return 0;
            case 4: {
                cout << "Choose how to split the students into passed / failed:\n";
                cout << "1. Strategy 1: two new containers (students are copied)\n";
                cout << "2. Strategy 2: one new container (failed students moved out and erased)\n";
                cout << "3. Strategy 1 using <algorithm> (remove_copy_if + copy_if)\n";
                cout << "4. Strategy 2 using <algorithm> (stable_partition)\n";
                cout << "5. Strategy 2 using <algorithm> (partition, then sort the two groups)\n";
                cout << "6. Strategy 2 using <algorithm> (find_if + list::splice, list only)\n";
                cout << "7. Run all of them\n";
                cout << "Choice: ";
                int st;
                if(!(cin >> st) || st < 1 || st > 7) throw invalid_argument("Invalid strategy choice");

                if(st == 7){
                    for(int i = 1; i <= 6; ++i) Test::benchmarkAll(static_cast<Strategy>(i));
                } else {
                    Test::benchmarkAll(static_cast<Strategy>(st));
                }
                return 0;
            }
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
