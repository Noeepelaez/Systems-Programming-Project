#include "lib.h"
#include "Student.h"

 int main(){
    vector <Student> Group;
    while(true){
        cout<<"Do you want to add a student? yY/nN ";
        char answ;
        cin >> answ;
        if(answ == 'n' || answ == 'N') break;
        Student A;
        Group.push_back(A);
        A.clear();
    }
    

    cout << "Final Grade: Use (A)verage or (M) as calculation method: ";
    char method;
    cin>> method;
    bool useMedian = 'm' == method || 'M' == method;
    cout<<"Final Grade calculation using: " << (useMedian ? "MEDIAN" : "AVERAGE") << "\n\n";

    cout << left << setw(15) << "Name" 
        << setw(15) << "Surname" 
        << right << setw(15) << (useMedian ? "Final_Point(Med.)" : "Final_Point(Med.)")<<"\n";

    cout << string(45, '-') << "\n";

    for(const Student& i : Group){
        i.print(useMedian);
    }      
 }