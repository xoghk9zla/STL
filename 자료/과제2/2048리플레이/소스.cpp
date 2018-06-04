#include <Windows.h>
#include <math.h>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include "resources.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define REPLAY 5

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = "2048";	// ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

struct Rect{
	int left, top, right, bottom, val;
	bool sel;
};

class Replay {
public:
	int dir;
	int elapsed_time;
	int random_position[2];
	int block_val;

public:
	Replay() {}
	Replay(int d, int e, int* r, int v): dir(d), elapsed_time(e), block_val(v){
		random_position[0] = r[0];
		random_position[1] = r[1];
	}

};

Rect board[4][4];	// ��
int Score, Goal, Max;	// ���� ����, ��ǥ ����, �ִ� ���� ��
DWORD start, finish;
Replay temp;
bool playing, save_replay;
list<Replay> replaydata;
auto p = replaydata.begin();
auto q = replaydata.end();
DWORD temp2;

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

	//������ Ŭ���� �̸�, Ÿ��Ʋ �̸�, ��Ÿ��, x��ǥ, y��ǥ, ��, ����, �θ������� �ڵ�, �޴� �ڵ�, ���� ���α׷�id, ������ ������ ����
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1200, 700, NULL, (HMENU)NULL, hInstance, NULL); 

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)){
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hdc, memdc;
	PAINTSTRUCT ps;
	static HBITMAP hBitmap, oldBitmap;
	static bool Move;	// ����� ������ �� �� ���콺 �۵� ���ϰ�
	static int x1, y1;	// ����ġ �ʱ�ȭ��
	static int Sx, Sy, Ex, Ey; // ���콺 �巡��
	static int a, b, cnt;	// ��� ������, �� �̵� Ƚ��
	static char buf[100];	// ���� ���� �� ���� ����, �ִ� ���� ���� ����ϱ� ���� ���ڿ�
	switch (uMsg)
	{
	case WM_CREATE:
		x1 = 50, y1 = 50, cnt = 0, Score = 0, Goal = 2048, Max = 0, Move = TRUE, playing = TRUE, save_replay = FALSE;
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
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

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				Rectangle(hdc, board[i][j].left, board[i][j].top, board[i][j].right, board[i][j].bottom);
			}
		}
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
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
		// ���� �ؽ�Ʈ�� ���
		wsprintf(buf, "���ѤѤѤ������ǤѤѤѤѦ�");
		TextOut(hdc, 475, 75, buf, strlen(buf));
		wsprintf(buf, "����: %d", Score);
		TextOut(hdc, 500, 100, buf, strlen(buf));
		wsprintf(buf, "��ǥ ����: %d", Goal);
		TextOut(hdc, 500, 125, buf, strlen(buf));
		wsprintf(buf, "�ִ� ���� ��: %d", Max);
		TextOut(hdc, 500, 150, buf, strlen(buf));
		wsprintf(buf, "���ѤѤѤѤѤѤѤѤѤѤѦ�");
		TextOut(hdc, 475, 175, buf, strlen(buf));
		if (!playing) {
			// ���÷��� ������ ���
			wsprintf(buf, "���ѤѤѤѤѤѤѤѸ��÷��̵����ͤѤѤѤѤѤѤѤѦ�");
			TextOut(hdc, 750, 75, buf, strlen(buf));
			wsprintf(buf, "���� �Է� �ð�: %d", p->elapsed_time);
			TextOut(hdc, 775, 100, buf, strlen(buf));
			wsprintf(buf, "���� �Է� ����(LEFT: 1, RIGHT: 2, UP: 3, DOWN: 4): %d", p->dir);
			TextOut(hdc, 775, 125, buf, strlen(buf));
			wsprintf(buf, "���� �� ���� ��ġ: (%d, %d), ���� ��: %d", p->random_position[0], p->random_position[1], p->block_val);
			TextOut(hdc, 775, 150, buf, strlen(buf));
			wsprintf(buf, "���ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѦ�");
			TextOut(hdc, 750, 175, buf, strlen(buf));
		}
		else {
			wsprintf(buf, "���ѤѤѤѤѤѤѤѸ��÷��̵����ͤѤѤѤѤѤѤѤѦ�");
			TextOut(hdc, 750, 75, buf, strlen(buf));
			wsprintf(buf, "���� �Է� �ð�: ����");
			TextOut(hdc, 775, 100, buf, strlen(buf));
			wsprintf(buf, "���� �Է� ����(LEFT: 1, RIGHT: 2, UP: 3, DOWN: 4): ����");
			TextOut(hdc, 775, 125, buf, strlen(buf));
			wsprintf(buf, "���� �� ���� ��ġ: ����, ���� ��: ����");
			TextOut(hdc, 775, 150, buf, strlen(buf));
			wsprintf(buf, "���ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѦ�");
			TextOut(hdc, 750, 175, buf, strlen(buf));
		}
		if (LoseCheck()) {
			wsprintf(buf, "����: %d, �ְ� ��: %d", Score, Max);
			if (MessageBox(hWnd, buf, "���� ����!", MB_OK) == IDOK) {
				PostQuitMessage(0);
				return 0;
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		if (Move) {
			Sx = LOWORD(lParam);
			Sy = HIWORD(lParam);
		}
		break;

	case WM_LBUTTONUP:
		if (Move) {
			Ex = LOWORD(lParam);
			Ey = HIWORD(lParam);

			if (Sx > Ex && abs(Sx - Ex) > abs(Sy - Ey)) {
				finish = GetTickCount();
				temp.dir = LEFT;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, LEFT, 200, NULL);
			}
			else if (Sx < Ex && abs(Sx - Ex) > abs(Sy - Ey)) {
				finish = GetTickCount();
				temp.dir = RIGHT;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, RIGHT, 200, NULL);
			}
			else if (Sy > Ey && abs(Sx - Ex) < abs(Sy - Ey)) {
				finish = GetTickCount();
				temp.dir = UP;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, UP, 200, NULL);
			}
			else if (Sy < Ey && abs(Sx - Ex) < abs(Sy - Ey)) {
				finish = GetTickCount();
				temp.dir = DOWN;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, DOWN, 200, NULL);
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (Move) {
				finish = GetTickCount();
				temp.dir = LEFT;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, LEFT, 200, NULL);
			}
			break;
		case VK_RIGHT:
			if (Move) {
				finish = GetTickCount();
				temp.dir = RIGHT;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, RIGHT, 200, NULL);
			}
			break;
		case VK_UP:
			if (Move) {
				finish = GetTickCount();
				temp.dir = UP;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, UP, 200, NULL);
			}
			break;
		case VK_DOWN:
			if (Move) {
				finish = GetTickCount();
				temp.dir = DOWN;
				temp.elapsed_time = finish - start;
				SetTimer(hWnd, DOWN, 200, NULL);
			}
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

		case ID_SAVE: {	// ���÷��� ���� ����
			if (!save_replay) {
				if (Move) {
					save_replay = TRUE;
					ofstream out("Replaydata.dat", ios::binary);
					replaydata.clear();
					for (int i = 0; i < 4; ++i) {
						for (int j = 0; j < 4; ++j) {
							out << board[i][j].val << " ";
						}
					}
					out << Score << " " << Goal << " " << Max << endl;
					start = GetTickCount();
				}
			}
			else {
				wsprintf(buf, "���÷��� ���� �� �Դϴ�.");
				MessageBox(hWnd, buf, "notice", MB_OK);
			}
			break;
		}
		case ID_STOP:	// ���÷��� ���� ����
			if (save_replay) {
				if (Move) {
					ofstream out("Replaydata.dat", ios::app, ios::binary);
					for (auto d : replaydata) {
						out << d.dir << " " << d.elapsed_time << " " << d.random_position[0] << " " << d.random_position[1] << " " << d.block_val << endl;
					}
					save_replay = FALSE;
				}
			}
			else {
				wsprintf(buf, "���÷��� ���� ���� �ƴմϴ�.");
				MessageBox(hWnd, buf, "notice", MB_OK);
			}
			break;

		case ID_LOAD: {	// ���÷��� �ҷ��ͼ� ����
			if (!save_replay) {
				if (Move) {
					ifstream in("Replaydata.dat", ios::_Nocreate);

					if (!in.fail()) {
						string s;
						// ���� ��������� ������ ���� ���� �����͸� int������ ��ȯ
						for (int i = 0; i < 4; ++i) {
							for (int j = 0; j < 4; ++j) {
								in >> s;
								board[i][j].val = atoi(s.c_str());
							}
						}
						// ���÷��� ������ ���� �� ����, ��ǥ����, �ִ� ���� ���� ������
						in >> Score >> Goal >> Max;

						list<Replay> temp;
						int dir;
						int elapsed_time;
						int random_position[2];
						int block_val;
						while (!in.eof()) {
							in >> dir >> elapsed_time >> random_position[0] >> random_position[1] >> block_val;
							temp.emplace_back(dir, elapsed_time, random_position, block_val);
						}
						replaydata = temp;
						p = replaydata.begin();
						q = replaydata.end();
						--q;
						temp2 = GetTickCount();
						playing = false;
						SetTimer(hWnd, REPLAY, 200, NULL);
					}
					else {
						wsprintf(buf, "�ҷ��� ������ �����ϴ�.");
						MessageBox(hWnd, buf, "notice", MB_OK);
					}
				}
			}
			else {
				wsprintf(buf, "���÷��� ���� �� �Դϴ�.");
				MessageBox(hWnd, buf, "notice", MB_OK);
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
		if(wParam != 5)
			Move = FALSE;
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				if (board[i][j].val == Goal){
					KillTimer(hWnd, 1);
					KillTimer(hWnd, 2);
					KillTimer(hWnd, 3);
					KillTimer(hWnd, 4);
					wsprintf(buf, "����: %d, �ְ� ��: %d", Score, Max);
					if (MessageBox(hWnd, buf, "���� ����!", MB_OK) == IDOK){
						PostQuitMessage(0);
						return 0;
					}
				}
			}
		}
		switch (wParam)
		{
		case LEFT:
			for (int i = 0; i < 4; ++i){	// ����
				for (int j = 1; j < 4; ++j){
					if (board[i][j - 1].val == 0){	// �� �̵�
						board[i][j - 1].val = board[i][j].val;
						board[i][j].val = 0;
					}
					if (board[i][j - 1].val == board[i][j].val){	// �� ��ġ��
						board[i][j - 1].val += board[i][j].val;
						Score += board[i][j].val;
						board[i][j].val = 0;
					}
				}
			}
			++cnt;
			if (cnt % 3 == 0){
				MakeBlock();
				start = GetTickCount();
				replaydata.emplace_back(temp);
				KillTimer(hWnd, LEFT);
				Move = TRUE;
				if (p != q) {
					++p;
					temp2 = GetTickCount();
					SetTimer(hWnd, REPLAY, 200, NULL);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case RIGHT:
			for (int i = 0; i < 4; ++i){	// ������
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
				start = GetTickCount();
				replaydata.emplace_back(temp);
				KillTimer(hWnd, RIGHT);
				Move = TRUE;
				if (p != q) {
					++p;
					temp2 = GetTickCount();
					SetTimer(hWnd, REPLAY, 200, NULL);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case UP:
			for (int j = 0; j < 4; ++j){	// ����
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
				start = GetTickCount();
				replaydata.emplace_back(temp);
				KillTimer(hWnd, UP);
				Move = TRUE;
				if (p != q) {
					++p;
					temp2 = GetTickCount();
					SetTimer(hWnd, REPLAY, 200, NULL);
				}
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case DOWN:
			for (int j = 0; j < 4; ++j){	// �Ʒ���
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
				start = GetTickCount();
				replaydata.emplace_back(temp);
				KillTimer(hWnd, DOWN);
				Move = TRUE;
				if (p != q) {
					++p;
					temp2 = GetTickCount();
					SetTimer(hWnd, REPLAY, 200, NULL);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case REPLAY: {
			playing = false;
			DWORD temp1 = GetTickCount() - temp2;
			int time = p->elapsed_time;
			time = time - temp1;
			if(p != q) {
				if (time < 0) {
					time -= temp1;
					SetTimer(hWnd, p->dir, 200, NULL);
					KillTimer(hWnd, REPLAY);
					break;
				}
				else {
					break;
				}
			}
			else {
				KillTimer(hWnd, REPLAY);
				playing = true;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
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
	if (playing) {
		int a, b, c;
		c = rand() % 2 + 1;
		while (FullCheck()) {
			a = rand() % 4, b = rand() % 4;
			if (board[a][b].val == 0) {
				board[a][b].val = c * 2;
				temp.random_position[0] = a;
				temp.random_position[1] = b;
				temp.block_val = c * 2;
				break;
			}
		}
	}
	else {
		board[p->random_position[0]][p->random_position[1]].val = p->block_val;
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
	for (int i = 0; i < 4; ++i){	// ����
		for (int j = 1; j < 4; ++j){
			if (board[i][j - 1].val == board[i][j].val){	// �� ��ġ��
				return TRUE;
			}
		}
	}
	for (int i = 0; i < 4; ++i){	// ������
		for (int j = 2; j >= 0; --j){
			if (board[i][j + 1].val == board[i][j].val){
				return TRUE;
			}
		}
	}
	for (int j = 0; j < 4; ++j){	// ����
		for (int i = 1; i < 4; ++i){
			if (board[i - 1][j].val == board[i][j].val){
				return TRUE;
			}
		}
	}
	for (int j = 0; j < 4; ++j){	// �Ʒ���
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