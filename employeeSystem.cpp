#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct dateEmployed {
    int month,
        day,
        year;
};

struct Employee {
    string name;
    int age;
    dateEmployed date;
};

Employee *readEmployees(const string &empFile, int &numEmps);
void displayEmployees(const Employee emps[], int numEmps);
Employee *inputEmployees(Employee *emps, int &numEmps);


int main() {
    string empFile = "Employees.txt";
    int numEmps;
    fstream f;
    char entry;

    f.open(empFile, ios::in);

    while (f.is_open()) {
        f >> numEmps;
        f.close();

        Employee *emps = readEmployees(empFile, numEmps);
        displayEmployees(emps, numEmps);

        cout << "\nAny additional employees need to be added? (Y/N)" << endl;
        cin >> entry;
        entry = toupper(entry);

        if (entry == 'Y') {
            Employee *newEmps = inputEmployees(emps, numEmps);
            displayEmployees(newEmps, numEmps);

            delete[] emps;
            emps = nullptr;
            delete[] newEmps;
            newEmps = nullptr;
        } else {
            delete[] emps;
            emps = nullptr;

            break;
        }
    }
    if (!f)
        cerr << "Error: Unable to open file\n";

    return 0;
}

Employee *readEmployees(const string &empFile, int &numEmps) {
    fstream f;

    f.open(empFile, ios::in);
    Employee *tmp = new Employee[numEmps];
    f.ignore(2);

    for (int i = 0; i < numEmps; ++i) {
        getline(f, tmp[i].name, ',');
        f >> tmp[i].age;
        f.ignore();
        f >> tmp[i].date.month;
        f.ignore();
        f >> tmp[i].date.day;
        f.ignore();
        f >> tmp[i].date.year;
        f.ignore();
    }

    f.close();

    return tmp;
}

Employee *inputEmployees(Employee *emps, int &numEmps) {
    fstream f;
    int newEntries,
        oldEmps = numEmps,
        age,
        month,
        day,
        year;
    string name;

    cout << "\nHow many?" << endl;
    cin >> newEntries;

    cin.ignore();
    Employee *newemps = new Employee[numEmps + newEntries];

    for (int i = 0; i < numEmps; i++) {
        newemps[i].name = emps[i].name;
        newemps[i].age = emps[i].age;
        newemps[i].date.month = emps[i].date.month;
        newemps[i].date.day = emps[i].date.day;
        newemps[i].date.year = emps[i].date.year;
    }

    numEmps = numEmps + newEntries;

    f.open("Employees.txt", ios::out);
    f << numEmps << endl;

    for (int i = 0; i < numEmps - newEntries; ++i)
        f << newemps[i].name << ","
          << newemps[i].age << ","
          << newemps[i].date.month
          << "/" << newemps[i].date.day
          << "/" << newemps[i].date.year << endl;

    f.close();

    f.open("Employees.txt", ios::app);

    for (int i = oldEmps; i < numEmps; ++i) {
        cout << "\nName: ";
        getline(cin, name);

        cout << "Age: ";
        cin >> age;

        cout << "\nDate Employed\n"
             << "Month: ";
        cin >> month;

        cout << "Day: ";
        cin >> day;

        cout << "Year: ";
        cin >> year;

        cin.ignore();
        newemps[i].name = name;
        newemps[i].age = age;
        newemps[i].date.month = month;
        newemps[i].date.day = day;
        newemps[i].date.year = year;
        f << newemps[i].name << ","
          << newemps[i].age << ","
          << newemps[i].date.month
          << "/" << newemps[i].date.day
          << "/" << newemps[i].date.year << endl;
    }
    f.close();

    return newemps;
}

void displayEmployees(const Employee emps[], int numEmps) {
    cout << left << setw(30) << "\nName" << setw(20) << "Age" << setw(10) << "Date Employed" << endl;

    cout << setfill('-') << setw(63) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < numEmps; ++i)
        cout << left
             << setw(30) << emps[i].name
             << setw(23) << emps[i].age
             << right << setw(10)
             << setw(2) << emps[i].date.month << "/"
             << setw(2) << emps[i].date.day << "/"
             << setw(4) << emps[i].date.year << endl;
}