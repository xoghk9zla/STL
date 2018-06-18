//----------------------------------------------------------------------
// 2018. 1. STL 월 23, 화 56	6월 5일	(13주 2일차)
// 
// 9장 알고리즘
// 학과 자료실에서 "단어들.txt"를 받아 vector<string>에 읽어주세요.
// 
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <list>
#include "save.h"

using namespace std;

struct PS : pair<string, string> {
	PS(string s) : pair<string,string>(s, s) {
		sort(first.begin(), first.end());
	}

	operator string() const { return second; };
};

void main() {
	ifstream in("단어들.txt");
	vector<string> v{ istream_iterator<string>(in), istream_iterator<string>() };

	cout << v.size() << "개의 표제어를 읽었습니다." << endl;  

	// 1. game이라는 단어가 있나 찾아봐!
	// 2. 사용자가 찾는 단어가 있나?
	//   있다면 몇 번째 단어인지 출력해줘. - 영원히
	// 3. 이 사전에서 가장 길이가 긴 단어를 찾아 출력하라.
	// 4. 이 사전에서 길이가 긴 단어 20개만 골라 출력하라.
	// 5. 이 사전에서 s로 시작하는 단어의 갯수는?
	// 6. 사용자가 입력한 단어의 애너그램을 모두 출력하세요.
	
	// 애너그램 쌍을 찾아 "애너그램들.txt" 파일에 기록하라
	vector<PS> pv{ v.begin(), v.end() };
	sort(pv.begin(), pv.end(), [](const PS& a, const PS& b) {
		return a.first < b.first;
	});
	map<string, list<string>> m;
	vector<PS>::const_iterator j, k, e;
	j = pv.begin();
	e = pv.end();
	int i = 1;
	while (true) {
		j = adjacent_find(j, e, [](const PS& a, const PS& b) {
			return a.first == b.first;
		});
		if (j == e)
			break;
		k = find_if_not(j, e, [j](const PS& a) {
			return a.first == j->first;
		});
		m.insert(make_pair(j->first, list<string>{ j,k }));
		j = k;
	}
	// 가장 갯수가 많은 애너그램은?
	map<string, list<string>>::iterator saveMax;
	int num = 0;
	for (auto p = m.begin(); p != m.end(); ++p) {
		if (num < p->second.size()) {
			num = p->second.size();
			saveMax = p;
		}
	}
	cout << "최대 애ㅓㄴ그램의 갯수 - " << num << endl;
	for (auto i = saveMax->second.begin(); i != saveMax->second.end(); ++i)
		cout << *i << "  ";
	// 사용자가 입력한 단어의 anagram을 찾아줘
	while (true) {
		string s;
		cout << "단어 입력";
		cin >> s;
		string sort_s{ s };
		sort(sort_s.begin(), sort_s.end());
		auto p = m.find(sort_s);
		if (p != m.end()) {
			cout << s << "의 애너그램 입니다.";
			for (auto i = p->second.begin(); i != p->second.end(); ++i) {
				cout << *i << "\t";
			}
			cout << endl;
		}
		else {
			cout << "애너그램이 없는 단어 입니다." << endl;
		}
	}
	save();
}
