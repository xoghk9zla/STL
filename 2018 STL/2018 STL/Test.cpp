#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <fstream>

using namespace std;

vector<string> temp;
map<char, int> spelling_frequency;
map<string, int> sort_by_word;
map<int, string> word_frequency;

void load();
void show();
void show_frequency();

void main(){
	// 1) ������ �о� �� ö���� �󵵼� ǥ��
	// 2) ���� ���� ������ �ܾ�� ���
	// 3) ���̰� ���� �� �ܾ� ���
	load();

	while (1){
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
	char inputString[1000];

	fstream in("�̻��� ������ �ٸ���.txt");
	while (!in.eof()) {
		in.getline(inputString, 128);
		temp.emplace_back(inputString);
	}
	for (string d : temp) {
		for (char c : d) {
			spelling_frequency[c] ++;
		}
	}
	in.close();

	in.open("�̻��� ������ �ٸ���.txt");
	while(in >> inputString) {
		sort_by_word[inputString] ++;
	}

	for (auto d : sort_by_word)
		word_frequency[d.second] = d.first;
}

void show() {
	for (auto v : temp)
		cout << v.c_str() << endl;
}

void show_frequency() {
	for (auto& s : spelling_frequency)
		cout << "[\t" << s.first << "\t]: " << s.second << endl;
}