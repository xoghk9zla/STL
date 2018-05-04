#include "stdafx.h"

#include "CPlayer.h"
#include "CMainGame.h"

 int main() {
	CMainGame maingame;

	if (!maingame.Initialize()) {
		return 0;
	}

	maingame.GameProgress();
}