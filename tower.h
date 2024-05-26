#pragma once
/********************************************************************
 *          ������������ ������ �1 �� ��� 4 �������                 *
 *------------------------------------------------------------------*
 * Project Type  : Win64 Console Application                        *
 * Project Name  : Laba_OOP_1                                       *
 * File Name     : tower.h                                          *
 * Programmer(s) : ������ ����� �3�-209�-22           				*
 * Modifyed By   :                                                  *
 * Created       : 14/04/2023                                       *
 * Last Revision : 14/04/2023                                       *
 * Comment(s)    : ���������� �������� �������						*
 *******************************************************************/

/*-----------------------------------------------------------------------*/
/*                         � � � �    � � � � � �                        */
/*-----------------------------------------------------------------------*/

#define ARR_SIZE 4 //������ ������� ����������� ��������

/*-----------------------------------------------------------------------*/
/*                         � � � �    � � � � � �                        */
/*-----------------------------------------------------------------------*/

/*-----------------------  ����� Location -------------------------*/
class Location {
	protected:		
		int x;							//���������� X
		int y;							//���������� Y

	public:
		Location(int InitX, int InitY); //�����������
		~Location();                    //����������
		int GetX();						//�������� X ���������� �����
		int GetY();						//�������� Y ���������� �����
};

/*-----------------------  ����� Point ----------------------------------*/
class Point : public Location{
	protected:							
		bool visible;					//��������� �����

	public:
		Point(int InitX, int InitY);		//�����������
		~Point();							//����������

		bool IsVisible();					//�������� �������
		void MoveTo(int NewX, int NewY);	//�����������
		
		virtual void Drag(int Step); 		//����������
		virtual void Show();				//�������� 
		virtual void Hide();				//������
};

/*-----------------------  ����� Tower ----------------------------------*/
class Tower : public Point {
	protected:
		int BaseLength;						//����� ����������
		int ObservationRadius;				//������ ��������� ��������
		int TotalHigh;						//����� ������

		//hitbox sides
		int rightSideHB;	//������ ������� ��������
		int downSideHB;		//������ ������� ��������
		int leftSideHB;		//����� ������� ��������
		int upSideHB;		//������� ������� ��������
		int index;			//������ �������
	public:
		Tower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~Tower();
		void Show();
		void Hide();
		void MoveTo(int NewX, int NewY);
		void Drag(int Step);
		virtual void Draw(HPEN pen);				//���������� �����
		virtual void DrawHitbox(HPEN pen);			//���������� �������

		//������� ��������
		int GetRightSideHB();
		int GetDownSideHB();
		int GetLeftSideHB();
		int GetUpSideHB();

		int GetIndex();								//������ �������
};

/*-----------------------  ����� BrokenTower ----------------------------------*/
class BrokenTower : public Tower {
	public:
		BrokenTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~BrokenTower();
		void Draw(HPEN pen);
};

/*-----------------------  ����� PaintedTower ----------------------------------*/
class PaintedTower : public Tower {
	public:
		PaintedTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~PaintedTower();
		void Show();
		void Hide();
		void Draw(HPEN white, HPEN blue);
};

/*-----------------------  ����� SqareTower ----------------------------------*/
class SqareTower : public Tower {
	public:
		SqareTower(int InitX, int InitY, int BaseLength, int ObservationRadius, int TotalHigh);	
		~SqareTower();
		void Show();
		void Hide();
		void Draw(HPEN pen1, HPEN pen2);
};

/*-----------------------  ����� Object ----------------------------------*/
class Object: public Point {
	protected:
		int rightSideHB;	//������ ������� ��������
		int downSideHB;		//������ ������� ��������
		int leftSideHB;		//����� ������� ��������
		int upSideHB;		//������� ������� ��������
		int index;			//������ �������
			
	public:
		Object(int InitX, int InitY);
		Object();					//���������� �����������
		~Object();
		
		int GetIndex();				//������ �������

		bool Collision(Tower& car); //������������ ������������

		void Hide();
		void Show();
		virtual void Draw(HPEN pen);
};

/*-----------------------  ����� Stone ----------------------------------*/
class Stone : public Object {
	protected:
		int radius; //������ �����
	public:
		Stone(int InitX, int InitY, int r);
		~Stone();
		void Draw(HPEN pen);
};

/*-----------------------  ����� Stop ----------------------------------*/
class Stop : public Object {
	protected:
		int radius;
		int stick;
	public:
		Stop(int InitX, int InitY, int r, int stick);
		~Stop();
		void Draw(HPEN pen);
};

/*-----------------------  ����� Pond ----------------------------------*/
class Pond : public Object {
	protected:
		int radius;
	public:
		Pond(int InitX, int InitY, int r);
		~Pond();
		void Show();
		void Draw(HPEN pen);
};

/*-----------------------  ����� Tree ----------------------------------*/
class Tree : public Object {
	protected:
		int High;
	public:
		Tree(int InitX, int InitY, int High);
		~Tree();
		void Draw(HPEN pen);
};