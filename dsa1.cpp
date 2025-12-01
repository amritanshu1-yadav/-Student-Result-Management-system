#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Student {
public:
    int roll;
    string name;
    vector<int> marks;
    int total;
    float percentage;

    Student() {
        total = 0;
        percentage = 0;
    }

    void calculateResult() {
        total = 0;
        for (int m : marks)
            total += m;
        percentage = total / 5.0;
    }

    string toCSV() {
        stringstream ss;
        ss << roll << "," << name;
        for (int m : marks)
            ss << "," << m;
        ss << "," << total << "," << percentage;
        return ss.str();
    }

    static Student fromCSV(string line) {
        Student s;
        stringstream ss(line);
        string value;

        getline(ss, value, ',');
        s.roll = stoi(value);

        getline(ss, s.name, ',');

        for (int i = 0; i < 5; i++) {
            getline(ss, value, ',');
            s.marks.push_back(stoi(value));
        }

        getline(ss, value, ',');
        s.total = stoi(value);

        getline(ss, value, ',');
        s.percentage = stof(value);

        return s;
    }
};

vector<Student> students;

void saveToFile() {
    ofstream fout("students.csv");
    for (auto &s : students)
        fout << s.toCSV() << endl;
    fout.close();
}

void loadFromFile() {
    students.clear();
    ifstream fin("students.csv");
    string line;
    while (getline(fin, line)) {
        students.push_back(Student::fromCSV(line));
    }
    fin.close();
}

void addStudent() {
    Student s;
    cout << "\nEnter Roll Number: ";
    cin >> s.roll;
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter 5 Subject Marks:\n";
    for (int i = 0; i < 5; i++) {
        int m;
        cout << "Subject " << i + 1 << ": ";
        cin >> m;
        s.marks.push_back(m);
    }

    s.calculateResult();
    students.push_back(s);
    saveToFile();

    cout << "✅ Student Record Added Successfully!\n";
}

void viewStudents() {
    cout << "\n========== STUDENT RECORDS ==========\n";
    for (auto &s : students) {
        cout << "\nRoll No: " << s.roll;
        cout << "\nName: " << s.name;
        cout << "\nMarks: ";
        for (int m : s.marks)
            cout << m << " ";
        cout << "\nTotal: " << s.total;
        cout << "\nPercentage: " << s.percentage << "%\n";
        cout << "---------------------------------\n";
    }
}

void searchStudent() {
    int r;
    cout << "\nEnter Roll Number to Search: ";
    cin >> r;

    for (auto &s : students) {
        if (s.roll == r) {
            cout << "\n✅ Student Found!";
            cout << "\nName: " << s.name;
            cout << "\nTotal: " << s.total;
            cout << "\nPercentage: " << s.percentage << "%\n";
            return;
        }
    }

    cout << "❌ Student Not Found!\n";
}

int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n====== STUDENT RESULT MANAGEMENT SYSTEM ======\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            cout << "✅ Exiting Program...\n";
            break;
        default:
            cout << "❌ Invalid Choice!\n";
        }
    } while (choice != 4);

    return 0;
}
