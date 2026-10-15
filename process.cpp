#include "process.h"
#include "Student.h"
static bool byName(const Student& a, const Student& b) {
    if (a.getName() == b.getName()) {
        return a.getSurname() < b.getSurname();
    }
    return a.getName() < b.getName();
}

void sortStudents(list<Student>& Group) {
    Group.sort(byName);
}

void splitStudents(list<Student> &all, list<Student> &passed, list<Student> &failed) {
    for (Student &s : all) {
        bool ok = s.resultsAverage() >= PASS_MARK;     
        (ok ? passed : failed).push_back(move(s));
    }
}