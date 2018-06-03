#pragma once

#include "CPlayer.h"

class CMainGame {
private:
	shared_ptr<CPlayer> m_player;
	vector<shared_ptr<CPlayer>> m_vecPlayerlist;
	vector<shared_ptr<CPlayer>> m_vecSchoolRank;
	vector<shared_ptr<CPlayer>> m_vecEscapeRank;

public:
	CMainGame(void);
	~CMainGame(void);

public:
	bool Initialize();
	void GameProgress();
	void Save();
	void Load();

public:
	void SetMyPlayer();
	void SetSchoolRank();
	void SetEscapeRank();
	void PlaySchool();
	void PlayEscape();
	void PlayCookieRun();

};