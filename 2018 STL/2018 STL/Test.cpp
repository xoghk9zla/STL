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

	// 1) ������ �о� �� ö���� �󵵼� ǥ��

	// 2) ���� ���� ������ �ܾ�� ���

	// 3) ���̰� ���� �� �ܾ� ���

	load();



	while (1) {

		system("cls");

		cout << "1. �� ö���� �󵵼� ��� 2. ���� ���� ������ �ܾ�� ���" << endl;

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



	fstream in("�̻��� ������ �ٸ���.txt");

	// �� ������ UTF-8 ������ ���Ϸ� BOM(Byte order mark)�� ��ϵǾ� �ִ�.



	char c;

	in >> c >> c >> c; // BOM����



	map<string, int> simap;



	string s;

	while (in >> s) {

		simap[s]++;	// cimap.operator[](c)

	}



	// ���� ���̰� �� �ܾ��? (�ܾ�� �������� �и���)

	// STL���� �����ϸ� for loop�� ������� �ʴ´�.( ����� �˰����� �ִ� ���)

	auto p = max_element(simap.begin(), simap.end(), [](const auto& a, const auto& b) {

		return a.first < b.first;

	});

	if (p != simap.end())

		cout << p->first << endl;



	system("pause");

}