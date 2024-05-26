#pragma once
/********************************************************************
 *          ЛАБОРАТОРНАЯ РАБОТА №1 ПО ООП 4 СЕМЕСТР                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : Laba_OOP_1                                       *
 * File Name     : tower.h                                          *
 * Programmer(s) : Глазов Вадим М3О-209Б-22           				*
 * Modifyed By   :                                                  *
 * Created       : 14/04/2023                                       *
 * Last Revision : 14/04/2023                                       *
 * Comment(s)    : ПРОСТЕЙШАЯ ИЕРАРХИЯ КЛАССОВ						*
 *******************************************************************/

/*-----------------------------------------------------------------------*/
/*                         Т И П Ы    Д А Н Н Ы Х                        */
/*-----------------------------------------------------------------------*/

#define ARR_SIZE 4 //размер массива конфликтных объектов

/*-----------------------------------------------------------------------*/
/*                         Т И П Ы    Д А Н Н Ы Х                        */
/*-----------------------------------------------------------------------*/

/*-----------------------  Класс Location -------------------------*/
class Location {
	protected:		
		int x;							//координата X
		int y;							//координата Y

	public:
		Location(int InitX, int InitY); //конструктор
		~Location();                    //деструктор
		int GetX();						//получить X координату точки
		int GetY();						//получить Y координату точки
};

/*-----------------------  Класс Point ----------------------------------*/
class Point : public Location{
	protected:							
		bool visible;					//видимость точки

	public:
		Point(int InitX, int InitY);		//конструктор
		~Point();							//деструктор

		bool IsVisible();					//является видимой
		void MoveTo(int NewX, int NewY);	//переместить
		
		virtual void Drag(int Step); 		//буксировка
		virtual void Show();				//показать 
		virtual void Hide();				//скрыть
};

/*-----------------------  Класс Tower ----------------------------------*/
class Tower : public Point {
	protected:
		int BaseLength;						//длина фундамента
		int ObservationRadius;				//радиус смотровой площадки
		int TotalHigh;						//общая высота

		//hitbox sides
		int rightSideHB;	//правая граница хитбокса
		int downSideHB;		//нижняя граница хитбокса
		int leftSideHB;		//левая граница хитбокса
		int upSideHB;		//верхняя граница хитбокса
		int index;			//индекс объекта
	public:
		Tower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~Tower();
		void Show();
		void Hide();
		void MoveTo(int NewX, int NewY);
		void Drag(int Step);
		virtual void Draw(HPEN pen);				//нарисовать башню
		virtual void DrawHitbox(HPEN pen);			//нарисовать хитбокс

		//геттеры хитбокса
		int GetRightSideHB();
		int GetDownSideHB();
		int GetLeftSideHB();
		int GetUpSideHB();

		int GetIndex();								//геттер индекса
};

/*-----------------------  Класс BrokenTower ----------------------------------*/
class BrokenTower : public Tower {
	public:
		BrokenTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~BrokenTower();
		void Draw(HPEN pen);
};

/*-----------------------  Класс PaintedTower ----------------------------------*/
class PaintedTower : public Tower {
	public:
		PaintedTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~PaintedTower();
		void Show();
		void Hide();
		void Draw(HPEN white, HPEN blue);
};

/*-----------------------  Класс SqareTower ----------------------------------*/
class SqareTower : public Tower {
	public:
		SqareTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~SqareTower();
		void Show();
		void Hide();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  Класс Object ----------------------------------*/
class Object: public Point {
	protected:
		int rightSideHB;	//правая граница хитбокса
		int downSideHB;		//нижняя граница хитбокса
		int leftSideHB;		//левая граница хитбокса
		int upSideHB;		//верхняя граница хитбокса
		int index;			//индекс объекта
			
	public:
		Object(int InitX, int InitY);
		Object();					//формальный конструктор
		~Object();
		
		int GetIndex();				//геттер индекса

		bool Collision(Tower& car); //определитель столкновения

		void Hide();
		void Show();
		virtual void Draw(HPEN pen);
};

/*-----------------------  Класс Stone ----------------------------------*/
class Stone : public Object {
	protected:
		int radius; //радиус камня
	public:
		Stone(int InitX, int InitY, int r);
		~Stone();
		void Draw(HPEN pen);
};

/*-----------------------  Класс Stop ----------------------------------*/
class Stop : public Object {
	protected:
		int radius;
		int stick;
	public:
		Stop(int InitX, int InitY, int r, int stick);
		~Stop();
		void Draw(HPEN pen);
};

/*-----------------------  Класс Pond ----------------------------------*/
class Pond : public Object {
	protected:
		int radius;
	public:
		Pond(int InitX, int InitY, int r);
		~Pond();
		void Show();
		void Draw(HPEN pen);
};

/*-----------------------  Класс Tree ----------------------------------*/
class Tree : public Object {
	protected:
		int High;
	public:
		Tree(int InitX, int InitY, int High);
		~Tree();
		void Draw(HPEN pen);
};