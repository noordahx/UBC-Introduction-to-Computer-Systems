#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctype.h>

using namespace std;
int score = 0;
/*
void calculate(string a, string b) {
    int lenA = a.length();
    int lenB = b.length();
    vector<char> first(a.begin(), a.end());
    vector<char> second(b.begin(), b.end());
    vector<char> v((lenA+lenB));
    sort(first.begin(), first.begin() + lenA);
    sort(second.begin(), second.begin() + lenB);

    vector<char>::iterator it = set_intersection(first.begin(), first.begin() + lenA, second.begin(), second.begin() + lenB, v.begin());
    v.resize(it - v.begin());

    sort(v.begin(), v.end());
    
    v.erase(unique(v.begin(), v.end() ), v.end());


    for(char c : v) {
        if (isupper(c)) {
        //    cout << c << " " << c-'A'+27;
            score += c-'A'+27;
        } else {
      //      cout << c << " " << c-'a'+1;
            score += c-'a'+1;
        }
    }
    //cout << " " << score << endl;
}
*/

void calculate(string a, string b, string c) {
    int lenA = a.length();
    int lenB = b.length();
    int lenC = c.length();
    
    vector<char> first(a.begin(), a.end());
    vector<char> second(b.begin(), b.end());
    vector<char> third(c.begin(), c.end());

    sort(first.begin(), first.begin() + lenA);
    sort(second.begin(), second.begin() + lenB);
    sort(third.begin(), third.begin() + lenC);
    vector<char> v(max(max(lenA,lenB),lenC));

    vector<char>::iterator it = set_intersection(first.begin(), first.begin() + lenA, second.begin(), second.begin() + lenB, v.begin());
    int lenV = v.size();
    it = set_intersection(v.begin(), v.begin() + lenV, third.begin(), third.begin() + lenC, v.begin());
    v.resize(it - v.begin());
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    char d = v[0];
    if (isupper(d)) {
    //    cout << d << " " << d-'A'+27;
        score += d-'A'+27;
    } else {
        //  cout << d << " " << d-'a'+1;
        score += d-'a'+1;
    }

}




int main() {
	while (true) {
		string input, input2, input3;
		getline(cin, input);
		if (input == "q" || input == "") {
			cout << score;
            return 0;
		}
        getline(cin, input2);
        getline(cin, input3);
        calculate(input, input2, input3);
	}
	return 0;
}
