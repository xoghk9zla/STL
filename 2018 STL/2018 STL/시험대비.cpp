#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	ifstream in("시험대비.cpp", ios::binary);
	list<string> slist;
	int num{ 0 };
	string s;
	while (in >> s) {
		slist.emplace_back(s);
	}

	auto p = search(slist.begin(), slist.end(), string("inc"));
	//auto p = equal_range(slist.begin(), slist.end(), string("inc"));
	while (p != slist.end()) {
		num++;
		++p;
	}
	

	cout << "inc의 출현 횟수 - " << num << endl;
}	