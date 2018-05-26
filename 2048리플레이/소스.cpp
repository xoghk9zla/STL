#include <Windows.h>
#include <math.h>
#include <unordered_map>
#include <string>
#include <fstream>
#include "resources.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = "2048";	// 제목

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

struct Rect{
	int left, top, right, bottom, val;
	bool sel;
};

Rect board[4][4];	// 판
int Score, Goal, Max;	// 현재 점수, 목표 점수, 최대 도달 블럭
unordered_multimap<int, int> replaydata;

void NewGame();
void MakeBlock();
bool FullCheck();
bool MoveCheck();
bool LoseCheck();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	//윈도우 클래스 이름, 타이틀 이름, 스타일, x좌표, y좌표, 폭, 높이, 부모윈도우 핸들, 메뉴 핸들, 응용 프로그램id, 생성된 윈도우 정보
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 700, NULL, (HMENU)NULL, hInstance, NULL); 

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)){
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap, oldBitmap;
	static bool Move;	// 블록이 움직일 때 못 마우스 작동 못하게
	static int x1, y1;	// 판위치 초기화용
	static int Sx, Sy, Ex, Ey; // 마우스 드래그
	static int a, b, cnt;	// 블록 생성용, 블럭 이동 횟수
	static char buf[50];	// 게임 종료 시 현재 점수, 최대 도달 블럭을 출력하기 위한 문자열
	switch (uMsg)
	{
	case WM_CREATE:
		x1 = 50, y1 = 50, cnt = 0, Score = 0, Goal = 2048, Max = 0, Move = TRUE;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				board[i][j].left = x1, board[i][j].top = y1, board[i][j].right = x1 + 100, board[i][j].bottom = y1 + 100;
				board[i][j].val = 0, board[i][j].sel = FALSE;
				x1 += 100;
			}
			x1 = 50, y1 += 100;
		}
		MakeBlock();
		MakeBlock();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				Rectangle(hdc, board[i][j].left, board[i][j].top, board[i][j].right, board[i][j].bottom);
			}
		}
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				if (Max < board[i][j].val)
					Max = board[i][j].val;

				if (board[i][j].val == 2)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_2));
				else if (board[i][j].val == 4)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_4));
				else if (board[i][j].val == 8)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_8));
				else if (board[i][j].val == 16)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_16));
				else if (board[i][j].val == 32)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_32));
				else if (board[i][j].val == 64)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_64));
				else if (board[i][j].val == 128)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_128));
				else if (board[i][j].val == 256)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_256));
				else if (board[i][j].val == 512)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_512));
				else if (board[i][j].val == 1024)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_1024));
				else if (board[i][j].val == 2048)
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_2048));
				else
					hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_EMPTY));

				memdc = CreateCompatibleDC(hdc);
				SelectObject(memdc, hBitmap);
				oldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);
				StretchBlt(hdc, board[i][j].left + 1, board[i][j].top + 2, board[i][j].right - board[i][j].left, board[i][j].bottom - board[i][j].top, memdc, 0, 0, board[i][j].right - board[i][j].left, board[i][j].bottom - board[i][j].top, SRCCOPY);
				SelectObject(memdc, oldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(memdc);
			}
		}
		wsprintf(buf, "점수: %d", Score);
		TextOut(hdc, 500, 100, buf, strlen(buf));
		wsprintf(buf, "목표 점수: %d", Goal);
		TextOut(hdc, 500, 125, buf, strlen(buf));
		wsprintf(buf, "최대 도달 블럭: %d", Max);
		TextOut(hdc, 500, 150, buf, strlen(buf));
		
		if (LoseCheck()){
			wsprintf(buf, "점수: %d, 최고 블럭: %d", Score, Max);
			if (MessageBox(hWnd, buf, "게임 종료!", MB_OK) == IDOK){
				PostQuitMessage(0);
				return 0;
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		if (Move){
			Sx = LOWORD(lParam);
			Sy = HIWORD(lParam);
		}
		break;

	case WM_LBUTTONUP:
		if (Move){
			Ex = LOWORD(lParam);
			Ey = HIWORD(lParam);

			if (Sx > Ex && abs(Sx - Ex) > abs(Sy - Ey))
				SetTimer(hWnd, LEFT, 200, NULL);

			else if (Sx < Ex && abs(Sx - Ex) > abs(Sy - Ey))
				SetTimer(hWnd, RIGHT, 200, NULL);

			else if (Sy > Ey && abs(Sx - Ex) < abs(Sy - Ey))
				SetTimer(hWnd, UP, 200, NULL);

			else if (Sy < Ey && abs(Sx - Ex) < abs(Sy - Ey))
				SetTimer(hWnd, DOWN, 200, NULL);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if(Move)
				SetTimer(hWnd, LEFT, 200, NULL);
			break;
		case VK_RIGHT:
			if (Move)
				SetTimer(hWnd, RIGHT, 200, NULL);
			break;
		case VK_UP:
			if (Move)
				SetTimer(hWnd, UP, 200, NULL);
			break;
		case VK_DOWN:
			if (Move)
				SetTimer(hWnd, DOWN, 200, NULL);
			break;
		default:
			break;
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_NEW:
			NewGame();
			break;

		case ID_END:
			PostQuitMessage(0);
			break;

		case ID_END_256:
			Goal = 256;
			break;

		case ID_END_512:
			Goal = 512;
			break;

		case ID_END_1024:
			Goal = 1024;
			break;

		case ID_END_2048:
			Goal = 2048;
			break;

		case ID_SAVE: {	// 리플레이 저장 시작
			if (Move) {
				ofstream out("test.txt");
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						out << board[i][j].val << " ";
					}
				}
				out << Score << " " << Goal << " " << Max << endl;
			}
			break;
		}
		case ID_STOP:	// 리플레이 저장 종료
			if (Move) {


			}
			break;

		case ID_LOAD: {	// 리플레이 불러와서 실행
			if (Move) {
				ifstream in("test.txt");
				string s;
				// 파일 입출력으로 가져온 게임 판의 데이터를 int형으로 변환
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						in >> s;
						board[i][j].val = atoi(s.c_str());
					}
				}
				// 리플레이 저장이 시작 된 점수, 목표점수, 최대 도달 블럭을 가져옴
				in >> Score >> Goal >> Max;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		default:
			break;

		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_TIMER:
		Move = FALSE;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				if (board[i][j].val == Goal){
					KillTimer(hWnd, 1);
					KillTimer(hWnd, 2);
					KillTimer(hWnd, 3);
					KillTimer(hWnd, 4);
					wsprintf(buf, "점수: %d, 최고 블럭: %d", Score, Max);
					if (MessageBox(hWnd, buf, "게임 종료!", MB_OK) == IDOK){
						PostQuitMessage(0);
						return 0;
					}
				}
			}
		}
		switch (wParam)
		{
		case LEFT:
			for (int i = 0; i < 4; ++i){	// 왼쪽
				for (int j = 1; j < 4; ++j){
					if (board[i][j - 1].val == 0){	// 블럭 이동
						board[i][j - 1].val = board[i][j].val;
						board[i][j].val = 0;
					}
					if (board[i][j - 1].val == board[i][j].val){	// 블럭 합치기
						board[i][j - 1].val += board[i][j].val;
						Score += board[i][j].val;
						board[i][j].val = 0;
					}
				}
			}
			++cnt;
			if (cnt % 3 == 0){
				MakeBlock();
				KillTimer(hWnd, LEFT);
				Move = TRUE;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case RIGHT:
			for (int i = 0; i < 4; ++i){	// 오른쪽
				for (int j = 2; j >= 0; --j){
					if (board[i][j + 1].val == 0){
						board[i][j + 1].val = board[i][j].val;
						board[i][j].val = 0;
					}
					if (board[i][j + 1].val == board[i][j].val){
						board[i][j + 1].val += board[i][j].val;
						Score += board[i][j].val;
						board[i][j].val = 0;
					}
				}
			}
			++cnt;
			if (cnt % 3 == 0){
				MakeBlock();
				KillTimer(hWnd, RIGHT);
				Move = TRUE;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case UP:
			for (int j = 0; j < 4; ++j){	// 위쪽
				for (int i = 1; i < 4; ++i){
					if (board[i - 1][j].val == 0){
						board[i - 1][j].val = board[i][j].val;
						board[i][j].val = 0;
					}
					else if (board[i - 1][j].val == board[i][j].val){
						board[i - 1][j].val += board[i][j].val;
						Score += board[i][j].val;
						board[i][j].val = 0;
					}
				}
			}
			++cnt;
			if (cnt % 3 == 0){
				MakeBlock();
				KillTimer(hWnd, UP);
				Move = TRUE;
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case DOWN:
			for (int j = 0; j < 4; ++j){	// 아래쪽
				for (int i = 2; i >= 0; --i){
					if (board[i + 1][j].val == 0){
						board[i + 1][j].val = board[i][j].val;
						board[i][j].val = 0;
					}
					else if (board[i + 1][j].val == board[i][j].val){
						board[i + 1][j].val += board[i][j].val;
						Score += board[i][j].val;
						board[i][j].val = 0;
					}
				}
			}
			++cnt;
			if (cnt % 3 == 0){
				MakeBlock();
				KillTimer(hWnd, DOWN);
				Move = TRUE;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		default:
			break;

		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void NewGame(){
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			board[i][j].val = 0;
		}
	}
	Score = 0, Goal = 2048, Max = 0;
	MakeBlock();
	MakeBlock();
}
void MakeBlock(){
	int a, b, c;
	c = rand() % 2 + 1;
	while (FullCheck()){
		a = rand() % 4, b = rand() % 4;
		if (board[a][b].val == 0){
			board[a][b].val = c * 2;
			break;
		}
	}
}
bool FullCheck(){
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			if (board[i][j].val == 0)
				return TRUE;
		}
	}
	return FALSE;
}
bool MoveCheck(){
	for (int i = 0; i < 4; ++i){	// 왼쪽
		for (int j = 1; j < 4; ++j){
			if (board[i][j - 1].val == board[i][j].val){	// 블럭 합치기
				return TRUE;
			}
		}
	}
	for (int i = 0; i < 4; ++i){	// 오른쪽
		for (int j = 2; j >= 0; --j){
			if (board[i][j + 1].val == board[i][j].val){
				return TRUE;
			}
		}
	}
	for (int j = 0; j < 4; ++j){	// 위쪽
		for (int i = 1; i < 4; ++i){
			if (board[i - 1][j].val == board[i][j].val){
				return TRUE;
			}
		}
	}
	for (int j = 0; j < 4; ++j){	// 아래쪽
		for (int i = 2; i >= 0; --i){
			if (board[i + 1][j].val == board[i][j].val){
				return TRUE;
			}
		}
	}
	return FALSE;
}
bool LoseCheck(){
	if (FullCheck() == FALSE && MoveCheck() == FALSE)
		return TRUE;
	else
		return FALSE;
}