#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Rules:     Rock > Scissors , Scissor > Paper, Paper > Rock
// Opponent : A - Rock , B - Paper , C - Scissors
// You :      X - Lose , Y - Draw,   Z - Win
// Scores :   1 ,        2 ,         3
// Outcome :  0 - Lost , 3 - Draw,   6 - Won 
int score = 0;
vector<char> op = {'A', 'B', 'C'};
vector<char> u = {'X', 'Y', 'Z'};
int find_pos(int mode, char input) {
    if (!mode) {
        for (int i = 0; i < op.size(); i++) {
            if (input == op[i]) {
                return i+1;
            }
        }
    }
    for (int i = 0; i < u.size(); i++) {
        if (input == u[i]) {
            return i+1;
        }
    }
    return -1;
}

void lose(int a) {
    if (a == 1) score += 3;
    if (a == 3) score += 2;
    if (a == 2) score += 1;
}
void win (int a) {
    score += 6;
    if (a == 1) score += 2;
    if (a == 3) score += 1;
    if (a == 2) score += 3;
}

void calculate(char a, char b) {
    int opponent = find_pos(0, a);
    int you = find_pos(1, b);
    if (you == 2) {score += opponent + 3; return;}
    if (you == 1) {lose(opponent); return;}
    win(opponent); return;
}


int main() {
	while (true) {
		string input;
		getline(cin, input);
		if (input == "q" || input == "") {
			cout << score;
            return 0;
		}
        calculate(input[0], input[2]);
	}
	return 0;
}
