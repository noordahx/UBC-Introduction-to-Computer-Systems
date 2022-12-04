#include <bits/stdc++.h>

/*
2-4,6-8
2-3,4-5
5-7,7-9
2-8,3-7
6-6,4-6
2-6,4-8
*/

using namespace std;
int score = 0;

void calculate(string a) {
    string first = a.substr(0, a.find(","));
    a.erase(0, a.find(",") + 1);
    string second = a;

    int first_start = stoi(first.substr(0, first.find("-")));
    first.erase(0, first.find("-") + 1);
    int first_end = stoi(first);

    int second_start = stoi(second.substr(0, second.find("-")));
    second.erase(0, second.find("-") + 1);
    int second_end = stoi(second);

    vector<char> f;
    vector<char> s;
    for (int i = first_start; i <= first_end; i++) f.push_back(i);
    for (int i = second_start; i <= second_end; i++) s.push_back(i);

    vector<char> v(max(f.size(), s.size()));
    vector<char>::iterator it = set_intersection(f.begin(), f.begin() + (f.size()), s.begin(), s.begin() + (s.size()), v.begin());
    
    v.resize(it - v.begin());
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());


    if (v.size() > 0) score++;
}




int main() {
	while (true) {
		string input;
		getline(cin, input);
		if (input == "q" || input == "") {
			cout << score;
            return 0;
		}
        calculate(input);
	}
	return 0;
}
