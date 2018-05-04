#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid;

class CDog{
private:
	int m_age;
	const char* m_name = "Unknown";
public:
	CDog(){ m_age = uid(dre); }
	friend ostream& operator<<(ostream&, const CDog&);
};
ostream& operator<<(ostream& os, const CDog& d){
	os << "나이: " << d.m_age << ", 이름: " << d.m_name << endl;
	return os;
}
void main(){
	CDog dogs[1000];
	
	sort(begin(dogs), end(dogs), [](const CDog& a, const CDog& b){
	
	});

	for (int i = 0; i < 10; ++i)
		cout << dogs[i] << endl;
	delete[] dogs;
}