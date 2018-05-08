//----------------------------------------------------------------------
// 2018. 1. STL 월 23, 화 56	5월 8일	(10주 2일차)
// 
// 5장 - 연관 컨테이너
// set
//
// map
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <algorithm>
#include "save.h"

using namespace std;

int gid = 0;

class Model {
private:
	int id;
	char* data = nullptr;
	size_t size = 0;
public:
	Model() :id(++gid) { cout << id << " - default ctor" << endl; }
	Model(size_t s) :size(s), id(++gid) {
		data = new char[size];
		cout << id << " - 생성자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
	}
	Model(const Model& m) :id(++gid) {
		size = m.size;
		data = new char[size];  
		// 깊은 복사
		memcpy(data, m.data, size);

		cout << id << " - 복사 생성자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
	}
	~Model() {
		cout << id << " - 소멸자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
		if (data != nullptr)
			delete[] data;
	}
	Model& operator=(const Model& m) {	// 복사할당자
		if (this == &m)
			return *this;

		size = m.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = new char[size];
		memcpy(data, m.data, size);

		cout << id << " - 복사할당자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
		return *this;
	}
	// 이동 생성자, 이동 할당 연산자
	Model(Model&& other) :id(++gid) {
		size = other.size;
		data = other.data;
		// 원본은 well-known 상태로 만들어주자(defaul값)
		other.size = 0;
		other.data = 0;

		cout << id << " - 이동생성자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
	}
	Model& operator=(Model&& other) {
		if (this == &other)
			return *this;

		size = other.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = other.data;

		// 원본은 well-known 상태로 만들어주자(defaul값)
		other.size = 0;
		other.data = 0;

		cout << id << " - 이동할당 연산자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
		return *this;
	}
	void Show() const { cout << this->size << endl; };
	int getSize()const { return size; }

	// find 알고리즘을 위한 == 연산자 프로그램
	bool operator==(const Model& other)const {
		if (size == other.size)
			return true;

		return false;
	}
	bool operator < (const Model& rhs)const {
		return size < rhs.getSize();
	}
};

// 

void main() {
	
	// 
	vector<char> v(100000); // 알파벳 10만개

	default_random_engine dre;
	uniform_int_distribution<> ui('a', 'z');

	for(char& d: v)
		d = ui(dre);
	// 각 알파벳이 몇 개씩 있는지 화면에 출력하라
	map<char, int> m;

	for (char d : v)
		m[d] ++;

	for (auto& d : m)
		cout << "[" << d.first << "]: " << d.second << endl;
	save();
}
