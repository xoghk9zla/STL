#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main() {
	ifstream in("�ܾ��.txt");
	ofstream out1("E ���� �ܾ��.txt", ios::binary);
	ofstream out2("E �ִ� �ܾ��.txt", ios::binary);

	partition_copy(istream_iterator<string>(in), istream_iterator<string>(), ostream_iterator<string>(out1), ostream_iterator<string>(out2), find(istream_iterator<string>(in), istream_iterator<string>(), "e"));
}	