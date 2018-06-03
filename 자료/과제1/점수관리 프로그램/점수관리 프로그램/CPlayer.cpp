#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"

#include "CPlayer.h"

CPlayer::CPlayer(void){}

CPlayer::CPlayer(string sId, int iSchool_Score, int iEscape_Score) :
m_iSchool_Score(iSchool_Score), m_iEscape_Score(iEscape_Score){
	strcpy(m_sId, sId.c_str());
	m_bPlayed = false;	
}
CPlayer::~CPlayer(void){}

ostream& operator<<(ostream&os, const CPlayer& player){
	os << player.m_sId << endl;
	return os;
}

void CPlayer::Show()const {
	cout << "ID: " << m_sId << endl;
	cout << "��Ű�Ʒü� ����: " << m_iSchool_Score << ", ��Ű �Ʒü� ��ŷ: " << m_iSchool_Rank << endl;
	cout << "�� Ż�� ����: " << m_iEscape_Score << ", �� Ż�� ��ŷ: " << m_iEscape_Rank << endl;
	cout << endl;
}

int CPlayer::GetSchoolScore()const { return m_iSchool_Score; }

int CPlayer::GetSchoolRank()const { return m_iSchool_Rank; };

int CPlayer::GetEscapeScore()const { return m_iEscape_Score; }
	
int CPlayer::GetEscapeRank()const { return m_iEscape_Rank; };

string CPlayer::GetID() const { return m_sId; }

bool CPlayer::GetPlayed()const { return m_bPlayed; }

void  CPlayer::SetSchoolRank(int rank) {
	m_iSchool_Rank = rank;
}
void  CPlayer::SetEscapeRank(int rank) {
	m_iEscape_Rank = rank;
} 

void CPlayer::SetSchoolScore(int score) {
	m_iSchool_Score = score;
}
void CPlayer::SetEscapeScore(int score) {
	m_iEscape_Score = score;
}

void CPlayer::SetID() {
	string tempname = "��";
	strcpy(m_sId, tempname.c_str());
}

void CPlayer::SetPlayed() {
	m_bPlayed = true;
}