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

// ǥ�� �ݺ��ڶ�� �ټ����� Ÿ���� �����ؾ� �Ѵ�.
// ����ڰ� iterator_traits<�� �ݺ���>::�ټ����� Ÿ���� �̿��Ͽ� ������ ������ �� �ִ�.
class myIter:public iterator<random_access_iterator_tag, char>{
	char* p{ nullptr };
public:
	myIter(char* p) : p(p){}
	// �ݺ��ڰ� �ؾ� �� �⺻������ ���α׷� �ؾ� ��
	char& operator*(){ return *p; }
	bool operator==(const myIter& rhs) const { return p == rhs.p; }
	bool operator!=(const myIter& rhs) const { return p != rhs.p; }
	myIter& operator=(const myIter&rhs) { p = rhs.p; return *this; }
	myIter& operator++() { ++p; return *this; }	// ��������
	myIter operator++(int) { myIter temp = *this; ++p; return temp; }	// ��������

	// ���� �ݺ��ڰ� �����ϴ� �����
	int operator-(const myIter&rhs) const { return p - rhs.p; }
	bool operator<(const myIter&rhs) const { return p < rhs.p; }
	myIter operator-(int n) const { myIter t(p); t.p -= n; return t; }
	myIter operator+(int n) const { myIter t(p); t.p += n; return t; }
	myIter& operator--() { --p; return *this; }	// ��������
	myIter operator--(int) { myIter temp = *this; --p; return temp; }	// ��������
};

class myRevIter :public iterator<random_access_iterator_tag, char> {
	char* p{ nullptr };
public:
	myRevIter(char* p) : p(p) {}
	char& operator*() { return *(p - 1); }
	bool operator!=(const myRevIter& rhs) { return p != rhs.p; }
	myRevIter& operator++() { --p; return *this; }	// ��������
	myRevIter operator++(int) { myRevIter temp = *this; --p; return temp; }	// ��������
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

	//��� ¦������ �˻��Ͻÿ�
	bool result = my_all_of(begin(a), end(a), [](int n) {
		return !(n & 1);
	});

	if (result)
		cout << "��� ¦�� �Դϴ�." << endl;
	else
		cout << "Ȧ���� ���� �ֽ��ϴ�." << endl;

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