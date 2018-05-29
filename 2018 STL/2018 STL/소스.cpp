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

// 표준 반복자라면 다섯가지 타입을 정의해야 한다.
// 사용자가 iterator_traits<내 반복자>::다섯가지 타입을 이용하여 변수를 선언할 수 있다.
class myIter:public iterator<random_access_iterator_tag, char>{
	char* p{ nullptr };
public:
	myIter(char* p) : p(p){}
	// 반복자가 해야 할 기본동작을 프로그램 해야 함
	char& operator*(){ return *p; }
	bool operator==(const myIter& rhs) const { return p == rhs.p; }
	bool operator!=(const myIter& rhs) const { return p != rhs.p; }
	myIter& operator=(const myIter&rhs) { p = rhs.p; return *this; }
	myIter& operator++() { ++p; return *this; }	// 전위증가
	myIter operator++(int) { myIter temp = *this; ++p; return temp; }	// 후위증가

	// 랜덤 반복자가 제공하는 연산들
	int operator-(const myIter&rhs) const { return p - rhs.p; }
	bool operator<(const myIter&rhs) const { return p < rhs.p; }
	myIter operator-(int n) const { myIter t(p); t.p -= n; return t; }
	myIter operator+(int n) const { myIter t(p); t.p += n; return t; }
	myIter& operator--() { --p; return *this; }	// 전위감소
	myIter operator--(int) { myIter temp = *this; --p; return temp; }	// 후위감소
};

class myRevIter :public iterator<random_access_iterator_tag, char> {
	char* p{ nullptr };
public:
	myRevIter(char* p) : p(p) {}
	char& operator*() { return *(p - 1); }
	bool operator!=(const myRevIter& rhs) { return p != rhs.p; }
	myRevIter& operator++() { --p; return *this; }	// 전위증가
	myRevIter operator++(int) { myRevIter temp = *this; --p; return temp; }	// 후위증가
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
	myRevIter rbegin() { return myRevIter(p + len); }
	myRevIter rend() { return myRevIter(p); }
};
ostream& operator<<(ostream& os, const myString& s) {
	os << s.p;
	return os;
}

template<class Iter, class Call >
bool my_all_of(Iter, Iter, Call);

void main() {
	int a[]{ 2,4,6,8,10 };

	//모두 짝수인지 검사하시오
	bool result = my_all_of(begin(a), end(a), [](int n) {
		return !(n & 1);
	});

	if (result)
		cout << "모두 짝수 입니다." << endl;
	else
		cout << "홀수가 섞여 있습니다." << endl;

	save();
}
template<class Iter, class Call>
bool my_all_of(Iter begin, Iter end, Call func) {

	if (begin == end)
		return true;
	while (begin != end) {
		if (!func(*begin))
			return false;
		++begin;
	}
	return true;
}