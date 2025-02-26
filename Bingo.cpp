#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <vector>
#include <iomanip>
#include <algorithm> // Added for shuffle
#include <random> // Added for better randomness

using namespace std;

const int SIZE = 5;
const int BINGO_RANGES[SIZE][2] = { {1, 15}, {16, 30}, {31, 45}, {46, 60}, {61, 75} };

void generateCard(int card[SIZE][SIZE]) {
    set<int> usedNumbers;
    for (int col = 0; col < SIZE; col++) {
        vector<int> numbers;
        for (int i = BINGO_RANGES[col][0]; i <= BINGO_RANGES[col][1]; i++) {
            numbers.push_back(i);
        }
        random_device rd;
        mt19937 g(rd());
        shuffle(numbers.begin(), numbers.end(), g);

        for (int row = 0; row < SIZE; row++) {
            if (row == 2 && col == 2) {
                card[row][col] = 0; // الوسط فارغ
            }
            else {
                card[row][col] = numbers[row];
            }
        }
    }
}

void printCard(int card[SIZE][SIZE], const string& playerName) {
    cout << "Player: " << playerName << endl;
    cout << "_____________________" << endl;
    cout << "| B | I | N | G | O |" << endl;
    cout << "|___|___|___|___|___|" << endl;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (card[i][j] == 0)
                cout << "| * ";
            else
                cout << "|" << setw(2) << card[i][j] << " ";
        }
        cout << "|" << endl;
        cout << "|___|___|___|___|___|" << endl;
    }
    cout << endl;
}

void removeNumber(int num, int card[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (card[i][j] == num) {
                card[i][j] = 0;
            }
        }
    }
}

bool checkWin(int card[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (card[i][0] == 0 && card[i][1] == 0 && card[i][2] == 0 && card[i][3] == 0 && card[i][4] == 0)
            return true;
        if (card[0][i] == 0 && card[1][i] == 0 && card[2][i] == 0 && card[3][i] == 0 && card[4][i] == 0)
            return true;
    }
    if (card[0][0] == 0 && card[1][1] == 0 && card[2][2] == 0 && card[3][3] == 0 && card[4][4] == 0)
        return true;
    if (card[0][4] == 0 && card[1][3] == 0 && card[2][2] == 0 && card[3][1] == 0 && card[4][0] == 0)
        return true;
    return false;
}

int main() {
    srand(time(0));
    string player1, player2;
    cout << "Enter name for Player 1: ";
    cin >> player1;
    cout << "Enter name for Player 2: ";
    cin >> player2;

    int card1[SIZE][SIZE], card2[SIZE][SIZE];
    generateCard(card1);
    generateCard(card2);

    printCard(card1, player1);
    printCard(card2, player2);

    set<int> usedNumbers;
    while (true) {
        int num;
        cout << player1 << ", choose a number: ";
        cin >> num;
        while (num < 1 || num > 75 || usedNumbers.count(num)) {
            cout << "Invalid or used number. Choose again: ";
            cin >> num;
        }
        usedNumbers.insert(num);
        removeNumber(num, card1);
        removeNumber(num, card2);
        if (checkWin(card1)) { cout << player1 << " wins!\n"; break; }
        if (checkWin(card2)) { cout << player2 << " wins!\n"; break; }

        cout << player2 << ", choose a number: ";
        cin >> num;
        while (num < 1 || num > 75 || usedNumbers.count(num)) {
            cout << "Invalid or used number. Choose again: ";
            cin >> num;
        }
        usedNumbers.insert(num);
        removeNumber(num, card1);
        removeNumber(num, card2);
        if (checkWin(card1)) { cout << player1 << " wins!\n"; break; }
        if (checkWin(card2)) { cout << player2 << " wins!\n"; break; }
    }
    return 0;
}
