#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
	vector<int> cals(1);
	int count = 0;
	while (true) {
		string input;
		getline(cin, input);
		if (input == "q") {
			sort(cals.begin(), cals.begin() + cals.size());
			cout << cals[cals.size()-1] + cals[cals.size()-2] + cals[cals.size()-3];
			return 0;
		}
		if (input == "") {
			cals.push_back(0);
			count++;
			continue;
		}
		cals[count] += stoi(input);
	}
	return 0;
}
