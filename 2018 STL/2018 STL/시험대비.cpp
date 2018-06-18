#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

int main() {
	ifstream in("이상한 나라의 앨리스.txt");
	int num{ 0 };

	char c;
		in >> c >> c >> c; // BOM무시

	set<string> sset;
	string s;

	while (in >> s)
	{
		sset.emplace(s);
		num++;
	}

	cout << "/이상한 나라의 앨리스.txt/에 사용된 단어의 갯수:" << num << endl;
}