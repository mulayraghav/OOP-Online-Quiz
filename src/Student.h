#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Quiz.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

class Student : public User {
public:
    Student(string uname = "", string pass = "") : User(uname, pass) {}

    void registerStudent() {
        cout << "\n[Student Registration]\n";
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ofstream file("students.txt", ios::app);
        if (!file) {
            cout << "Error opening student file.\n";
            return;
        }
        file << username << " " << password << endl;
        file.close();

        cout << "\nRegistration successful! You can now log in.\n";
    }

    void login() override {
        cout << "\n[Student Login]\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream file("students.txt");
        if (!file) {
            cout << "No registered students found. Please register first.\n";
            return;
        }

        string u, p;
        bool found = false;
        while (file >> u >> p) {
            if (u == username && p == password) {
                found = true;
                break;
            }
        }
        file.close();

        if (found) {
            cout << "\nLogin successful!\n";
            studentMenu();
        } else {
            cout << "\nInvalid credentials. Try again or register first.\n";
        }
    }

    void studentMenu() {
        int choice;
        Quiz quiz;
        quiz.loadQuestions();

        do {
            cout << "\n--- Student Menu ---\n";
            cout << "1. Attempt Quiz\n";
            cout << "2. View Results\n";
            cout << "3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1)
                attemptQuiz(quiz);
            else if (choice == 2)
                viewResults();
            else if (choice == 3)
                cout << "Logging out...\n";
            else
                cout << "Invalid choice! Try again.\n";

        } while (choice != 3);
    }

    void attemptQuiz(Quiz& quiz) {
        int total = quiz.getQuestionCount();
        if (total == 0) {
            cout << "No questions available.\n";
            return;
        }

        cout << "\nStarting Quiz...\n";
        int score = 0;
        char ans;
        for (int i = 0; i < total; i++) {
            Question q = quiz.getQuestion(i);
            cout << "\nQ" << i + 1 << ": " << q.text << endl;
            for (int j = 0; j < 4; j++)
                cout << "  " << char('A' + j) << ") " << q.options[j] << endl;

            cout << "Enter your answer (A/B/C/D): ";
            cin >> ans;
            ans = toupper(ans);
            if (ans == q.correctOption)
                score++;
        }

        time_t now = time(0);
        tm* ltm = localtime(&now);
        ofstream result("results.txt", ios::app);
        result << left << setw(15) << username
               << " scored " << setw(5) << score << "/" << total
               << "  Date: " << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday
               << "  Time: " << setw(2) << setfill('0') << ltm->tm_hour << ":"
               << setw(2) << ltm->tm_min << ":" << setw(2) << ltm->tm_sec
               << setfill(' ') << endl;
        result.close();

        cout << "\nQuiz Completed! Your Score: " << score << "/" << total << endl;
    }

    void viewResults() {
        ifstream file("results.txt");
        if (!file) {
            cout << "\nNo results available.\n";
            return;
        }

        cout << "\n--- Student Quiz Results ---\n";
        cout << left << setw(15) << "Student" << setw(15) << "Score" << setw(15) << "Date" << setw(10) << "Time" << endl;
        cout << string(60, '-') << endl;

        string line;
        while (getline(file, line)) {
            if (line.find(username) != string::npos)
                cout << line << endl;
        }

        file.close();
    }
};

#endif
