#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Quiz.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
                    addQuestionToCSV();
                    break;
                case 2:
                    viewQuestionsFromCSV();
                    break;
                case 3:
                    viewResultsFromCSV();
                    break;
                case 4:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice! Try again.\n";
            }

        } while (choice != 4);
    }
// -------------------------------
// Add Question in CSV format (Clean + Header + Quotes for Question only)
// -------------------------------
void addQuestionToCSV() {
    // ✅ Check if header is needed
    bool writeHeader = false;
    ifstream check("questions.csv");
    if (!check.good() || check.peek() == ifstream::traits_type::eof())
        writeHeader = true;
    check.close();

    ofstream file("questions.csv", ios::app);
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

    //  Write header if file was empty
    if (writeHeader)
        file << "Question,OptionA,OptionB,OptionC,OptionD,Answer\n";

    //  Write data: Only the question is quoted
    file << '"' << text << '"' << ","
         << options[0] << ","
         << options[1] << ","
         << options[2] << ","
         << options[3] << ","
         << correctOption << "\n";

    file.close();
    cout << "\nQuestion added successfully to questions.csv!\n";
}

    // -------------------------------
    // View Questions from CSV
    // -------------------------------
    void viewQuestionsFromCSV() {
        ifstream file("questions.csv");
        if (!file) {
            cout << "\nNo questions available.\n";
            return;
        }

        cout << "\n--- All Questions ---\n";
        string line;
        int qNo = 1;

        while (getline(file, line)) {
            stringstream ss(line);
            string text, optA, optB, optC, optD, correct;
            getline(ss, text, ',');
            getline(ss, optA, ',');
            getline(ss, optB, ',');
            getline(ss, optC, ',');
            getline(ss, optD, ',');
            getline(ss, correct, ',');

            cout << "\nQ" << qNo++ << ": " << text << "\n";
            cout << "  A) " << optA << "\n";
            cout << "  B) " << optB << "\n";
            cout << "  C) " << optC << "\n";
            cout << "  D) " << optD << "\n";
            cout << "  Correct Option: " << correct << "\n";
        }

        file.close();
    }

    // -------------------------------
    // View Student Results from CSV
    // -------------------------------
    void viewResultsFromCSV() {
        ifstream file("results.csv");
        if (!file) {
            cout << "\nNo results found.\n";
            return;
        }

        cout << "\n--- Student Quiz Results ---\n";
        cout << left << setw(15) << "Student"
             << setw(10) << "Score"
             << setw(10) << "Total"
             << setw(15) << "Date"
             << setw(10) << "Time" << endl;
        cout << string(60, '-') << endl;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string user, score, total, date, time;

            getline(ss, user, ',');
            getline(ss, score, ',');
            getline(ss, total, ',');
            getline(ss, date, ',');
            getline(ss, time, ',');

            cout << left << setw(15) << user
                 << setw(10) << score
                 << setw(10) << total
                 << setw(15) << date
                 << setw(10) << time << endl;
        }

        file.close();
    }
};

#endif
