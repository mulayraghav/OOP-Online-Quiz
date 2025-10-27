#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Quiz.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits> // for numeric_limits
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
            cout << "2. View Questions\n";
            cout << "3. View Student Results\n";
            cout << "4. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

            switch (choice) {
                case 1:
                    addQuestionToFile();
                    break;
                case 2:
                    viewQuestionsFromFile();
                    break;
                case 3:
                    viewResults();
                    break;
                case 4:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }

        } while (choice != 4);
    }

    void addQuestionToFile() {
        ofstream file("questions.txt", ios::app);
        if (!file) {
            cout << "Error opening questions file.\n";
            return;
        }

        string text, options[4];
        char correctOption;

        cout << "\nEnter Question: ";
        getline(cin, text);

        for (int i = 0; i < 4; i++) {
            cout << "Enter Option " << char('A' + i) << ": ";
            getline(cin, options[i]);
        }

        cout << "Enter Correct Option (A/B/C/D): ";
        cin >> correctOption;
        correctOption = toupper(correctOption);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        file << text << endl;
        for (int i = 0; i < 4; i++) file << options[i] << endl;
        file << correctOption << endl;
        file << "---" << endl;

        file.close();
        cout << "\nQuestion added successfully!\n";
    }

    void viewQuestionsFromFile() {
        ifstream file("questions.txt");
        if (!file) {
            cout << "\nNo questions available.\n";
            return;
        }

        string line;
        cout << "\n--- All Questions ---\n";
        int qNo = 1;
        while (getline(file, line)) {
            if (line == "---") {
                cout << "\n";
                qNo++;
            } else {
                cout << line << endl;
            }
        }

        file.close();
    }

    void viewResults() {
        ifstream file("results.txt");
        if (!file) {
            cout << "\nNo results found.\n";
            return;
        }

        cout << "\n--- Student Quiz Results ---\n";
        cout << left << setw(15) << "Student" << setw(15) << "Score"
             << setw(20) << "Date" << setw(10) << "Time" << endl;
        cout << string(60, '-') << endl;

        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

#endif
