////////////////////////////
//五子棋人工智能、双人操作//
////////////////////////////

//胡云飘、张呈庚制作//
//程序阅读声名：
//凡是有/*++(...)++*/处就是可以扩展的地方

// wzq.h: interface for the wzq class.
//
//////////////////////////////////////////////////////////////////////

//棋局声明在dim.h中
#if !defined(AFX_WZQ_H__F6209748_A637_4CAB_BB9C_9A71AE806015__INCLUDED_)
#define AFX_WZQ_H__F6209748_A637_4CAB_BB9C_9A71AE806015__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CDC2.h"

struct wzwin//获胜
{
	int winner;//0 没有获胜 1 白 2 黑
	int nx1;//五连的坐标
	int nx2;
	int ny1;
	int ny2;
};

struct wzsave//下棋记录
{
	bool used;//是否使用
	bool color;//颜色
	int ix;//坐标
	int iy;
};

class wzq  
{
public:
	wzq(CDC2*tchessboard,CDC2*tchess_black,CDC2*tchess_white,CDC2*tmask,CDC2*dead,CDC*dc);
	wzq();
	virtual ~wzq();
	void NewGame();//新游戏
//初始化
	void DrawQZ(int nx,int ny,bool style);//画棋子
	void SetDc(CDC2*tchessboard,CDC2*tchess_black,CDC2*tchess_white,CDC2*tmask,CDC2*dead,CDC*dc);//设置DC
	void redraw();//当需要重画时调用
//绘图
private:
	bool Black_pawn(int nx,int ny);//黑色下子Black_pawn
	bool White_pawn(int nx,int ny);//白色下子White_pawn
public:
	bool downzi(int nx,int ny);//外部调用此函数下子
	bool bewinner(bool style,int nx,int ny);//判断胜败
//下棋
	bool goback();//悔棋
	void record(int nx,int ny,bool style);//记录
	bool getbackble()
	{ return steps <= 0 ? false : true; }//是否可以悔棋
//操作
	CPoint AiGo(bool color);//人工智能外部控制



//------------------------------AI人工智能内部函数--------------------------------------////
/**/private:																			/**/																
/**/	void fillin(bool color,bool player,bool type);									/**/
/**/	void get_chess_manual(int nx ,int ny,bool style,bool player,int st,bool type);	/**/	//转换为棋谱
/**/	void setall();																	/**/
/**/	void clear(bool style);															/**/
/**/	void checkgo(int x,int y,bool color,int nu,int inx,int iny);//预测函数			/**/
/**/	bool be_hand_out(int nx, int ny);	/*++此处添加禁手控制++*/					/**/	//成为禁手
/**/	//因为不熟悉五子棋的规则，所以没有设置禁手										/**/
/**/	bool get_victory2(int x1,int y1,int x2,int y2,bool style);						/**/
/**/	char ntoc(char num,bool type,bool style);										/**/	//number to char
/**/	CPoint getmax(bool color);														/**/
/**/	CPoint get_victory(bool style);													/**/
/**/	int getAItype();																/**/	//找到最接近胜利的点
//AI								//请参见"五子棋算法"								/**/
///-------------------------------------------------------------------------------------////



public:
			bool firstgo;	//false:人true:机
			bool secondgo;	//false:人true:机
			int nturn;
			wzwin twinner;
			int AItype;		//0低预测6步 1中预测10步 2高预测16步
			int Model;		//0人->机 1机->人 2对翌
			bool backable ;	//是否悔棋 0=N 1=Y
protected:

private:
			CDC2 *chessboard;		//棋盘dc
			CDC2 *chess_black;		//黑子dc
			CDC2 *chess_white;		//白子dc
			CDC2 *mask;				//屏蔽dc
			CDC2 *dead;				//红子
			CDC	 *dc;				//窗口dc
			unsigned char user[15][15][4];	//储存棋局
			unsigned char pc[15][15][4];	//储存棋局
			char map[15][15];				//储存棋盘地图
			unsigned char nicest[15][15];
			char trygo[15][15];
			bool DC_Seted;
			int steps;						//步数
			int aitype2;
			wzsave wzs[225];
};

#endif // !defined(AFX_WZQ_H__F6209748_A637_4CAB_BB9C_9A71AE806015__INCLUDED_)
