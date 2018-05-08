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
	// 1) 파일을 읽어 각 철자의 빈도수 표시
	// 2) 가장 많이 출현한 단어순 출력
	// 3) 길이가 가장 긴 단어 출력
	load();

	while (1){
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
	char inputString[1000];

	fstream in("이상한 나라의 앨리스.txt");
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

	in.open("이상한 나라의 앨리스.txt");
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