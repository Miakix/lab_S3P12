#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Student {
private:
    int id;
    string name;
    int age;
    double grade;
    int course;
    string faculty;
    string groupNumber;

public:
    // Конструктор с параметрами
    Student(int id, string name, int age, double grade, int course, string faculty, string groupNumber)
        : id(id), name(name), age(age), grade(grade), course(course), faculty(faculty), groupNumber(groupNumber) {}

    // Конструктор по умолчанию
    Student() : id(0), name("Unknown"), age(0), grade(0.0), course(1), faculty("Unknown"), groupNumber("Unknow") {}

    // Метод для вывода информации о студенте
    void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age
             << ", Grade: " << grade << ", Course: " << course
             << ", Faculty: " << faculty << ", Group Number: " << groupNumber << endl;
    }

    // Метод для сохранения данных студента в файл в виде одной строки
    void saveToFile(ofstream &file) const {
        if (file.is_open()) {
            file << id << " " << name << " " << age << " " << grade << " "
                 << course << " " << faculty << " " << groupNumber << endl;
        }
    }

    // Метод для редактирования свойств студента
    void editProperty() {
        int choice;
        cout << "Choose property to edit:\n1. ID\n2. Name\n3. Age\n4. Grade\n5. Course\n6. Faculty\n7. Group Number\n8. Cancel\n";
        cin >> choice;
        cin.ignore(); // Пропускаем символ новой строки

        if (choice == 8) {
            cout << "Edit cancelled.\n";
            return;
        }

        switch (choice) {
            case 1: {
                cout << "Enter new ID: ";
                cin >> id;
                break;
            }
            case 2: {
                cout << "Enter new Name: ";
                getline(cin, name);
                break;
            }
            case 3: {
                cout << "Enter new Age: ";
                cin >> age;
                break;
            }
            case 4: {
                cout << "Enter new Grade: ";
                cin >> grade;
                break;
            }
            case 5: {
                cout << "Enter new Course: ";
                cin >> course;
                break;
            }
            case 6: {
                cout << "Enter new Faculty: ";
                getline(cin, faculty);
                break;
            }
            case 7: {
                cout << "Enter new Group Number: ";
                cin >> groupNumber;
                break;
            }
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }

    // Метод для загрузки студента из строки
    static Student fromString(const string &data) {
        istringstream iss(data);
        int id, age, course;
        double grade;
        string name, faculty, groupNumber;
        iss >> id >> name >> age >> grade >> course >> faculty >> groupNumber;
        return Student(id, name, age, grade, course, faculty, groupNumber);
    }
};

// Функция для загрузки всех студентов из файла
vector<Student> loadStudentsFromFile(const string &filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            students.push_back(Student::fromString(line));
        }
    }
    file.close();
    return students;
}

// Функция для сохранения всех студентов в файл в одной строке на студента
void saveAllStudents(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Student& student : students) {
            student.saveToFile(file);
        }
        file.close();
        cout << "All student data saved to " << filename << endl;
    } else {
        cerr << "Unable to open file for writing." << endl;
    }
}

// Функция для создания студента с вводом данных от пользователя
Student createStudent() {
    int id, age, course;
    double grade;
    string name, faculty, groupNumber;

    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Grade: ";
    cin >> grade;
    cout << "Enter Course: ";
    cin >> course;
    cout << "Enter Faculty: ";
    cin.ignore();
    getline(cin, faculty);
    cout << "Enter Group Number: ";
    cin >> groupNumber;

    return Student(id, name, age, grade, course, faculty, groupNumber);
}

// Основная программа
int main() {
    string filename = "students.txt";
    vector<Student> students = loadStudentsFromFile(filename);

    // Вывод данных всех студентов, загруженных из файла
    cout << "Current students in file:\n";
    for (size_t i = 0; i < students.size(); ++i) {
        cout << "Student " << i + 1 << " Information:\n";
        students[i].display();
    }

    char choice;
    do {
        // Создание и добавление нового студента
        Student student = createStudent();
        students.push_back(student);

        // Сохранение всех студентов в файл
        saveAllStudents(students, filename);

        cout << "Do you want to add another student? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    // Редактирование данных существующего студента
    int index;
    cout << "\nEnter the index of the student to edit (1 to " << students.size() << ", or 0 to cancel): ";
    cin >> index;
    if (index < 1 || index > students.size()) {
        if (index == 0) {
            cout << "Edit cancelled.\n";
        } else {
            cout << "Invalid index." << endl;
        }
    } else {
        // Отображение данных выбранного студента перед редактированием
        cout << "\nStudent " << index << " Information before editing:\n";
        students[index - 1].display();

        // Редактирование данных выбранного студента
        cout << "\nEdit Student " << index << " Information:\n";
        students[index - 1].editProperty();

        // Повторное сохранение всех студентов в файл
        saveAllStudents(students, filename);

        // Повторное отображение обновлённой информации
        cout << "\nUpdated Student Information:\n";
        students[index - 1].display();
    }

    return 0;
}

