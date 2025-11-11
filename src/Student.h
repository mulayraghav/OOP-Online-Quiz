#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Quiz.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

class Student : public User
{
public:
    Student(string uname = "", string pass = "") : User(uname, pass) {}

    void registerStudent()
    {
        cout << "\n[Student Registration]\n";
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // ✅ Check if file is empty (write header only once)
        bool writeHeader = false;
        ifstream check("students.csv");
        if (!check.good() || check.peek() == ifstream::traits_type::eof())
            writeHeader = true;
        check.close();

        ofstream file("students.csv", ios::app);
        if (!file)
        {
            cout << "Error opening student file.\n";
            return;
        }

        if (writeHeader)
            file << "Username,Password\n";

        file << username << "," << password << "\n";
        file.close();

        cout << "\nRegistration successful! You can now log in.\n";
    }

    void login() override
    {
        cout << "\n[Student Login]\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream file("students.csv");
        if (!file)
        {
            cout << "No registered students found. Please register first.\n";
            return;
        }

        string line, u, p;
        bool found = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, u, ',');
            getline(ss, p, ',');
            if (u == username && p == password)
            {
                found = true;
                break;
            }
        }
        file.close();

        if (found)
        {
            cout << "\nLogin successful!\n";
            studentMenu();
        }
        else
        {
            cout << "\nInvalid credentials. Try again or register first.\n";
        }
    }

    void studentMenu()
    {
        int choice;
        Quiz quiz;
        quiz.loadQuestions();

        do
        {
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

    void attemptQuiz(Quiz &quiz)
    {
        int total = quiz.getQuestionCount();
        if (total == 0)
        {
            cout << "No questions available.\n";
            return;
        }

        cout << "\nStarting Quiz...\n";
        int score = 0;
        char ans;
        for (int i = 0; i < total; i++)
        {
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

        // Get current date and time
        time_t now = time(0);
        tm *ltm = localtime(&now);

        // Check if file is empty (write header only once)
        bool writeHeader = false;

        ifstream check("results.csv");

        if (!check.good() || check.peek() == ifstream::traits_type::eof())
            writeHeader = true;
        check.close();

        ofstream result("results.csv", ios::app);
        if (!result)
        {
            cout << "Error opening results file.\n";
            return;
        }

        if (writeHeader)
            result << "Username,Score,Total,Date,Time\n";

        result << username << ","
               << score << ","
               << total << ","
               << (1900 + ltm->tm_year) << "-"
               << setw(2) << setfill('0') << (1 + ltm->tm_mon) << "-"
               << setw(2) << ltm->tm_mday << ","
               << setw(2) << ltm->tm_hour << ":"
               << setw(2) << ltm->tm_min << ":"
               << setw(2) << ltm->tm_sec << "\n";
        result.close();

        cout << "\nQuiz Completed! Your Score: " << score << "/" << total << endl;
    }

    void viewResults()
    {
        ifstream file("results.csv");
        if (!file)
        {
            cout << "\nNo results available.\n";
            return;
        }

        cout << "\n--- Your Quiz Results ---\n";
        cout << left << setw(15) << "Student"
             << setw(10) << "Score"
             << setw(10) << "Total"
             << setw(15) << "Date"
             << setw(10) << "Time" << endl;
        cout << string(60, '-') << endl;

        string line, user, score, total, date, time;
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, user, ',');
            getline(ss, score, ',');
            getline(ss, total, ',');
            getline(ss, date, ',');
            getline(ss, time, ',');

            if (user == username)
            {
                cout << left << setw(15) << user
                     << setw(10) << score
                     << setw(10) << total
                     << setw(15) << date
                     << setw(10) << time << endl;
            }
        }

        file.close();
    }
};

#endif
