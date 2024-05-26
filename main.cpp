/********************************************************************
 *          ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП 4 СЕМЕСТР                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : tower	                                        *
 * File Name     : main.cpp		                                    *
 * Programmer(s) : Глазов Вадим М3О-209Б-22                         *
 * Modifyed By   :                                                  *
 * Created       : 13/04/2024                                       *
 * Last Revision : 14/04/2024                                       *
 * Comment(s)    : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ						*
 *******************************************************************/
#include <windows.h>
#include <iostream>    
using namespace std;

#include "tower.h" 
#include "tower.cpp" 

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HDC hdc;	// Объявим контекст устройства
HWND GetConcolWindow() {
	char str[128];
	char title[128]="xxxxxxxxxxxxxxxxxx";
	// string title = "xxxxxxxxxxxxxxxxxx";	//новая версия Windows
	GetConsoleTitle(str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(LPCSTR(title));						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, LPCSTR(title));// определяем дескриптор окна
	SetConsoleTitle(str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}
HWND hwnd = GetConcolWindow(); //указатель на консольное окно

Object objects[4];
int objectIndex = -1; //индекс предмета столкновения
int ObjectWidht = 300;
int ObjectHigh = 300;
Point Start(400, 700);
int defaultStep = 5;


//переписать основную иерархию черензх интерфейс
//переписать Object через абстрактный базовый класс


// g++ main.cpp -o main.exe -lgdi32
int main() {
	setlocale(LC_ALL, "ru");
	system("color F0");

	// 0 - tower
	// 1 - broken tower
	// 2 - blue tower
	// 3 - square tower
	//матрица перехода (по строкам конфликтные объекты, по столбцам башни)
	int TransMatrix[ARR_SIZE][ARR_SIZE] = {
	{3, 0, 1, 3},
	{0, 1, 2, 0},
	{1, 1, 2, 2},
	{2, 2, 3, 3}};

	if (hwnd != NULL) { //если дескриптор существует
		hdc = GetWindowDC(hwnd); //получим контекст устройства для консольного окна

		if (hdc != 0) {	
			//начальные координаты
			int BaseLength = 120;
			int ObservationRadius = 50;
			int TotalHigh = 500;

			Tower tower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			BrokenTower brokenTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			PaintedTower paintedTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);
			SqareTower sqareTower(Start.GetX(), Start.GetY(), BaseLength, ObservationRadius, TotalHigh);

			Tower* towers[ARR_SIZE] = {&tower, &brokenTower, &paintedTower, &sqareTower}; //массив башен
			Tower* currentTower = towers[0];

			//объекты, с которыми сталкиваемся
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
				
				//выход в результате столкновения
				if (objectIndex != -1) {
					currentTower->Hide();
					currentTower->MoveTo(Start.GetX(), Start.GetY()); //переход башни на начальное место

					currentTower = towers[TransMatrix[objectIndex][currentTower->GetIndex()]]; //переход к новому объекту

					currentTower->Show();
					objectIndex = -1;

					while (true) {
						if (KEY_DOWN(VK_ESCAPE)) { //esc, выход из программы						
							return 0;
						}

						if (KEY_DOWN(VK_NUMPAD0)) { //цифра 0, продолжение движения						
							break;
						}
					}
				}
			}
		}
	}
	ReleaseDC(GetConsoleWindow(), hdc);
}


