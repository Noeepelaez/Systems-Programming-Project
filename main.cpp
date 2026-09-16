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
    for(Student i : Group){
        i.print();
    }      
 }