//----------------------------------------------------------------------
// 2018. 1. STL 월 23, 화 56	6월 4일	(13주 1일차)
// 
// 9장 알고리즘
// 1. 원소를 수정하지 않는 알고리즘()
// 2. 원소를 수정하는 알고리즘()
// 3. 정렬과 관련된 알고리즘
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
