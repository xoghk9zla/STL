//----------------------------------------------------------------------
// 2018. 1. STL �� 23, ȭ 56	6�� 4��	(13�� 1����)
// 
// 9�� �˰���
// 1. ���Ҹ� �������� �ʴ� �˰���()
// 2. ���Ҹ� �����ϴ� �˰���()
// 3. ���İ� ���õ� �˰���
// 
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "save.h"

using namespace std;

void main() {

	string s{ "abcdefghijklmnopqrstuvwxyz " };

	while (1)
	{
		system("cls");
		for (int i = 0; i < 10; ++i) {
			cout << endl;
		}

		cout << "\t\t";

		rotate(s.rbegin(), s.rbegin() + 1, s.rend());
		cout << s << endl;
		this_thread::sleep_for(30ms);
	}


	save();
}
