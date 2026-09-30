#include "file.h"

void readStudentsFromFile(vector<Student>& Group) {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    
    string filepath = "files/" + filename;
    ifstream file(filepath); 
    
    if (!file) {
        cout << "Error opening file: " << filepath << "!\n";
        return;
    }
    
    string line;
    getline(file, line);
    
    while (getline(file, line)) {
        if (line.empty()) continue; 
        
        istringstream iss(line);
        string n, sn;
        iss >> n >> sn;
        
        int grade;
        vector<int> sp;
        while (iss >> grade) {
            sp.push_back(grade);
        }
        
        if (!sp.empty()) {
            int examGrade = sp.back();
            sp.pop_back();             
            
            Student s(n, sn, sp, examGrade);
            Group.push_back(s);
        }
    }
    cout << "Data loaded successfully from " << filepath << "\n";
}