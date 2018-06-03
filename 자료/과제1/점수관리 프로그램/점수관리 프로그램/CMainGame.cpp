#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

#include "CMainGame.h"

CMainGame::CMainGame(void) {}
CMainGame::~CMainGame(void) { 
	system("cls");
	cout << "================파일에 플레이어의 데이터를 저장하는 중입니다.=================" << endl; 
	Save(); 
	cout << "=================================저장 성공!===================================" << endl;
	system("pause");
}

// 초기화(파일이 있으면 불러오고, 없으면 플레이어 10만명 생산)
bool CMainGame::Initialize() {
	random_device rd;
	default_random_engine dre(rd());
	normal_distribution<> nd(0, 1);

	m_vecPlayerlist.reserve(CAPACITY);
	m_vecSchoolRank.reserve(CAPACITY);
	m_vecEscapeRank.reserve(CAPACITY);

	ofstream out("CookieRunData.dat", ios::_Nocreate);

	if (out.fail()) {	// 저장할 파일이 없다면 100,000명의 플레이어를 생성한다.
		cout << "==========파일이 존재하지 않습니다. 100,000명의 플레이어를 생성합니다.==========" << endl;
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
		cout << "=====================플레이어 100,000명이 생성 되었습니다.======================" << endl;
		system("pause");
	}
	else {
		cout << "================파일에서 플레이어의 데이터를 읽어오는 중입니다.=================" << endl;
		Load();
		SetMyPlayer();
		cout << "================================불러오기 성공!==================================" << endl;
		system("pause");
	}

	return true;
}

void CMainGame::GameProgress() {
	int iOption;

	while (true) {
		system("cls");
		cout << "====================================" << endl;
		cout << "||1. 쿠키런 플레이 2. 저장 3. 종료||" << endl;
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
			cout << "잘못 입력하셨습니다. 다시 입력하세요." << endl;
			break;
		}
		cout << "완료." << endl;
		system("pause");
	}
}

// 데이터를 저장
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
	
	// 학교 플레이 점수
	cout << "====================쿠키 훈련소====================" << endl;
	cout << "내 등수: " << m_player->GetSchoolRank() << "(" << iPre_SchoolRank - m_player->GetSchoolRank() << "), 상위 " 
		<< double(m_player->GetSchoolRank()) / double(CAPACITY) * 100.0 << "%, 점수: " << m_player->GetSchoolScore() << endl << endl;
	if (2 < m_player->GetSchoolRank() && m_player->GetSchoolRank() < CAPACITY) {
		cout << "이전 등수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolRank() << endl;
		cout << "이전 등수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolRank() << endl;
		cout << "이후 등수: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolRank() << endl;
		cout << "이후 등수: " << m_vecSchoolRank[m_player->GetSchoolRank() +1]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank() +1]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank() +1]->GetSchoolRank() << endl;
	} 
	else if (m_player->GetSchoolRank() == 1) {
		cout << "축하합니다. 1등을 하셨군요!" << endl;
		cout << "이후 등수: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank()]->GetSchoolRank() << endl;
		cout << "이후 등수: " << m_vecSchoolRank[m_player->GetSchoolRank() + 1]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank() + 1]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank() + 1]->GetSchoolRank() << endl;
	}
	else if (m_player->GetSchoolRank() == CAPACITY) {
		cout << "이전 등수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank() - 3]->GetSchoolRank() << endl;
		cout << "이전 등수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetID() << ", 점수: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolScore()
			<< ", 순위: " << m_vecSchoolRank[m_player->GetSchoolRank() - 2]->GetSchoolRank() << endl;
		cout << "꼴등 하셨습니다. 분발 하세요." << endl;
	}
	// 떼 탈출 플레이 점수
	cout << "===================================================" << endl;
	cout << "======================떼 탈출======================" << endl;
	cout << "내 등수: " << m_player->GetEscapeRank() << "(" << iPre_EscapeRank - m_player->GetEscapeRank() << "), 상위 "
		<< double(m_player->GetEscapeRank()) / double(CAPACITY) * 100.0 << "%, 점수: " << m_player->GetEscapeScore() << endl << endl;
	if (2 < m_player->GetEscapeRank() && m_player->GetEscapeRank() < CAPACITY) {
		cout << "이전 등수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeRank() << endl;
		cout << "이전 등수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeRank() << endl;
		cout << "이후 등수: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeRank() << endl;
		cout << "이후 등수: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeRank() << endl;
	}
	else if (m_player->GetEscapeRank() == 1) {
		cout << "축하합니다. 1등을 하셨군요!" << endl;
		cout << "이후 등수: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank()]->GetEscapeRank() << endl;
		cout << "이후 등수: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank() + 1]->GetEscapeRank() << endl;
	}
	else if (m_player->GetEscapeRank() == CAPACITY) {
		cout << "이전 등수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank() - 3]->GetEscapeRank() << endl;
		cout << "이전 등수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetID() << ", 점수: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeScore()
			<< ", 순위: " << m_vecEscapeRank[m_player->GetEscapeRank() - 2]->GetEscapeRank() << endl;
		cout << "꼴등 하셨습니다. 분발 하세요." << endl;

	}
	cout << "===================================================" << endl;
}