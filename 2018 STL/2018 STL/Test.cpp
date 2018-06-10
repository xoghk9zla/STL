#include <iostream>

#include <functional>

#include <vector>

#include <map>

#include <string>

#include <fstream>

#include <algorithm>



using namespace std;



vector<string> temp;

map<char, int> spelling_frequency;

map<string, int> sort_by_word;

map<int, string> word_frequency;



void load();



void main() {

	// 1) 파일을 읽어 각 철자의 빈도수 표시

	// 2) 가장 많이 출현한 단어순 출력

	// 3) 길이가 가장 긴 단어 출력

	load();



	while (1) {

		system("cls");

		cout << "1. 각 철자의 빈도수 출력 2. 가장 많이 출현한 단어순 출력" << endl;

		int option;

		cin >> option;



		switch (option)

		{

		case 1:

			show_frequency();

			break;

		case 2:

			cout << word_frequency[word_frequency.size() - 1].c_str() << endl;

			for (auto& s : word_frequency)

				cout << "[\t" << s.first << "\t]: " << s.second.c_str() << endl;

			break;

		default:

			break;

		}

		system("pause");

	}

}



void load() {



	fstream in("이상한 나라의 앨리스.txt");

	// 이 파일은 UTF-8 형식의 파일로 BOM(Byte order mark)이 기록되어 있다.



	char c;

	in >> c >> c >> c; // BOM무시



	map<string, int> simap;



	string s;

	while (in >> s) {

		simap[s]++;	// cimap.operator[](c)

	}



	// 가장 길이가 긴 단어는? (단어는 공백으로 분리됨)

	// STL에서 가능하면 for loop를 사용하지 않는다.( 대신할 알고리즘이 있는 경우)

	auto p = max_element(simap.begin(), simap.end(), [](const auto& a, const auto& b) {

		return a.first < b.first;

	});

	if (p != simap.end())

		cout << p->first << endl;



	system("pause");

}