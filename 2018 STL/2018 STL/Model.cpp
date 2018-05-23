#include "Model.h"

#include <iostream>

using namespace std;

int gid = 0;

Model::Model() :id(++gid) {
	cout << id << " - default ctor" << endl;
}

Model::Model(size_t s) : size(s), id(++gid) {
	data = new char[size];
	cout << id << " - ������ - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
}

Model::Model(const Model & m) : id(++gid) {
	size = m.size;
	data = new char[size];
	// ���� ����
	memcpy(data, m.data, size);

	cout << id << " - ���� ������ - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
}

Model & Model::operator=(const Model & m) {	// �����Ҵ���
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

Model::Model(Model && other) :id(++gid) {
	size = other.size;
	data = other.data;
	// ������ well-known ���·� ���������(defaul��)
	other.size = 0;
	other.data = 0;

	cout << id << " - �̵������� - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
}

Model & Model::operator=(Model && other) {
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
	cout << id << " - �Ҹ��� - " << size << ", ����Ʈ: " << static_cast<void*>(data) << endl;
	if (data != nullptr)
		delete[] data;
}