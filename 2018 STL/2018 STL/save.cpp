#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

void save(void){
	// ���ǰ� ����� �ð��� �������
	// main()�� �ִ� �ҽ������� ������ �����̱�� �������

	ifstream in("�ҽ�.cpp");
	ofstream out("2018 STL.txt", ios::app);

	auto tp = chrono::system_clock::now();
	auto t = chrono::system_clock::to_time_t(tp);

	out << "-------------------------------------------------" << endl;
	out << "���ǽð�: " << ctime(&t);
	out << "-------------------------------------------------" << endl;

	char c;

	while (in.get(c)){
		out.put(c);
	}
	out << endl;
}

/*
// ���� ����
auto begin = chrono::high_resolution_clock::now();

this_thread::sleep_for(1s);

// ���� ��
auto elapsedTime = chrono::high_resolution_clock::now() - begin;
cout << chrono::duration<double>(elapsedTime).count() << "��";
*/