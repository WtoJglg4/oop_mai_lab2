/********************************************************************
 *          ������������ ������ �1 �� ��� 4 �������                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : tower	                                        *
 * File Name     : main.cpp		                                    *
 * Programmer(s) : ������ ����� �3�-209�-22                         *
 * Modifyed By   :                                                  *
 * Created       : 13/04/2024                                       *
 * Last Revision : 14/04/2024                                       *
 * Comment(s)    : ���������� �������� �������						*
 *******************************************************************/
#include <windows.h>
#include <iostream>    
using namespace std;

#include "tower.h" 
#include "tower.cpp" 

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HDC hdc;	// ������� �������� ����������
HWND GetConcolWindow() {
	char str[128];
	char title[128]="xxxxxxxxxxxxxxxxxx";
	// string title = "xxxxxxxxxxxxxxxxxx";	//����� ������ Windows
	GetConsoleTitle(str, sizeof((LPWSTR)str)); // �������� ��������� ����
	SetConsoleTitle(LPCSTR(title));						// ���������� ����� ��������� ����
	Sleep(100);									// ���� ����� ��������� ���� (100 ��);

	HWND hwnd = FindWindow(NULL, LPCSTR(title));// ���������� ���������� ����
	SetConsoleTitle(str);				//���������� ������� ���������

	return hwnd;//������� ���������� ����
}
HWND hwnd = GetConcolWindow(); //��������� �� ���������� ����

Object objects[4];
int objectIndex = -1; //������ �������� ������������
int ObjectWidht = 300;
int ObjectHigh = 300;
Point Start(400, 700);
int defaultStep = 5;


//���������� �������� �������� ������� ���������
//���������� Object ����� ����������� ������� �����


// g++ main.cpp -o main.exe -lgdi32
int main() {
	setlocale(LC_ALL, "ru");
	system("color F0");

	// 0 - tower
	// 1 - broken tower
	// 2 - blue tower
	// 3 - square tower
	//������� �������� (�� ������� ����������� �������, �� �������� �����)
	int TransMatrix[ARR_SIZE][ARR_SIZE] = {
	{3, 0, 1, 3},
	{0, 1, 2, 0},
	{1, 1, 2, 2},
	{2, 2, 3, 3}};

	if (hwnd != NULL) { //���� ���������� ����������
		hdc = GetWindowDC(hwnd); //������� �������� ���������� ��� ����������� ����

		if (hdc != 0) {	
			//��������� ����������
			int BaseLength = 120;
			int ObservationRadius = 50;
			int TotalHigh = 500;

			Tower tower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			BrokenTower brokenTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			PaintedTower paintedTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			SqareTower sqareTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);

			Tower* towers[ARR_SIZE] = {&tower, &brokenTower, &paintedTower, &sqareTower}; //������ �����
			Tower* currentTower = towers[0];

			//�������, � �������� ������������
			Stone stone(200, 200, 50);
			Stop stop(100, 700, 60, 100);
			Pond pond(900, 700, 250);
			Tree tree(1200, 400, 300);

			objects[0] = stone;
			objects[1] = stop;
			objects[2] = pond;
			objects[3] = tree;

			stone.Show();
			stop.Show();
			pond.Show();
			tree.Show();

			currentTower->Show(); 

			while (true) {
				currentTower->Drag(defaultStep);
				
				//����� � ���������� ������������
				if (objectIndex != -1) {
					currentTower->Hide();
					currentTower->MoveTo(Start.GetX(), Start.GetY()); //������� ����� �� ��������� �����

					currentTower = towers[TransMatrix[objectIndex][currentTower->GetIndex()]]; //������� � ������ �������

					currentTower->Show();
					objectIndex = -1;

					while (true) {
						if (KEY_DOWN(VK_ESCAPE)) { //esc, ����� �� ���������						
							return 0;
						}

						if (KEY_DOWN(VK_NUMPAD0)) { //����� 0, ����������� ��������						
							break;
						}
					}
				}
			}
		}
	}
	ReleaseDC(GetConsoleWindow(), hdc);
}


