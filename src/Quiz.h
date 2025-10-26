#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <random>
using namespace std;

struct Question {
    string text;
    string options[4];
    char correctOption;
};

class Quiz {
private:
    vector<Question> questions;

public:
    void loadQuestions() {
        ifstream file("questions.txt");
        if (!file) {
            cout << "No questions file found!\n";
            return;
        }
        questions.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            Question q;
            q.text = line;
            for (int i = 0; i < 4; i++)
                getline(file, q.options[i]);
            file >> q.correctOption;
            q.correctOption = toupper(q.correctOption);
            file.ignore();
            getline(file, line); // read separator ---
            questions.push_back(q);
        }
        file.close();
    }

    void saveQuestions() {
        ofstream file("questions.txt");
        if (!file) {
            cout << "Error saving questions!\n";
            return;
        }
        for (auto &q : questions) {
            file << q.text << endl;
            for (int i = 0; i < 4; i++)
                file << q.options[i] << endl;
            file << q.correctOption << endl;
            file << "---" << endl;
        }
        file.close();
    }

    void displayAll() const {
        if (questions.empty()) {
            cout << "\nNo questions available.\n";
            return;
        }
        for (size_t i = 0; i < questions.size(); i++) {
            cout << "\nQ" << i + 1 << ": " << questions[i].text << endl;
            for (int j = 0; j < 4; j++)
                cout << char('A' + j) << ". " << questions[i].options[j] << endl;
            cout << "Correct Answer: " << questions[i].correctOption << endl;
        }
    }

    void addQuestion() {
        Question q;
        cin.ignore();
        cout << "\nEnter Question: ";
        getline(cin, q.text);
        for (int i = 0; i < 4; i++) {
            cout << "Enter Option " << char('A' + i) << ": ";
            getline(cin, q.options[i]);
        }
        cout << "Enter Correct Option (A-D): ";
        cin >> q.correctOption;
        q.correctOption = toupper(q.correctOption);
        questions.push_back(q);
        saveQuestions();
        cout << "\nQuestion added successfully!\n";
    }

    void editQuestion() {
        if (questions.empty()) {
            cout << "No questions to edit.\n";
            return;
        }
        displayAll();
        cout << "\nEnter question number to edit: ";
        int qno;
        cin >> qno;
        if (qno < 1 || qno > (int)questions.size()) {
            cout << "Invalid question number!\n";
            return;
        }
        Question &q = questions[qno - 1];
        cin.ignore();
        cout << "Editing Question " << qno << ":\n";
        cout << "Current: " << q.text << "\nEnter new (or press Enter to keep same): ";
        string newText;
        getline(cin, newText);
        if (!newText.empty()) q.text = newText;
        for (int i = 0; i < 4; i++) {
            cout << "Option " << char('A' + i) << " [" << q.options[i] << "]: ";
            string newOpt;
            getline(cin, newOpt);
            if (!newOpt.empty()) q.options[i] = newOpt;
        }
        cout << "Correct Option [" << q.correctOption << "]: ";
        string temp;
        getline(cin, temp);
        if (!temp.empty()) {
            char newCorrect = toupper(temp[0]);
            if (newCorrect >= 'A' && newCorrect <= 'D')
                q.correctOption = newCorrect;
        }
        saveQuestions();
        cout << "Question updated successfully!\n";
    }

    void deleteQuestion() {
        if (questions.empty()) {
            cout << "No questions to delete.\n";
            return;
        }
        displayAll();
        cout << "\nEnter question number to delete: ";
        int qno;
        cin >> qno;
        if (qno < 1 || qno > (int)questions.size()) {
            cout << "Invalid question number!\n";
            return;
        }
        questions.erase(questions.begin() + (qno - 1));
        saveQuestions();
        cout << "Question deleted successfully!\n";
    }

    void shuffleQuestions() {
        random_device rd;
        mt19937 g(rd());
        shuffle(questions.begin(), questions.end(), g);
    }

    void takeQuiz() {
        if (questions.empty()) {
            cout << "No questions available!\n";
            return;
        }
        shuffleQuestions();
        int score = 0;
        char ans;
        for (size_t i = 0; i < questions.size(); i++) {
            cout << "\nQ" << i + 1 << ": " << questions[i].text << endl;
            for (int j = 0; j < 4; j++)
                cout << char('A' + j) << ". " << questions[i].options[j] << endl;
            cout << "Enter your answer (A-D): ";
            cin >> ans;
            ans = toupper(ans);
            if (ans == questions[i].correctOption)
                score++;
        }
        cout << "\nFinal Score: " << score << "/" << questions.size() << "\n";
    }

    int getQuestionCount() const { return questions.size(); }
    Question getQuestion(int index) const {
        if (index >= 0 && index < (int)questions.size())
            return questions[index];
        return Question();
    }
};

#endif
