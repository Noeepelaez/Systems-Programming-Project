#include "file.h"

void readStudentsFromFile(deque<Student>& Group) {
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    
    string filepath = "files/" + filename;
    deque<Student> loaded = readStudentsFromPath(filepath);

    for(Student &s : loaded) Group.push_back(move(s));
    cout<<"Data loaded succesfully from " <<filepath<< "\n";
}

deque<Student> readStudentsFromPath(const string &filepath){
    ifstream file(filepath); 
    
    if (!file) throw ios_base::failure("Cannot open file: " + filepath);
    
    deque<Student> Group;
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
    return Group;
}

void exportCSV(const string& filepath, const deque<Student>& Group) {
    ofstream fout(filepath);
    if (!fout) throw ios_base::failure("Cannot create file: " + filepath);

    fout << "Name,Surname,Final_Avg,Final_Med\n";
    fout << fixed << setprecision(2);
    for (const Student& s : Group)
        fout << s.getName() << ',' << s.getSurname() << ','
             << s.resultsAverage() << ',' << s.resultsMedian() << '\n';

    if (!fout) throw ios_base::failure("Error while writing file: " + filepath);
}

void writeStudentsToFile(const string& filepath, const deque<Student> &Group) {
    ofstream fout(filepath);
    if (!fout) throw runtime_error("Cannot create file: " + filepath);

    fout << left << setw(16) << "Name" << setw(16) << "Surname" << "Final(Avg.)\n";
    fout << fixed << setprecision(2);
    for (const Student &s : Group)
        fout << left << setw(16) << s.getName() << setw(16) << s.getSurname()
             << s.resultsAverage() << '\n';

    if (!fout) throw ios_base::failure("Error while writing file: " + filepath);
}

void generateStudentsFile(const string &filepath, size_t count, int numSemPoints){
    ofstream fout(filepath);
    if (!fout) throw ios_base::failure("Cannot create file: " + filepath);

    mt19937 gen(random_device{}());
    uniform_int_distribution<int> dist(1, 10);

    fout << "Name Surname";
    for (int i = 1; i <= numSemPoints; ++i) fout << " HW" << i;
    fout << " Exam\n";

    for (size_t i = 1; i <= count; ++i) {
        fout << "Name" << i << " Surname" << i;
        for (int j = 0; j < numSemPoints; ++j) fout << ' ' << dist(gen);
        fout << ' ' << dist(gen) << '\n';
    }

    if (!fout) throw ios_base::failure("Error while writing file: " + filepath);
}
