#include <iostream>
#include "Admin.h"
#include "Student.h"
using namespace std;

int main() {
    Admin admin("admin", "1234");
    int choice;

    while (true) {
        cout << "\n==== Online Quiz Management System ====\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Student Registration\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                admin.login();
                break;
            case 2: {
                Student student;
                student.login();
                break;
            }
            case 3: {
                Student student;
                student.registerStudent();
                break;
            }
            case 4:
                cout << "\nThank you for using the Quiz System!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
