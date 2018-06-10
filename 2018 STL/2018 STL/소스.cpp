//----------------------------------------------------------------------
// 2018. 1. STL �� 23, ȭ 56	6�� 5��	(13�� 2����)
// 
// 9�� �˰���
// 1. ���Ҹ� �������� �ʴ� �˰���()
// 2. ���Ҹ� �����ϴ� �˰���()
// 3. ���İ� ���õ� �˰���
//		partition - ���ǿ� �´� �Ͱ� �ƴѰ��� �и��Ѵ�.
//		sort - ��ü�� ����(�⺻ < )�� ���� ���� �Ѵ�.
//		partial_sort - Ư�� ��ġ������ �����Ѵ�.
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

	// v�� ������������ �����϶�.
	sort(v.begin(), v.end());

	// v���� 7777�̶�� ���� �ִ��� ã�ƺ��� ��� �ִ���(�� ������) ����غ���.
	cout << boolalpha << binary_search(v.begin(), v.end(), 7777) << endl;
	equal_range(v.begin(), v.end(), 9777);

	save();
}
