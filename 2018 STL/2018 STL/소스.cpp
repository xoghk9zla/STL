//----------------------------------------------------------------------
// 2018. 1. STL �� 23, ȭ 56	5�� 21��	(12�� 1����)
// 
// 7��. �ݺ���
// �ݺ��� ������ ���� �ٸ���
// �ݺ��� ������ �Ǵ��ϰ� ȿ������ �˰����� �ۼ��ϴ� ��
// 
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <list>
#include <iterator>

#include "Model.h"
#include "save.h"

using namespace std;
//
//template<class Iter>
//iterator_traits<Iter>::differnce_type my_distance(Iter begin, Iter end);

void main() {
	int* p = reinterpret_cast<int*>(1000);
	int* q = reinterpret_cast<int*>(2000);
	cout << typeid(cin).name() << endl;
	//cout << my_distance(p, q) << endl;
	
	list<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	list<int>::iterator iter = v.begin();
	cout << *iter++;
	cout << *iter--;
	cout << *iter;


	
	
	//save();
}

//template<class Iter>
//iterator_traits<Iter>::differnce_type my_distance(Iter begin, Iter end) {
//	if(typeid(begin).name())
//	// if(Iter�� ������ �����̶��)
//	// return end - begin;
//	// else
//	// while(begin != end){
//	// cnt++;
//	// ++begin;
//	// }
//	// return cnt;
//}