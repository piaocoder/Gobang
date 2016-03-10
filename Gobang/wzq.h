////////////////////////////
//�������˹����ܡ�˫�˲���//
////////////////////////////

//����Ʈ���ųʸ�����//
//�����Ķ�������
//������/*++(...)++*/�����ǿ�����չ�ĵط�

// wzq.h: interface for the wzq class.
//
//////////////////////////////////////////////////////////////////////

//���������dim.h��
#if !defined(AFX_WZQ_H__F6209748_A637_4CAB_BB9C_9A71AE806015__INCLUDED_)
#define AFX_WZQ_H__F6209748_A637_4CAB_BB9C_9A71AE806015__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CDC2.h"

struct wzwin//��ʤ
{
	int winner;//0 û�л�ʤ 1 �� 2 ��
	int nx1;//����������
	int nx2;
	int ny1;
	int ny2;
};

struct wzsave//�����¼
{
	bool used;//�Ƿ�ʹ��
	bool color;//��ɫ
	int ix;//����
	int iy;
};

class wzq  
{
public:
	wzq(CDC2*tchessboard,CDC2*tchess_black,CDC2*tchess_white,CDC2*tmask,CDC2*dead,CDC*dc);
	wzq();
	virtual ~wzq();
	void NewGame();//����Ϸ
//��ʼ��
	void DrawQZ(int nx,int ny,bool style);//������
	void SetDc(CDC2*tchessboard,CDC2*tchess_black,CDC2*tchess_white,CDC2*tmask,CDC2*dead,CDC*dc);//����DC
	void redraw();//����Ҫ�ػ�ʱ����
//��ͼ
private:
	bool Black_pawn(int nx,int ny);//��ɫ����Black_pawn
	bool White_pawn(int nx,int ny);//��ɫ����White_pawn
public:
	bool downzi(int nx,int ny);//�ⲿ���ô˺�������
	bool bewinner(bool style,int nx,int ny);//�ж�ʤ��
//����
	bool goback();//����
	void record(int nx,int ny,bool style);//��¼
	bool getbackble()
	{ return steps <= 0 ? false : true; }//�Ƿ���Ի���
//����
	CPoint AiGo(bool color);//�˹������ⲿ����



//------------------------------AI�˹������ڲ�����--------------------------------------////
/**/private:																			/**/																
/**/	void fillin(bool color,bool player,bool type);									/**/
/**/	void get_chess_manual(int nx ,int ny,bool style,bool player,int st,bool type);	/**/	//ת��Ϊ����
/**/	void setall();																	/**/
/**/	void clear(bool style);															/**/
/**/	void checkgo(int x,int y,bool color,int nu,int inx,int iny);//Ԥ�⺯��			/**/
/**/	bool be_hand_out(int nx, int ny);	/*++�˴���ӽ��ֿ���++*/					/**/	//��Ϊ����
/**/	//��Ϊ����Ϥ������Ĺ�������û�����ý���										/**/
/**/	bool get_victory2(int x1,int y1,int x2,int y2,bool style);						/**/
/**/	char ntoc(char num,bool type,bool style);										/**/	//number to char
/**/	CPoint getmax(bool color);														/**/
/**/	CPoint get_victory(bool style);													/**/
/**/	int getAItype();																/**/	//�ҵ���ӽ�ʤ���ĵ�
//AI								//��μ�"�������㷨"								/**/
///-------------------------------------------------------------------------------------////



public:
			bool firstgo;	//false:��true:��
			bool secondgo;	//false:��true:��
			int nturn;
			wzwin twinner;
			int AItype;		//0��Ԥ��6�� 1��Ԥ��10�� 2��Ԥ��16��
			int Model;		//0��->�� 1��->�� 2����
			bool backable ;	//�Ƿ���� 0=N 1=Y
protected:

private:
			CDC2 *chessboard;		//����dc
			CDC2 *chess_black;		//����dc
			CDC2 *chess_white;		//����dc
			CDC2 *mask;				//����dc
			CDC2 *dead;				//����
			CDC	 *dc;				//����dc
			unsigned char user[15][15][4];	//�������
			unsigned char pc[15][15][4];	//�������
			char map[15][15];				//�������̵�ͼ
			unsigned char nicest[15][15];
			char trygo[15][15];
			bool DC_Seted;
			int steps;						//����
			int aitype2;
			wzsave wzs[225];
};

#endif // !defined(AFX_WZQ_H__F6209748_A637_4CAB_BB9C_9A71AE806015__INCLUDED_)
