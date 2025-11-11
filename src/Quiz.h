#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <limits>
using namespace std;

struct Question
{
    string text;
    string options[4];
    char correctOption;
};

class Quiz
{
private:
    vector<Question> questions;

public:
    void loadQuestions()
    {
        ifstream file("questions.csv");

        if (!file)
        {
            cout << "No questions file found (questions.csv)! \n";
            return;
        }

        questions.clear();
        string line;

        // Skip header line if it exists
        if (file.peek() != EOF)
            getline(file, line);

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            Question q;
            string correct;

            getline(ss, q.text, ',');
            getline(ss, q.options[0], ',');
            getline(ss, q.options[1], ',');
            getline(ss, q.options[2], ',');
            getline(ss, q.options[3], ',');
            getline(ss, correct, ',');

            q.text = trimQuotes(q.text);
            for (int i = 0; i < 4; i++)
                q.options[i] = trimQuotes(q.options[i]);

            q.correctOption = toupper(correct.empty() ? 'A' : correct[0]);
            questions.push_back(q);
        }

        file.close();
    }

    void saveQuestions()
    {
        const string filename = "questions.csv";

        ofstream file(filename, ios::out);
        if (!file)
        {
            cout << "Error saving questions!\n";
            return;
        }

        // Write header
        file << "Question,OptionA,OptionB,OptionC,OptionD,CorrectOption\n";

        // Write each question
        for (auto &q : questions)
        {
            file << '"' << q.text << '"' << ","
                 << '"' << q.options[0] << '"' << ","
                 << '"' << q.options[1] << '"' << ","
                 << '"' << q.options[2] << '"' << ","
                 << '"' << q.options[3] << '"' << ","
                 << q.correctOption << "\n";
        }

        file.close();

        cout << "\n✅ Questions saved successfully to " << filename << " with header.\n";
    }

    void displayAll() const
    {
        if (questions.empty())
        {
            cout << "\nNo questions available.\n";
            return;
        }

        for (size_t i = 0; i < questions.size(); i++)
        {
            cout << "\nQ" << i + 1 << ": " << questions[i].text << endl;
            for (int j = 0; j < 4; j++)
                cout << "  " << char('A' + j) << ") " << questions[i].options[j] << endl;
            cout << "  Correct Answer: " << questions[i].correctOption << endl;
        }
    }

    void takeQuiz()
    {
        if (questions.empty())
        {
            cout << "No questions available!\n";
            return;
        }

        int score = 0;
        char ans;

        for (size_t i = 0; i < questions.size(); i++)
        {
            cout << "\nQ" << i + 1 << ": " << questions[i].text << endl;
            for (int j = 0; j < 4; j++)
                cout << "  " << char('A' + j) << ") " << questions[i].options[j] << endl;

            cout << "Enter your answer (A-D): ";
            cin >> ans;
            ans = toupper(ans);

            if (ans == questions[i].correctOption)
                score++;
        }

        cout << "\nFinal Score: " << score << "/" << questions.size() << "\n";
    }

    static string trimQuotes(const string &str)
    {
        if (str.size() >= 2 && str.front() == '"' && str.back() == '"')
            return str.substr(1, str.size() - 2);
        return str;
    }

    int getQuestionCount() const { return questions.size(); }

    Question getQuestion(int index) const
    {
        if (index >= 0 && index < (int)questions.size())
            return questions[index];
        return Question();
    }
};

#endif
