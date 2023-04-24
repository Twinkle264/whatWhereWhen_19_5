#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int NUM_SECTORS = 13;
const int POINTS_TO_WIN = 6;

bool isCorrect(int) {

    if (cin.fail()) {
        cerr << "Invalid input! Please enter an integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    } else {
        return true;
    }
}

int main() {
    bool sectorsPlayed[13] = {false};
    string questions[13];
    string answers[13];
    string fileName;

    for (int i = 0; i < NUM_SECTORS; ++i) {
        for (int j = 0; j < 2; ++j) {
            j == 0 ? fileName = "question" : fileName = "answer";

            string filePath = "./files/" + fileName + to_string(i + 1) + ".txt";
            ifstream fin(filePath);

            if (fin.is_open() && j == 0) {
                getline(fin, questions[i]);
                fin.close();
            } else if (fin.is_open() && j == 1) {
                getline(fin, answers[i]);
                fin.close();
            } else {
                cerr << "ERROR! The file with path \"" << filePath << "\" is not open!";
                return 1;
            }
        }
    }

    int currentSector = 0;
    int playerScore = 0;
    int viewerScore = 0;

    while (playerScore < POINTS_TO_WIN && viewerScore < POINTS_TO_WIN) {
        int offset;
        do {
            cout << "Enter offset: ";
            cin >> offset;
        } while (!isCorrect(offset));

        currentSector = (currentSector + offset) % NUM_SECTORS;
        if (sectorsPlayed[currentSector]) {
            currentSector = (currentSector + 1) % NUM_SECTORS;
        }
        sectorsPlayed[currentSector] = true;

        cout << questions[currentSector] << endl;

        string playerAnswer;

        cout << "Enter the answer: ";
        cin >> playerAnswer;

        if (playerAnswer == answers[currentSector]) {
            playerScore++;
            cout << "\tCorrect!" << endl;
        } else {
            viewerScore++;
            cout << "\tIncorrect!" << endl;
        }
        cout << "\tPlayer score: " << playerScore << endl;
        cout << "\tViewer score: " << viewerScore << endl;
    }

    if (playerScore >= POINTS_TO_WIN) {
        cout << "Congratulation! You won!" << endl;
    } else if (viewerScore >= POINTS_TO_WIN) {
        cout << "Sorry, you lost! Viewer wins!" << endl;
    }
    return 0;
}
