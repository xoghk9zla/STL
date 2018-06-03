#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

#include "CMainGame.h"

CMainGame::CMainGame(void) {}
CMainGame::~CMainGame(void) { 
	system("cls");
	cout << "================���Ͽ� �÷��̾��� �����͸� �����ϴ� ���Դϴ�.=================" << endl; 
	Save(); 
	cout << "=================================���� ����!===================================" << endl;
	system("pause");
}

// �ʱ�ȭ(������ ������ �ҷ�����, ������ �÷��̾� 10���� ����)
bool CMainGame::Initialize() {
	random_device rd;
	default_random_engine dre(rd());
	normal_distribution<> nd(0, 1);

	m_vecPlayerlist.reserve(CAPACITY);
	m_vecSchoolRank.reserve(CAPACITY);
	m_vecEscapeRank.reserve(CAPACITY);

	ofstream out("CookieRunData.dat", ios::_Nocreate);

	if (out.fail()) {	// ������ ������ ���ٸ� 100,000���� �÷��̾ �����Ѵ�.
		cout << "==========������ �������� �ʽ��ϴ�. 100,000���� �÷��̾ �����մϴ�.==========" << endl;
		for (int i = 0; i != m_vecPlayerlist.capacity(); ++i) {
			double dSchool_score=nd(dre);
			while (dSchool_score < -1.0 || 1.0 < dSchool_score) {
				dSchool_score = nd(dre);
			}
			dSchool_score += 1;
			dSchool_score *= AVERAGE_SCHOOL_SCORE;
			
			double dEscape_score=nd(dre);
			while (dEscape_score < -1.0 || 1.0 < dEscape_score) {
				dEscape_score = nd(dre);
			}
			dEscape_score += 1;
			dEscape_score *= AVERAGE_ESCAPE_SCORE;
			m_vecPlayerlist.emplace_back(new CPlayer(string("Player") + to_string(i + 1), dSchool_score, dEscape_score));
		}
		m_vecSchoolRank = m_vecPlayerlist;
		SetSchoolRank();
		m_vecEscapeRank = m_vecPlayerlist;
		SetEscapeRank();

		SetMyPlayer();

		Save();
		cout << "=====================�÷��̾� 100,000���� ���� �Ǿ����ϴ�.======================" << endl;
		system("pause");
	}
	else {
		cout << "================���Ͽ��� �÷��̾��� �����͸� �о���� ���Դϴ�.=================" << endl;
		Load();
		SetMyPlayer();
		cout << "================================�ҷ����� ����!==================================" << endl;
		system("pause");
	}

	return true;
}

void CMainGame::GameProgress() {
	int iOption;

	while (true) {
		system("cls");
		cout << "====================================" << endl;
		cout << "||1. ��Ű�� �÷��� 2. ���� 3. ����||" << endl;
		cout << "====================================" << endl;
		cin >> iOption;

		switch (iOption)
		{
		case 1:
			PlayCookieRun();
			break;
		case 2:
			Save();
			break;
		case 3:
			return;
			break;	
		default:
			cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է��ϼ���." << endl;
			break;
		}
		cout << "�Ϸ�." << endl;
		system("pause");
	}
}

// �����͸� ����
void CMainGame::Save(){
	vector<CPlayer> vecTempdata;
	vecTempdata.reserve(CAPACITY);

	for (const shared_ptr<CPlayer> & p : m_vecPlayerlist) {
		vecTempdata.emplace_back(*p);
	}
		
	ofstream out("CookieRunData.dat", ios::binary);
	out.write((const char*)vecTempdata.data(), sizeof(CPlayer) * CAPACITY);
}

void CMainGame::Load(){	
	vector<CPlayer> vecTempList(CAPACITY);

	ifstream in("CookieRunData.dat", ios::binary);
	in.read((char*)vecTempList.data(), sizeof(CPlayer) * CAPACITY);
	
	for (int i = 0; static_cast<unsigned int>(i) < vecTempList.size(); ++i) {
		m_vecPlayerlist.emplace_back(make_shared<CPlayer>(vecTempList[i]));
	}
	m_vecSchoolRank = m_vecPlayerlist;
	SetSchoolRank();
	m_vecEscapeRank = m_vecPlayerlist;
	SetEscapeRank();
}

void CMainGame::SetMyPlayer(){
	m_player = m_vecPlayerlist[0];
	m_player->SetID();
}

void CMainGame::SetSchoolRank() {
	int rank = 1;
	sort(begin(m_vecSchoolRank), end(m_vecSchoolRank), [](const shared_ptr<CPlayer>& p1, const shared_ptr<CPlayer>& p2) {
		return p1->GetSchoolScore() > p2->GetSchoolScore();
	});
	for (shared_ptr<CPlayer>& p : m_vecSchoolRank) {
		p->SetSchoolRank(rank++);
	}
}
void CMainGame::SetEscapeRank(){
	int rank = 1;
	sort(begin(m_vecEscapeRank), end(m_vecEscapeRank), [](const shared_ptr<CPlayer>& p1, const shared_ptr<CPlayer>& p2) {
		return p1->GetEscapeScore() > p2->GetEscapeScore();
	});
	for (shared_ptr<CPlayer>& p : m_vecEscapeRank) {
		p->SetEscapeRank(rank++);
	}
}

void  CMainGame::PlaySchool() {
	random_device rd;
	default_random_engine dre(rd());
	normal_distribution<> nd(0, 1);

	while (true){
		double dSchool_score = nd(dre);

		while (dSchool_score < -1.0 || 1.0 < dSchool_score) {
			dSchool_score = nd(dre);
		}
		dSchool_score += 1;
		dSchool_score *= AVERAGE_SCHOOL_SCORE;
		if (m_player->GetSchoolScore() < dSchool_score) {
			m_player->SetSchoolScore(dSchool_score);
		}
		break;
	}

	int iPlayed_count = 1;

	for(int i = 0; i< 10000; ++i){
		double dIndex = nd(dre);

		while (dIndex < -1.0 || 1.0 < dIndex) {
			dIndex = nd(dre);
		}

		dIndex += 1;
		dIndex *= CAPACITY / 2;

		double dSchool_score = nd(dre);

		while (dSchool_score < -1.0 || 1.0 < dSchool_score) {
			dSchool_score = nd(dre);
		}
		dSchool_score += 1;
		dSchool_score *= AVERAGE_SCHOOL_SCORE;

		if (!m_vecSchoolRank[int(dIndex)]->GetPlayed()) {
			if (m_vecSchoolRank[int(dIndex)]->GetSchoolScore() < dSchool_score) {
				m_vecSchoolRank[int(dIndex)]->SetSchoolScore(dSchool_score);
			}
			m_vecSchoolRank[int(dIndex)]->SetPlayed();
			++iPlayed_count;
		}
		else {
			continue;
		}
	}
}

void  CMainGame::PlayEscape() {
	random_device rd;
	default_random_engine dre(rd());
	normal_distribution<> nd(0, 1);

	while (true) {
		double dEscape_score = nd(dre);

		while (dEscape_score < -1.0 || 1.0 < dEscape_score) {
			dEscape_score = nd(dre);
		}
		dEscape_score += 1;
		dEscape_score *= AVERAGE_ESCAPE_SCORE;
		if (m_player->GetEscapeScore() < dEscape_score) {
			m_player->SetEscapeScore(dEscape_score);
		}
		break;
	}

	int iPlayed_count = 1;

	for (int i = 0; i < 10000; ++i) {
		double dIndex = nd(dre);

		while (dIndex < -1.0 || 1.0 < dIndex) {
			dIndex = nd(dre);
		}

		dIndex += 1;
		dIndex *= CAPACITY / 2;

		double dEscape_score = nd(dre);

		while (dEscape_score < -1.0 || 1.0 < dEscape_score) {
			dEscape_score = nd(dre);
		}
		dEscape_score += 1;
		dEscape_score *= AVERAGE_ESCAPE_SCORE;

		if (!m_vecEscapeRank[int(dIndex)]->GetPlayed()) {
			if (m_vecEscapeRank[int(dIndex)]->GetEscapeScore() < dEscape_score) {
				m_vecEscapeRank[int(dIndex)]->SetEscapeScore(dEscape_score);
			}
			m_vecEscapeRank[int(dIndex)]->SetPlayed();
			++iPlayed_count;
		}
		else {
			continue;
		}
	}
}

void CMainGame::PlayCookieRun() {
	int iPre_SchoolRank = m_player->GetSchoolRank();
	int iPre_EscapeRank = m_player->GetEscapeRank();

	PlaySchool();
	PlayEscape();

	SetSchoolRank();
	SetEscapeRank();
	
	// �б� �÷��� ����
	cout << "====================��Ű �Ʒü�====================" << endl;
	cout << "�� ���: " << m_player->GetSchoolRank() << "(" << iPre_SchoolRank - m_player->GetSchoolRank() << "), ���� " 
		<< double(m_player->GetSchoolRank()) / double(CAPACITY) * 100.0 << "%, ����: " << m_player->GetSchoolScore() << endl << endl;
	if (2 < m_player->GetSchoolRank() && m_player->GetSchoolRank() < CAPACITY) {
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolRank() << endl;
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolRank() << endl;
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolRank() << endl;
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank() +1]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() +1]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() +1]->GetSchoolRank() << endl;
	} 
	else if (m_player->GetSchoolRank() == 1) {
		cout << "�����մϴ�. 1���� �ϼ̱���!" << endl;
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolRank() << endl;
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank() + 1]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() + 1]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() + 1]->GetSchoolRank() << endl;
	}
	else if (m_player->GetSchoolRank() == CAPACITY) {
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolRank() << endl;
		cout << "���� ���: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetID() << ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolScore()
			<< ", ����: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolRank() << endl;
		cout << "�õ� �ϼ̽��ϴ�. �й� �ϼ���." << endl;
	}
	// �� Ż�� �÷��� ����
	cout << "===================================================" << endl;
	cout << "======================�� Ż��======================" << endl;
	cout << "�� ���: " << m_player->GetEscapeRank() << "(" << iPre_EscapeRank - m_player->GetEscapeRank() << "), ���� "
		<< double(m_player->GetEscapeRank()) / double(CAPACITY) * 100.0 << "%, ����: " << m_player->GetEscapeScore() << endl << endl;
	if (2 < m_player->GetEscapeRank() && m_player->GetEscapeRank() < CAPACITY) {
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeRank() << endl;
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeRank() << endl;
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeRank() << endl;
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeRank() << endl;
	}
	else if (m_player->GetEscapeRank() == 1) {
		cout << "�����մϴ�. 1���� �ϼ̱���!" << endl;
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeRank() << endl;
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeRank() << endl;
	}
	else if (m_player->GetEscapeRank() == CAPACITY) {
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeRank() << endl;
		cout << "���� ���: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetID() << ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeScore()
			<< ", ����: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeRank() << endl;
		cout << "�õ� �ϼ̽��ϴ�. �й� �ϼ���." << endl;

	}
	cout << "===================================================" << endl;
}