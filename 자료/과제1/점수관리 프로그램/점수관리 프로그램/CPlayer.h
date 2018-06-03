#pragma once

class CPlayer {
private:
	char m_sId[10];

private:
	int m_iSchool_Score = 0;
	int m_iSchool_Rank = 0;

private:
	int m_iEscape_Score = 0;
	int m_iEscape_Rank = 0;

private:
	bool m_bPlayed = false;

public:
	CPlayer(void);
	CPlayer(string sId, int iSchool_Score = 0, int iEscape_Score = 0);
	~CPlayer(void);

public:		// Getter
	int GetSchoolScore()const;
	int GetSchoolRank()const;

	int GetEscapeScore()const;
	int GetEscapeRank()const;

	string GetID()const;

	bool GetPlayed()const;

public:		// Setter
	void SetSchoolRank(int);
	void SetEscapeRank(int);

	void SetSchoolScore(int);
	void SetEscapeScore(int);
	
	void SetID();
	
	void SetPlayed();

public:	
	void Show()const;

public:
	friend ostream& operator<<(ostream& , const CPlayer& );

};