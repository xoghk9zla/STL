//----------------------------------------------------------------------
// 2018. 1. STL �� 23, ȭ 56	5�� 28��	(12�� 1����)
// 
// 7��. �ݺ���
// �ݺ��� ������ ���� �ٸ���
// �ݺ��� ������ �Ǵ��ϰ� ȿ������ �˰����� �ۼ��ϴ� ��
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
	// �ݺ��ڰ� �ؾ� �� �⺻������ ���α׷� �ؾ� ��
	char operator*(){ return *p; }
	bool operator==(const myIter& rhs) const { return p == rhs.p; }
	bool operator!=(const myIter& rhs) const { return p != rhs.p; }
	myIter& operator=(const myIter&rhs) { p = rhs.p; return *this; }
	myIter& operator++() { ++p; return *this; }	// ��������
	myIter operator++(int) { myIter temp = *this; ++p; return temp; }	// ��������
};

class myString {
	int len{ 0 };
	char* p{ nullptr };
public:
	myString() {}	// �⺻ ������
	myString(const char* str) {	// ������
		len = strlen(str);
		p = new char[len + 1];
		strcpy(p, str);
	}
	myString(const myString& other) {	// ���� ������
		len = other.len;
		p = new char[len + 1];
		strcpy(p, other.p);
	}
	myString& operator=(const myString& other) {	// ���� �Ҵ���
		delete[] p;
		len = other.len;
		p = new char[len + 1];
		strcpy(p, other.p);
	}
	~myString(){	// �Ҹ���
		delete[] p;
	}
	friend ostream& operator<<(ostream& , const myString&);	// friend private�� �����ϱ� ���ؼ� ���
	void operator+=(const char* s) {
		int num = len + strlen(s);
		char* tp = new char[num + 1];
		strcpy(tp, p);
		strcat(tp, s);
		delete[] p;
		len = num;
		p = tp;
	}
	// �����̳ʰ� �����ϴ� �Լ�
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
	myString s{ "Hello, world!" };	// char*, char[]�� ��ġ�ϴ� class
	myString s1 = s;

	cout << s1 << endl;			

	s += " STL �� ����ִ�!";
	cout << s << endl;
	cout << s.length() << endl;
	cout << s.size() << endl;

	char str[40];
	strcpy(str, s.c_str());
	cout << str << endl;

	//for (char d : s) {	// ǥ�� �����̳ʶ�� �� �ڵ忡 ������ ����� ��
	//	cout << d << " ";
	//}
	//cout << endl;

	auto p = myFind(begin(s), end(s), 'w');
	cout << typeid(p).name() << endl;

	if (p != s.end())
		cout << "ã�ҽ��ϴ� - " << *p << "��" << endl;
	else
		cout << "�׷��� ����� �Ф�" << endl;

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