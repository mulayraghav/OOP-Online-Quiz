#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Quiz.h"
#include <iostream>
using namespace std;

class Admin : public User {
public:
    Admin(string uname = "admin", string pass = "1234") : User(uname, pass) {}

    void login() override {
        string u, p;
        cout << "\n[Admin Login]\n";
        cout << "Enter Username: ";
        cin >> u;
        cout << "Enter Password: ";
        cin >> p;

        if (u == username && p == password) {
            cout << "\nLogin Successful!\n";
            menu();
        } else {
            cout << "\nInvalid Credentials!\n";
        }
    }

    void menu() {
        int choice;
        Quiz quiz;
        quiz.loadQuestions();

        do {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Add Question\n";
            cout << "2. Edit Question\n";
            cout << "3. Delete Question\n";
            cout << "4. View Questions\n";
            cout << "5. Shuffle Questions\n";
            cout << "6. View Student Results\n";
            cout << "7. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1:
                    quiz.addQuestion();
                    break;
                case 2:
                    quiz.editQuestion();
                    break;
                case 3:
                    quiz.deleteQuestion();
                    break;
                case 4:
                    quiz.displayAll();
                    break;
                case 5:
                    quiz.shuffleQuestions();
                    cout << "\nQuestions shuffled successfully!\n";
                    break;
                case 6:
                    viewResults();
                    break;
                case 7:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }

        } while (choice != 7);
    }

    void viewResults() {
        ifstream file("results.txt");
        if (!file) {
            cout << "\nNo results found.\n";
            return;
        }

        cout << "\n--- Student Quiz Results ---\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

#endif
