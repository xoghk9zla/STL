#include <iostream>
#include <fstream>
#include <list>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;

int main() {
<<<<<<< HEAD
	ifstream in("�̻��� ������ �ٸ���.txt", ios::binary);
=======
	ifstream in("������.cpp", ios::binary);
	list<string> slist;
>>>>>>> a4128c55b8e037b241befc9d7c02aa0aa5fc3d59
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
	

	cout << "inc�� ���� Ƚ�� - " << num << endl;
}	