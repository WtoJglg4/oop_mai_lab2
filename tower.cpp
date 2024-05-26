/********************************************************************
 *          ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП 4 СЕМЕСТР                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : tower	                                        *
 * File Name     : tower.cpp                                        *
 * Programmer(s) : Глазов Вадим Викторович М3О-209Б-22			    *
 * Modifyed By   :                                                  *
 * Created       : 10/04/2024                                       *
 * Last Revision : 16/04/2024                                       *
 * Comment(s)    : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ						*
 *******************************************************************/

#include <windows.h>
#include <iostream>  
#include "tower.h"			//объявление классов
using namespace std;        // Пространство имен std

extern HDC hdc;     		// объявление  контекста устройства
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

#define ARR_SIZE 4 			//размер массива конфликтных объектов
extern Object objects[4];
extern int objectIndex; 	//флаг, показывающий объект, с которым произошло столкновение
extern Point Start;
extern int ObjectWidht;
extern int ObjectHigh;
const int timeToSleep = 5; 	// время для задержки экрана в мс

/*----------------------------------------------------------------*/
/*             		ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ		                  */
/*----------------------------------------------------------------*/

void FillCirlce(HDC hdc, int x, int y, int radius){
	for (int i = radius; i > 0; i--){
		Ellipse(hdc, x - i, y - i, x + i, y + i);
	}
}

void FillSquare(HDC hdc, int x, int y, int radius){
	for (int i = radius; i > 0; i--){
		Rectangle(hdc, x - i, y - i, x + i, y + i);
	}
}

int DetectCollisionWithObjects(Tower& tower){
	for (int i = 0; i < ARR_SIZE; i++) {
		if (objects[i].Collision(tower)) {
			objectIndex = i;
			return i;
		}
	}
	return -1;
}

/*----------------------------------------------------------------*/
/*             Р Е А Л И З А Ц И Я    М Е Т О Д О В               */
/*----------------------------------------------------------------*/

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Location          */
/*----------------------------------------*/
Location:: Location(int InitX, int InitY) {
	x = InitX;
	y = InitY;
};

Location:: ~Location() {
};

int Location:: GetX() {
	return x;
};

int Location:: GetY() {
	return y;
};

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Point             */
/*----------------------------------------*/

Point:: Point(int InitX, int InitY) : Location(InitX, InitY) {
	visible = false;
}

Point:: ~Point(){
}

void Point:: Show() {
	visible = true;
	SetPixel(hdc, x+1, y, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x, y+1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x, y-1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y-1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y+1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y-1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y+1, RGB(255, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, x, y, RGB(255, 0, 0));//рисуем синим цветом или фона
}

void Point:: Hide() {
	visible = false;

	SetPixel(hdc, x+1, y, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y,RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x, y+1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x, y-1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y-1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x-1, y+1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y-1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x+1, y+1, RGB(255, 255, 255));//рисуем синим цветом или фона
	SetPixel(hdc, x, y, RGB(255, 255, 255));//рисуем синим цветом или фона

}

bool Point:: IsVisible() {
	return visible;
};

void Point:: MoveTo(int NewX, int NewY) {
	Hide();		//скрыть точку
	x = NewX;
	y = NewY;
	Show();		//показать точку
};

void Point:: Drag(int Step) {
	//получение координат точки
	int figX = GetX();
	int figY = GetY();

	//бесконечный цикл
	while (true) {
		if (KEY_DOWN(VK_ESCAPE)) break;	//esc - выход

		//перемещение фигуры в зависимости от нажатой стрелки
		if (KEY_DOWN(VK_LEFT)) figX -= Step;

		if (KEY_DOWN(VK_RIGHT)) figX += Step;

		if (KEY_DOWN(VK_UP)) figY -= Step;

		if (KEY_DOWN(VK_DOWN)) figY += Step;

		MoveTo(figX, figY);
		Sleep(timeToSleep);
	}
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Tower             */
/*----------------------------------------*/

Tower:: Tower(int InitX, int InitY, int InitBaseLength, int InitObservationRadius, int InitTotalHigh) : Point(InitX, InitY) {
	BaseLength = InitBaseLength;
	ObservationRadius = InitObservationRadius;
	TotalHigh = InitTotalHigh;

	rightSideHB = x + BaseLength / 2;
	downSideHB = y + BaseLength / 8;
	leftSideHB = x - BaseLength / 2;	
	upSideHB = y - TotalHigh;
	index = 0;
}

Tower:: ~Tower() {
}

void Tower:: MoveTo(int NewX, int NewY) {
	Hide();		//скрыть точку
	x = NewX;
	y = NewY;
	rightSideHB = x + BaseLength / 2;
	downSideHB = y + BaseLength / 8;
	leftSideHB = x - BaseLength / 2;	
	upSideHB = y - TotalHigh;
	Show();		//показать точку
};

void Tower:: DrawHitbox(HPEN pen){
	SelectObject(hdc, pen);

	MoveToEx(hdc, leftSideHB, upSideHB, NULL);
	LineTo(hdc, rightSideHB , upSideHB);
	LineTo(hdc, rightSideHB , downSideHB);
	LineTo(hdc, leftSideHB , downSideHB);
	LineTo(hdc, leftSideHB , upSideHB);
}

void Tower:: Draw(HPEN pen){
	SelectObject(hdc, pen);

	// фундамент
	Rectangle(hdc, x - BaseLength / 2 , y - BaseLength / 8, x + BaseLength / 2 , y + BaseLength / 8);
	int ObservationHigh = TotalHigh * 7 / 10;	//координаты центра смотровой площадки
	
	//смотровая площадка
	Ellipse(hdc, x - ObservationRadius, y - ObservationHigh - ObservationRadius, x + ObservationRadius, y - ObservationHigh + ObservationRadius);
	Rectangle(hdc, x - ObservationRadius / 2 , y - ObservationHigh + ObservationRadius, x + ObservationRadius / 2 , y - ObservationHigh + 3 * ObservationRadius / 2);
	Rectangle(hdc, x - ObservationRadius / 4 , y - ObservationHigh - 5 * ObservationRadius / 3, x + ObservationRadius / 4 , y - ObservationHigh - ObservationRadius);
	
	//сама башня
	MoveToEx(hdc, x - BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x - ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	MoveToEx(hdc, x + BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x + ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	//шпиль
	MoveToEx(hdc,  x - ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3, NULL);
	LineTo(hdc, x , y - TotalHigh);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3);
}

void Tower::  Show() {
	visible = true;
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	Draw(pen);
	DeleteObject(pen);

	//отрисовка хитбокса
	// HPEN gray = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));	//серый
	// DrawHitbox(gray);
	// DeleteObject(gray);
}

void Tower:: Hide() {
	visible = false;
	HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(pen);
	// DrawHitbox(pen);
	DeleteObject(pen);
}

void Tower:: Drag(int Step) {
	//получение координат точки
	int figX = GetX();
	int figY = GetY();
	int collisionIndex = -1;

	//бесконечный цикл
	while (true) {
		
		if (KEY_DOWN(VK_ESCAPE)) break;	//esc

		if (KEY_DOWN(VK_LEFT)) {	
			figX -= Step;
			leftSideHB -= Step;
			rightSideHB -= Step;
		}

		if (KEY_DOWN(VK_RIGHT)) { 
			figX += Step;
			rightSideHB += Step;
			leftSideHB += Step;
		}

		if (KEY_DOWN(VK_DOWN)) {
			figY += Step;
			downSideHB += Step;
			upSideHB += Step;
		}

		if (KEY_DOWN(VK_UP)) { //38 стрелка вверх		
			figY -= Step;
			downSideHB -= Step;
			upSideHB -= Step;
		}

		collisionIndex = DetectCollisionWithObjects(*this);
		if (collisionIndex != -1) {
			Hide();
			MoveTo(Start.GetX(), Start.GetY());
			return;
		}
		
		MoveTo(figX, figY);
		Sleep(timeToSleep);
	}
}

int Tower:: GetRightSideHB(){
	return rightSideHB;
}

int Tower:: GetDownSideHB(){
	return downSideHB;
}

int Tower:: GetLeftSideHB(){
	return leftSideHB;
}

int Tower:: GetUpSideHB(){
	return upSideHB;
}

int Tower:: GetIndex(){
	return index;
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА BrokenTower       */
/*----------------------------------------*/

BrokenTower:: BrokenTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh): Tower(InitX, InitY, BaseLength, ObservationRadius, TotalHigh){
	index = 1;
}

BrokenTower:: ~BrokenTower(){

}
		
void BrokenTower:: Draw(HPEN pen){
	SelectObject(hdc, pen);

	// фундамент
	Rectangle(hdc, x - BaseLength / 2 , y - BaseLength / 8, x + BaseLength / 2 , y + BaseLength / 8);
	int ObservationHigh = TotalHigh * 7 / 10;	//координаты центра смотровой площадки
	
	//смотровая площадка
	Ellipse(hdc, x - ObservationRadius, y - ObservationHigh - ObservationRadius, x + ObservationRadius, y - ObservationHigh + ObservationRadius);
	Rectangle(hdc, x - ObservationRadius / 2 , y - ObservationHigh + ObservationRadius, x + ObservationRadius / 2 , y - ObservationHigh + 3 * ObservationRadius / 2);
	Rectangle(hdc, x - ObservationRadius / 4 , y - ObservationHigh - 5 * ObservationRadius / 3, x + ObservationRadius / 4 , y - ObservationHigh - ObservationRadius);
	
	//сама башня
	MoveToEx(hdc, x - BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x - ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	MoveToEx(hdc, x + BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x + ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	//шпиль
	MoveToEx(hdc,  x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3, NULL);
	// LineTo(hdc, x + (TotalHigh - ObservationHigh), y - ObservationHigh - 5 * ObservationRadius / 3);
	LineTo(hdc, x +  BaseLength, y - ObservationHigh - 5 * ObservationRadius / 3);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 2 * ObservationRadius);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА PaintedTower      */
/*----------------------------------------*/

PaintedTower:: PaintedTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh): Tower(InitX, InitY, BaseLength, ObservationRadius, TotalHigh){
	index = 2;
}

PaintedTower:: ~PaintedTower(){

}
		
void PaintedTower:: Draw(HPEN white, HPEN blue){
	SelectObject(hdc, white);

	// фундамент
	Rectangle(hdc, x - BaseLength / 2 , y - BaseLength / 8, x + BaseLength / 2 , y + BaseLength / 8);
	int ObservationHigh = TotalHigh * 7 / 10;	//координаты центра смотровой площадки
	
	//смотровая площадка
	SelectObject(hdc, blue);
	FillCirlce(hdc, x, y - ObservationHigh, ObservationRadius);
	SelectObject(hdc, white);
	Rectangle(hdc, x - ObservationRadius / 2 , y - ObservationHigh + ObservationRadius, x + ObservationRadius / 2 , y - ObservationHigh + 3 * ObservationRadius / 2);
	Rectangle(hdc, x - ObservationRadius / 4 , y - ObservationHigh - 5 * ObservationRadius / 3, x + ObservationRadius / 4 , y - ObservationHigh - ObservationRadius);
	
	//сама башня
	MoveToEx(hdc, x - BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x - ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	MoveToEx(hdc, x + BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x + ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	//шпиль
	MoveToEx(hdc,  x - ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3, NULL);
	LineTo(hdc, x , y - TotalHigh);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3);
}

void PaintedTower::  Show() {
	visible = true;
	HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN blue = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	Draw(red, blue);
	DeleteObject(red);
	DeleteObject(blue);

	// HPEN gray = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));	//серый
	// DrawHitbox(gray);
	// DeleteObject(gray);
}

void PaintedTower:: Hide() {
	visible = false;
	HPEN white = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(white, white);
	// DrawHitbox(white);
	DeleteObject(white);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА SqareTower        */
/*----------------------------------------*/

SqareTower:: SqareTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh): Tower(InitX, InitY, BaseLength, ObservationRadius, TotalHigh){
	index = 3;
}

SqareTower:: ~SqareTower(){

}

void SqareTower::  Show() {
	visible = true;
	HPEN red = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN black = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	Draw(red, black);
	DeleteObject(red);
	DeleteObject(black);
}

void SqareTower:: Hide() {
	visible = false;
	HPEN white = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(white, white);
	// DrawHitbox(white);
	DeleteObject(white);
}
		
void SqareTower:: Draw(HPEN pen1, HPEN pen2){
	SelectObject(hdc, pen1);

	// фундамент
	Rectangle(hdc, x - BaseLength / 2 , y - BaseLength / 8, x + BaseLength / 2 , y + BaseLength / 8);
	int ObservationHigh = TotalHigh * 7 / 10;	//координаты центра смотровой площадки
	
	//Черный квадрат
	SelectObject(hdc, pen2);
	FillSquare(hdc, x, y - ObservationHigh, ObservationRadius);

	SelectObject(hdc, pen1);

	//подставки
	Rectangle(hdc, x - ObservationRadius / 2 , y - ObservationHigh + ObservationRadius, x + ObservationRadius / 2 , y - ObservationHigh + 3 * ObservationRadius / 2);
	Rectangle(hdc, x - ObservationRadius / 4 , y - ObservationHigh - 5 * ObservationRadius / 3, x + ObservationRadius / 4 , y - ObservationHigh - ObservationRadius);
	
	//сама башня
	MoveToEx(hdc, x - BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x - ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	MoveToEx(hdc, x + BaseLength / 4, y - BaseLength / 8, NULL);
	LineTo(hdc, x + ObservationRadius / 4, y - ObservationHigh + 3 * ObservationRadius / 2);

	//шпиль
	MoveToEx(hdc,  x - ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3, NULL);
	LineTo(hdc, x , y - TotalHigh);
	LineTo(hdc, x + ObservationRadius / 8, y - ObservationHigh - 5 * ObservationRadius / 3);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Objects           */
/*----------------------------------------*/

//формальный конструктор по умолчанию для создания массива
Object:: Object(): Point(0, 0) {	

}

//фактический конструктор
Object:: Object(int InitX, int InitY): Point(InitX, InitY) {
	//hitboxes
	rightSideHB = x + ObjectWidht / 2;
	downSideHB = y + ObjectHigh / 2;
	leftSideHB = x - ObjectWidht / 2;	
	upSideHB = y - ObjectHigh / 2;
}

Object:: ~Object() {

}

int Object:: GetIndex() {
	return index;
}

//опредление столкновения с каким-либо объектом
bool Object::Collision(Tower& tower) {
    // Получаем координаты хитбокса текущего объекта
    int leftA = this->leftSideHB;
    int rightA = this->rightSideHB;
    int topA = this->upSideHB;
    int bottomA = this->downSideHB;

    // Получаем координаты хитбокса другого объекта (башни)
    int leftB = tower.GetLeftSideHB();
    int rightB = tower.GetRightSideHB();
    int topB = tower.GetUpSideHB();
    int bottomB = tower.GetDownSideHB();

    // Проверяем, перекрываются ли хитбоксы
    bool horizontalOverlap = (leftA <= rightB) && (rightA >= leftB);
    bool verticalOverlap = (topA <= bottomB) && (bottomA >= topB);

    // Если есть перекрытие по обоим осям, значит прямоугольники сталкиваются
    return horizontalOverlap && verticalOverlap;
}

void Object:: Hide(){
	HPEN white = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	Draw(white);
}

void Object:: Show(){
	HPEN black = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	Draw(black);
}

void Object:: Draw(HPEN pen){
	
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Stone             */
/*----------------------------------------*/

Stone:: Stone(int InitX, int InitY, int r) : Object(InitX, InitY) {
	radius = r;
	index = 0;

	//расчет крайних координат
	rightSideHB = x + radius;
	downSideHB = y + radius;
	leftSideHB = x - radius;
	upSideHB = y - radius;
}

Stone:: ~Stone() {

}

void Stone:: Draw(HPEN pen){
	SelectObject(hdc, pen);
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
	DeleteObject(pen);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Stop             */
/*----------------------------------------*/
Stop:: Stop(int InitX, int InitY, int r, int s) : Object(InitX, InitY) {
	radius = r;
	index = 1;
	stick = s;

	//расчет крайних координат
	rightSideHB = x + radius;
	downSideHB = y;
	leftSideHB = x - radius;
	upSideHB = y - stick - 2 * radius;
}

Stop:: ~Stop() {
	 
}

void Stop:: Draw(HPEN pen){
	SelectObject(hdc, pen);	//сделаем перо активным
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y - stick);
	MoveToEx(hdc, x, y - radius - stick, NULL);
	Ellipse(hdc, x - radius, y - 2 * radius - stick, x + radius, y - stick); //знак
	Rectangle(hdc, x - 0.5 * radius, y - 1.25 * radius - stick, x + 0.5 * radius, y - 0.75 * radius - stick); //прямоугольник на знаке
	DeleteObject(pen);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Pond              */
/*----------------------------------------*/
Pond:: Pond(int InitX, int InitY, int r) : Object(InitX, InitY) {
	radius = r;
	index = 2;

	//расчет крайних координат, radius = 10
	rightSideHB = InitX + radius;
	downSideHB = InitY + radius / 4;
	leftSideHB = InitX - radius;
	upSideHB = InitY - radius / 4;
}

Pond:: ~Pond() {

}

void Pond:: Show(){
	HPEN black = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	Draw(black);
}

void Pond:: Draw(HPEN pen){
	SelectObject(hdc, pen);	//сделаем перо активным
	for (int i = radius; i > 0; i--){
		Ellipse(hdc, x - i, y - i/4, x + i, y + i/4); //лужа
	}
	DeleteObject(pen);
}

/*----------------------------------------*/
/*        МЕТОДЫ КЛАССА Tree              */
/*----------------------------------------*/
Tree:: Tree(int InitX, int InitY, int high) : Object(InitX, InitY) {
	High = high;
	index = 3;

	//расчет крайних координат
	rightSideHB = x + high / 4;
	downSideHB = y;
	leftSideHB = x - high / 4;
	upSideHB = y - high;
}

Tree:: ~Tree() {

}

void Tree:: Draw(HPEN pen){
	SelectObject(hdc, pen);	//сделаем перо активным

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y - High / 4);
	LineTo(hdc, x - High / 4, y - High / 4);
	LineTo(hdc, x, y - High / 2);
	LineTo(hdc, x + High / 4, y - High / 4);
	LineTo(hdc, x, y - High / 4);

	MoveToEx(hdc, x, y - 3 * High / 4, NULL);
	LineTo(hdc, x - High / 5, y - High / 2);
	LineTo(hdc, x + High / 5, y - High / 2);
	LineTo(hdc, x, y - 3 * High / 4);

	MoveToEx(hdc, x, y - High, NULL);
	LineTo(hdc, x - High / 6, y - 3 * High / 4);
	LineTo(hdc, x + High / 6, y - 3 * High / 4);
	LineTo(hdc, x, y - High);

	DeleteObject(pen);
}
