#include <bits/stdc++.h>
using namespace std;

void q1() {
    while (true) {
		vector<string> input(5);
		for (auto in : input) getline(cin, in);
		if (input[0] == "q" || input[0] == "") {
			return;
		}
        if (input[0] != "zero") cout << "wrong" << endl;        
        if (input[1] != "one") cout << "wrong" << endl;        
        if (input[2] != "two") cout << "wrong" << endl;        
        if (input[3] != "three") cout << "wrong" << endl;        
        if (input[4] != "-----") cout << "wrong" << endl;        
	}
}




int main() {
    q1();
    return 0;
}