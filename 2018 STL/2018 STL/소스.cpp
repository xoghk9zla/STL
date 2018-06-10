//----------------------------------------------------------------------
// 2018. 1. STL 월 23, 화 56	6월 5일	(13주 2일차)
// 
// 9장 알고리즘
// 1. 원소를 수정하지 않는 알고리즘()
// 2. 원소를 수정하는 알고리즘()
// 3. 정렬과 관련된 알고리즘
//		partition - 조건에 맞는 것과 아닌것을 분리한다.
//		sort - 전체를 기준(기본 < )에 따라 정렬 한다.
//		partial_sort - 특정 위치까지만 정렬한다.
//		nth_
// 
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>
#include "save.h"

using namespace std;

void main() {
	vector<int> v(10000);
	iota(v.begin(), v.end(), 1);
	random_shuffle(v.begin(), v.end());

	// v를 오름차순으로 정렬하라.
	sort(v.begin(), v.end());

	// v에서 7777이라는 값이 있는지 찾아보고 어디에 있는지(몇 등인지) 출력해보라.
	cout << boolalpha << binary_search(v.begin(), v.end(), 7777) << endl;
	equal_range(v.begin(), v.end(), 9777);

	save();
}
