//----------------------------------------------------------------------
// 2018. 1. STL �� 23, ȭ 56	6�� 5��	(13�� 2����)
// 
// 9�� �˰���
// �а� �ڷ�ǿ��� "�ܾ��.txt"�� �޾� vector<string>�� �о��ּ���.
// 
//----------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <list>
#include "save.h"

using namespace std;

struct PS : pair<string, string> {
	PS(string s) : pair<string,string>(s, s) {
		sort(first.begin(), first.end());
	}

	operator string() const { return second; };
};

void main() {
	ifstream in("�ܾ��.txt");
	vector<string> v{ istream_iterator<string>(in), istream_iterator<string>() };

	cout << v.size() << "���� ǥ��� �о����ϴ�." << endl;  

	// 1. game�̶�� �ܾ �ֳ� ã�ƺ�!
	// 2. ����ڰ� ã�� �ܾ �ֳ�?
	//   �ִٸ� �� ��° �ܾ����� �������. - ������
	// 3. �� �������� ���� ���̰� �� �ܾ ã�� ����϶�.
	// 4. �� �������� ���̰� �� �ܾ� 20���� ��� ����϶�.
	// 5. �� �������� s�� �����ϴ� �ܾ��� ������?
	// 6. ����ڰ� �Է��� �ܾ��� �ֳʱ׷��� ��� ����ϼ���.
	
	// �ֳʱ׷� ���� ã�� "�ֳʱ׷���.txt" ���Ͽ� ����϶�
	vector<PS> pv{ v.begin(), v.end() };
	sort(pv.begin(), pv.end(), [](const PS& a, const PS& b) {
		return a.first < b.first;
	});
	map<string, list<string>> m;
	vector<PS>::const_iterator j, k, e;
	j = pv.begin();
	e = pv.end();
	int i = 1;
	while (true) {
		j = adjacent_find(j, e, [](const PS& a, const PS& b) {
			return a.first == b.first;
		});
		if (j == e)
			break;
		k = find_if_not(j, e, [j](const PS& a) {
			return a.first == j->first;
		});
		m.insert(make_pair(j->first, list<string>{ j,k }));
		j = k;
	}
	// ���� ������ ���� �ֳʱ׷���?
	map<string, list<string>>::iterator saveMax;
	int num = 0;
	for (auto p = m.begin(); p != m.end(); ++p) {
		if (num < p->second.size()) {
			num = p->second.size();
			saveMax = p;
		}
	}
	cout << "�ִ� �֤ä��׷��� ���� - " << num << endl;
	for (auto i = saveMax->second.begin(); i != saveMax->second.end(); ++i)
		cout << *i << "  ";
	// ����ڰ� �Է��� �ܾ��� anagram�� ã����
	while (true) {
		string s;
		cout << "�ܾ� �Է�";
		cin >> s;
		string sort_s{ s };
		sort(sort_s.begin(), sort_s.end());
		auto p = m.find(sort_s);
		if (p != m.end()) {
			cout << s << "�� �ֳʱ׷� �Դϴ�.";
			for (auto i = p->second.begin(); i != p->second.end(); ++i) {
				cout << *i << "\t";
			}
			cout << endl;
		}
		else {
			cout << "�ֳʱ׷��� ���� �ܾ� �Դϴ�." << endl;
		}
	}
	save();
}
