#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

int main() {
	ifstream in("�̻��� ������ �ٸ���.txt");
	int num{ 0 };

	char c;
		in >> c >> c >> c; // BOM����

	set<string> sset;
	string s;

	while (in >> s)
	{
		sset.emplace(s);
		num++;
	}

	cout << "/�̻��� ������ �ٸ���.txt/�� ���� �ܾ��� ����:" << num << endl;
}