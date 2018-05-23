#include "Model.h"

#include <iostream>

using namespace std;

int gid = 0;

Model::Model() :id(++gid) {
	cout << id << " - default ctor" << endl;
}

Model::Model(size_t s) : size(s), id(++gid) {
	data = new char[size];
	cout << id << " - 생성자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
}

Model::Model(const Model & m) : id(++gid) {
	size = m.size;
	data = new char[size];
	// 깊은 복사
	memcpy(data, m.data, size);

	cout << id << " - 복사 생성자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
}

Model & Model::operator=(const Model & m) {	// 복사할당자
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

Model::Model(Model && other) :id(++gid) {
	size = other.size;
	data = other.data;
	// 원본은 well-known 상태로 만들어주자(defaul값)
	other.size = 0;
	other.data = 0;

	cout << id << " - 이동생성자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
}

Model & Model::operator=(Model && other) {
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

void Model::Show() const { 
	cout << this->size << endl; 
}
int Model::getSize() const { 
	return size; 
}

bool Model::operator==(const Model& other)const {
	if (size == other.size)
		return true;

	return false;
}

bool Model::operator < (const Model& rhs)const {
	return size < rhs.getSize();
}

Model::~Model() {
	cout << id << " - 소멸자 - " << size << ", 바이트: " << static_cast<void*>(data) << endl;
	if (data != nullptr)
		delete[] data;
}