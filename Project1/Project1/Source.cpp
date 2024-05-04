#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

enum Specialnist { KN, ME, IN, FI, TN };
string specialnistList[] = { "KN", "ME", "IN", "FI", "TN" };

struct Student {
    char surname[101];
    int course;
    Specialnist spec;
    int fiz;
    int mat;
    double average;
    union {
        int prog;
        int chis_metod;
        int pedagog;
    };
};

void Create(char* fname);
void Print(char* fname);
void Sort(char* fname);
void IndexSort(char* fname, char* gname);
void PhysicalSort(char* fname);
bool BinarySearch(char* fname, string surname, int course, int grade);

int main() {
    char fname[61];
    int menuItem;
    do {
        cout << endl << "Choose an action:" << endl << endl;
        cout << " [1] - Entering data from the keyboard and saving" << endl;
        cout << " [2] - loading and displaying data" << endl;
        cout << " [3] - Sorting" << endl;
        cout << " [4] - Index sorting and output" << endl;
        cout << " [5] - Binary search for a student" << endl;
        cout << " [0] - Quit" << endl << endl;
        cout << "Enter the value: "; cin >> menuItem;
        cout << endl << endl;
        switch (menuItem) {
        case 1:
            cin.get();
            cin.sync();
            cout << "Enter a file name: "; cin.getline(fname, sizeof(fname));
            Create(fname);
            break;
        case 2:
            cin.get();
            cin.sync();
            cout << "Enter a file name: "; cin.getline(fname, sizeof(fname));
            Print(fname);
            break;
        case 3:
            cin.get();
            cin.sync();
            cout << "Enter a file name: "; cin.getline(fname, sizeof(fname));
            PhysicalSort(fname);
            cout << "Table was sorted!";
            break;
        case 4: {
            char gname[61];
            cin.get();
            cin.sync();
            cout << "File name: "; cin.getline(fname, sizeof(fname));
            cout << endl << "Output file name: "; cin.getline(gname, sizeof(gname));
            IndexSort(fname, gname);
            cout << "Sorted file created!" << endl << endl;
            Print(gname);
            cout << endl;
            break;
        }
        case 5: {
            string searchSurname;
            int searchCourse, searchGrade;
            cout << "Enter the surname to search: "; cin >> searchSurname;
            cout << "Enter the course to search: "; cin >> searchCourse;
            cout << "Enter the grade to search: "; cin >> searchGrade;
            bool found = BinarySearch(fname, searchSurname, searchCourse, searchGrade);
            if (found)
                cout << "Student found!" << endl;
            else
                cout << "Student not found!" << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid value" << endl;
        }
    } while (menuItem != 0);
    return 0;
}

void Create(char* fname) {
    ofstream f(fname, ios::binary | ios::app);
    if (!f) {
        cerr << "Error opening file '" << fname << "'" << endl;
        f.close();
        return;
    }
    int spec;
    Student p;
    char ch;
    do {
        cout << "Surname: "; cin >> p.surname;
        cout << "Course: "; cin >> p.course;
        cout << "Grades in physics: "; cin >> p.fiz;
        cout << "Grades in math: "; cin >> p.mat;
        cout << "A specialty (0 - KN, 1 - ME, 2 - IN, 3 - FI, 4 - TN): "; cin >> spec;
        if (spec > 4) {
            cout << "Wrong value, selected 2 (IN)" << endl;
            spec = 0;
        }
        p.spec = (Specialnist)spec;
        switch (p.spec) {
        case KN:
            cout << "Grades in programming: "; cin >> p.prog;
            p.average = (p.mat + p.fiz + p.prog) / 3.0;
            break;
        case ME:
            cout << "Grades in pedagogy: "; cin >> p.pedagog;
            p.average = (p.mat + p.fiz + p.pedagog) / 3.0;
            break;
        case IN:
            cout << "Grades in num.methods: "; cin >> p.chis_metod;
            p.average = (p.mat + p.fiz + p.chis_metod) / 3.0;
            break;
        case FI:
        case TN:
            cout << "Grades in pedagogy: "; cin >> p.pedagog;
            p.average = (p.mat + p.fiz + p.pedagog) / 3.0;
            break;
        }
        f.write((char*)&p, sizeof(Student));
        cout << "Continue? (Y/N) "; cin >> ch;
    } while (ch == 'Y' || ch == 'y');
    f.close();
}

void Print(char* fname) {
    ifstream f(fname, ios::binary);
    if (!f) {
        cerr << "Error opening file '" << fname << "'" << endl;
        f.close();
        return;
    }
    Student student;
    int i = 0;
    cout << "==========================================================================================================="
        << endl;
    cout << "| # | Surname | Course | Specialization | Physic | Mathematics | Programming | Numerical Methods | Pedagogy |"
        << endl;
    cout << "-----------------------------------------------------------------------------------------------------------"
        << endl;
    while (f.read((char*)&student, sizeof(Student))) {
        cout << "|" << setw(2) << right << i + 1 << " ";
        cout << "| " << setw(8) << left << student.surname
            << "| " << setw(4) << right << student.course << "  "
            << " | " << setw(4) << left << specialnistList[student.spec] << " "
            << "| " << setw(5) << right << student.fiz << "  "
            << "| " << setw(11) << right << student.mat << "  ";
        switch (student.spec) {
        case KN:
            cout << "| " << setw(6) << right << student.prog << "            |"
                << setw(18) << right << "                  |" << endl;
            break;
        case ME:
            cout << "| " << setw(18) << right << "                  |"
                << setw(6) << right << student.pedagog << "            |" << endl;
            break;
        case IN:
            cout << "| " << setw(18) << right << "                  |"
                << setw(18) << right << student.chis_metod << "            |" << endl;
            break;
        case FI:
        case TN:
            cout << "| " << setw(18) << right << "                  |"
                << setw(6) << right << student.pedagog << "            |" << endl;
            break;
        }
        i++;
    }
    cout << "==========================================================================================================="
        << endl;
    cout << endl;
    f.close();
}

void Sort(char* fname) {
    ifstream f(fname, ios::binary);
    if (!f) {
        cerr << "Error opening file '" << fname << "'" << endl;
        f.close();
        return;
    }
    f.seekg(0, ios::end);
    int size = f.tellg();
    size = size / sizeof(Student);
    f.seekg(0, ios::beg);
    Student* students = new Student[size];
    f.read((char*)students, size * sizeof(Student));
    f.close();
    for (int i = 0; i < size - 1; i++) {
        for (int j = size - 1; j > i; j--) {
            if ((students[j].average > students[j - 1].average) ||
                (students[j].average == students[j - 1].average && students[j].course > students[j - 1].course) ||
                (students[j].average == students[j - 1].average && students[j].course == students[j - 1].course && strcmp(students[j].surname, students[j - 1].surname) > 0)) {
                swap(students[j], students[j - 1]);
            }
        }
    }
    ofstream file(fname, ios::binary);
    file.write((char*)students, size * sizeof(Student));
    file.close();
    delete[] students;
}

void PhysicalSort(char* fname) {
    ifstream f(fname, ios::binary);
    if (!f) {
        cerr << "Error opening file '" << fname << "'" << endl;
        f.close();
        return;
    }
    f.seekg(0, ios::end);
    int size = f.tellg();
    size = size / sizeof(Student);
    f.seekg(0, ios::beg);
    vector<Student> students(size);
    f.read((char*)students.data(), size * sizeof(Student));
    f.close();
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.average != b.average)
            return a.average > b.average;
        if (a.course != b.course)
            return a.course > b.course;
        return strcmp(a.surname, b.surname) > 0;
        });
    ofstream file(fname, ios::binary);
    file.write((char*)students.data(), size * sizeof(Student));
    file.close();
}

void IndexSort(char* fname, char* gname) {
    ifstream f(fname, ios::binary);
    if (!f) {
        cerr << "Error opening file '" << fname << "'" << endl;
        f.close();
        return;
    }
    f.seekg(0, ios::end);
    int size = f.tellg();
    size = size / sizeof(Student);
    f.seekg(0, ios::beg);
    vector<Student> students(size);
    f.read((char*)students.data(), size * sizeof(Student));
    f.close();
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.average != b.average)
            return a.average > b.average;
        if (a.course != b.course)
            return a.course > b.course;
        return strcmp(a.surname, b.surname) < 0;
        });
    ofstream file(gname, ios::binary);
    file.write((char*)students.data(), size * sizeof(Student));
    file.close();
}

bool BinarySearch(char* fname, string surname, int course, int grade) {
    ifstream f(fname, ios::binary);
    if (!f) {
        cerr << "Error opening file '" << fname << "'" << endl;
        f.close();
        return false;
    }
    Student student;
    int low = 0, high;
    f.seekg(0, ios::end);
    high = f.tellg() / sizeof(Student) - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        f.seekg(mid * sizeof(Student), ios::beg);
        f.read((char*)&student, sizeof(Student));
        if (strcmp(student.surname, surname.c_str()) == 0 && student.course == course &&
            (student.prog == grade || student.chis_metod == grade || student.pedagog == grade)) {
            f.close();
            return true;
        }
        else if (strcmp(student.surname, surname.c_str()) < 0 || (strcmp(student.surname, surname.c_str()) == 0 && student.course < course) ||
            (strcmp(student.surname, surname.c_str()) == 0 && student.course == course && student.chis_metod < grade)) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    f.close();
    return false;
}
