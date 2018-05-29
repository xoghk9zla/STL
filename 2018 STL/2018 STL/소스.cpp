//----------------------------------------------------------------------
// 2018. 1. STL 월 23, 화 56	5월 28일	(12주 1일차)
// 
// 7장. 반복자
// 반복자 종류에 따라 다른점
// 반복자 종류를 판단하고 효율적인 알고리즘을 작성하는 법
// 
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
//#include <string>
#include "save.h"

using namespace std;

class myIter {
	char* p{ nullptr };
public:
	myIter(char* p) : p(p){}
	// 반복자가 해야 할 기본동작을 프로그램 해야 함
	char operator*(){ return *p; }
	bool operator==(const myIter& rhs) const { return p == rhs.p; }
	bool operator!=(const myIter& rhs) const { return p != rhs.p; }
	myIter& operator=(const myIter&rhs) { p = rhs.p; return *this; }
	myIter& operator++() { ++p; return *this; }	// 전위증가
	myIter operator++(int) { myIter temp = *this; ++p; return temp; }	// 후위증가
};

class myString {
	int len{ 0 };
	char* p{ nullptr };
public:
	myString() {}	// 기본 생성자
	myString(const char* str) {	// 생성자
		len = strlen(str);
		p = new char[len + 1];
		strcpy(p, str);
	}
	myString(const myString& other) {	// 복사 생성자
		len = other.len;
		p = new char[len + 1];
		strcpy(p, other.p);
	}
	myString& operator=(const myString& other) {	// 복사 할당자
		delete[] p;
		len = other.len;
		p = new char[len + 1];
		strcpy(p, other.p);
	}
	~myString(){	// 소멸자
		delete[] p;
	}
	friend ostream& operator<<(ostream& , const myString&);	// friend private에 접근하기 위해서 사용
	void operator+=(const char* s) {
		int num = len + strlen(s);
		char* tp = new char[num + 1];
		strcpy(tp, p);
		strcat(tp, s);
		delete[] p;
		len = num;
		p = tp;
	}
	// 컨테이너가 제공하는 함수
	size_t size() const { return len; }
	size_t length() const { return len; }
	char* c_str() const { return p; }
	myIter begin() { return myIter(p); }
	myIter end() { return myIter(p + len); }
};
ostream& operator<<(ostream& os, const myString& s) {
	os << s.p;
	return os;
}
template <class Iter, class Value>
Iter myFind(Iter begin, Iter end, Value val);

void main() {
	myString s{ "Hello, world!" };	// char*, char[]를 대치하는 class
	myString s1 = s;

	cout << s1 << endl;			

	s += " STL 참 재미있다!";
	cout << s << endl;
	cout << s.length() << endl;
	cout << s.size() << endl;

	char str[40];
	strcpy(str, s.c_str());
	cout << str << endl;

	//for (char d : s) {	// 표준 컨테이너라면 이 코드에 문제가 없어야 함
	//	cout << d << " ";
	//}
	//cout << endl;

	auto p = myFind(begin(s), end(s), 'w');
	cout << typeid(p).name() << endl;

	if (p != s.end())
		cout << "찾았습니다 - " << *p << "를" << endl;
	else
		cout << "그런건 없어요 ㅠㅠ" << endl;

	iterator_traits<myIter>::iterator_category c;
	cout << typeid(c).name();

	save();
}
template <class Iter, class Value>
Iter myFind(Iter begin, Iter end, Value val) {
	while (begin != end)
	{
		if (*begin == val)
			return begin;
		++begin;
	}
	return end;
}