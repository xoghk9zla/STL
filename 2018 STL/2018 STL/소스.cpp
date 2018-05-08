//----------------------------------------------------------------------
// 2018. 1. STL �� 23, ȭ 56	5�� 8��	(10�� 2����)
// 
// 5�� - ���� �����̳�
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
		cout << id << " - ������ - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
	}
	Model(const Model& m) :id(++gid) {
		size = m.size;
		data = new char[size];  
		// ���� ����
		memcpy(data, m.data, size);

		cout << id << " - ���� ������ - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
	}
	~Model() {
		cout << id << " - �Ҹ��� - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
		if (data != nullptr)
			delete[] data;
	}
	Model& operator=(const Model& m) {	// �����Ҵ���
		if (this == &m)
			return *this;

		size = m.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = new char[size];
		memcpy(data, m.data, size);

		cout << id << " - �����Ҵ��� - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
		return *this;
	}
	// �̵� ������, �̵� �Ҵ� ������
	Model(Model&& other) :id(++gid) {
		size = other.size;
		data = other.data;
		// ������ well-known ���·� ���������(defaul��)
		other.size = 0;
		other.data = 0;

		cout << id << " - �̵������� - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
	}
	Model& operator=(Model&& other) {
		if (this == &other)
			return *this;

		size = other.size;
		if (data != nullptr) {
			delete[] data;
		}
		data = other.data;

		// ������ well-known ���·� ���������(defaul��)
		other.size = 0;
		other.data = 0;

		cout << id << " - �̵��Ҵ� ������ - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
		return *this;
	}
	void Show() const { cout << this->size << endl; };
	int getSize()const { return size; }

	// find �˰����� ���� == ������ ���α׷�
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
	vector<char> v(100000); // ���ĺ� 10����

	default_random_engine dre;
	uniform_int_distribution<> ui('a', 'z');

	for(char& d: v)
		d = ui(dre);
	// �� ���ĺ��� �� ���� �ִ��� ȭ�鿡 ����϶�
	map<char, int> m;

	for (char d : v)
		m[d] ++;

	for (auto& d : m)
		cout << "[" << d.first << "]: " << d.second << endl;
	save();
}
