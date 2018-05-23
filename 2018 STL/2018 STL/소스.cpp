//----------------------------------------------------------------------
// 2018. 1. STL 월 23, 화 56	5월 21일	(12주 1일차)
// 
// 7장. 반복자
// 반복자 종류에 따라 다른점
// 반복자 종류를 판단하고 효율적인 알고리즘을 작성하는 법
// 
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <vector>
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
	
	save();
}

//template<class Iter>
//iterator_traits<Iter>::differnce_type my_distance(Iter begin, Iter end) {
//	if(typeid(begin).name())
//	// if(Iter의 종류가 랜덤이라면)
//	// return end - begin;
//	// else
//	// while(begin != end){
//	// cnt++;
//	// ++begin;
//	// }
//	// return cnt;
//}