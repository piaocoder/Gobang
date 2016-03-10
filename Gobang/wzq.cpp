// wzq.cpp: implementation of the wzq class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Gobang.h"
#include "wzq.h"
#include "dim.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*___________________________________________________________________________________________*/
wzq::~wzq(){}
/*___________________________________________________________________________________________*/
wzq::wzq()
{	wzq::DC_Seted = false; }
/*___________________________________________________________________________________________*/

wzq::wzq(CDC2*tchessboard,CDC2*tchess_black,CDC2*tchess_white,CDC2*tmask,CDC2*dead,CDC*dc)
{
	SetDc(tchessboard,tchess_black,tchess_white,tmask,dead,dc);
}

void wzq::DrawQZ(int nx,int ny,bool style)//画棋子			//style == false是画白棋，style == true是画黑棋
{
	if (wzq::DC_Seted == false)
		return;
	if (nx > 15 || ny > 15) 
		return;
	if (style == false) 
	{
		dc->BitBlt(nx*29+7,ny*29+7,28,28,mask,0,0,MERGEPAINT);
		dc->BitBlt(nx*29+7,ny*29+7,28,28,chess_white,0,0,SRCAND);
	}
	else
	{
		dc->BitBlt(nx*29+7,ny*29+7,28,28,mask,0,0,MERGEPAINT);
		dc->BitBlt(nx*29+7,ny*29+7,28,28,chess_black,0,0,SRCAND);
	}
}

/*___________________________________________________________________________________________*/
void wzq::SetDc(CDC2*tchessboard,CDC2*tchess_black,CDC2*tchess_white,CDC2*tmask,CDC2*dead,CDC*dc)//设置DC
{
	wzq::mask = tmask;
	wzq::chessboard = tchessboard;
	wzq::chess_white = tchess_white;
	wzq::chess_black = tchess_black;
	wzq::dc = dc;
	wzq::dead = dead; 
	wzq::DC_Seted = true; 
}

/*___________________________________________________________________________________________*/
void wzq::NewGame()//新游戏
{
	if (wzq::DC_Seted == false)
		return;
	for(int i1 = 0; i1 < 15; i1++)
	{
		for(int i2 = 0; i2 < 15; i2++)
		{
			map[i1][i2] = 0;
			for(int i3 = 0 ; i3 <= 3; i3++)
			{
				user[i1][i2][i3]  = 255;
				pc[i1][i2][i3]  = 255;
			}
		}
	}
	for (int ix = 0; ix < 225; ix++)
	{
		wzq::wzs[ix].used = false; 
	}
	CSize x = chessboard->GetSize();
	dc->BitBlt(0,0,x.cx,x.cy,chessboard,0,0,SRCCOPY);//画棋盘
	wzq::twinner.winner = 0;			//1是白棋 2是黑棋
	wzq::nturn=0;						//0是黑棋 1是白棋
	wzq::steps =0;
	if (wzq::Model == 1)
	{
		Black_pawn(7,7);
	} 
}

/*___________________________________________________________________________________________*/
void wzq::redraw()//重画
{
	if (wzq::DC_Seted == false)
		return;
	CSize x = chessboard->GetSize() ;
	dc->BitBlt(0,0,x.cx,x.cy,chessboard,0,0,SRCCOPY);//画棋盘
	for(int i1 = 0; i1 < 15; i1++)
	{
		for(int i2 = 0 ;i2 < 15; i2++)
		{
			if (map[i1][i2] == 1)				//1是白棋
			{
				this->DrawQZ(i1,i2,false);
			}
			else
			{
				if (map[i1][i2] == 2)			//2是黑棋
				{
					this->DrawQZ(i1,i2,true);
				}
			}	
		}
	}
	if (wzq::twinner.winner != 0)
	{
		int x1=wzq::twinner.nx1, y1=wzq::twinner.ny1; 
		int xj,yj;
		if(wzq::twinner.nx2 - wzq::twinner.nx1 > 0)
		{
			xj = 1;
		}
		else
		{
			if (wzq::twinner.nx2-wzq::twinner.nx1 == 0)
			{
					xj = 0;
			}
			else
			{
					xj = -1;
			}
		}
		if (wzq::twinner.ny2 - wzq::twinner.ny1 > 0)
		{
			yj = 1;
		}
		else
		{
			if (wzq::twinner.ny2-wzq::twinner.ny1 == 0)
			{
				yj = 0;
			}
			else
			{
				yj = -1;
			}
		}
		if (wzq::twinner.winner != 0)
		{
			for (int ii = 1; ii <= 5; ii++)
			{
				dc->BitBlt(x1*29+7,y1*29+7,28,28,mask,0,0,MERGEPAINT);
				dc->BitBlt(x1*29+7,y1*29+7,28,28,dead,0,0,SRCAND);
				x1+=xj;
				y1+=yj;
			}
		}
	}
}  

/*___________________________________________________________________________________________*/
bool wzq::White_pawn(int nx,int ny)//白色下子
{
	if (wzq::DC_Seted == false)
		return false;
	if (map[nx][ny] == 0)
	{
		map[nx][ny] = 1;
		DrawQZ(nx,ny,false);
		return true;
	}
	return false;
}

/*___________________________________________________________________________________________*/
bool wzq::Black_pawn(int nx,int ny)//黑色下子
{
	if (wzq::DC_Seted == false)
		return false;
	if (map[nx][ny] == 0)
	{
		map[nx][ny] = 2;
		DrawQZ(nx,ny,true);
		return true;
	}
	return false;
}

/*__________________________________________________________________________________________*/
bool wzq::downzi(int nx,int ny)//外部调用此函数下子
{
	bool turnback;
	if (nx < 0 || nx > 14 || ny < 0 || nx > 14) 
		return false;
	if (wzq::nturn == -1)
		return false;
	if (wzq::Model == 2)
	{
		if (wzq::nturn == 0)
		{
			turnback = Black_pawn(nx,ny);
			if (bewinner(true,nx,ny) == true)
				wzq::nturn = -1; 
			wzq::nturn = turnback?1:0;
			record(nx,ny,true);
		}
		else
		{
			turnback = White_pawn(nx,ny);
			if(bewinner(false,nx,ny) == true)
				wzq::nturn = -1;
			wzq::nturn = turnback?0:1;
			record(nx,ny,false);
		}
	}
	else
	{
		if (wzq::Model == 1)
		{
			if (White_pawn(nx,ny) == false)
				return false;
			if(bewinner(false,nx,ny) == true)
				wzq::nturn = -1;
			record(nx,ny,false);
			CPoint aigo=wzq::AiGo(true);
			Black_pawn(aigo.x,aigo.y);
			record(aigo.x,aigo.y,true);
			if(bewinner(true,aigo.x,aigo.y) == true)
				wzq::nturn = -1;
		}
		else
		{
			if (wzq::Model == 0) 
			{
				if (Black_pawn(nx,ny) == false)
					return false;
				if(bewinner(true,nx,ny) == true)
					wzq::nturn =-1;
				record(nx,ny,true);
				CPoint aigo = wzq::AiGo(false);
				White_pawn(aigo.x,aigo.y);
				record(aigo.x,aigo.y,false);
				if(bewinner(false,aigo.x,aigo.y) == true)
					wzq::nturn =-1;
			}
		}
	}
	return turnback;
}

/*____________________________________________________________________________________*/
bool wzq::goback()//悔棋
{	
	if (wzq::getbackble == false) 
		return false; 
	wzq::steps--;
	if (wzq::Model == 2)
	{
		map[wzq::wzs[steps].ix][wzq::wzs[steps].iy] = 0;
		wzq::nturn = wzq::wzs[steps + 1].color;
		wzq::wzs[steps].used = false;
		wzq::dc->BitBlt(wzq::wzs[steps].ix*29+7,wzq::wzs[steps].iy*29+7,28,28,wzq::chessboard,wzq::wzs[steps].ix*29+7,wzq::wzs[steps].iy*29+7,SRCCOPY);
	}
	else
	{
		map[wzq::wzs[steps].ix][wzq::wzs[steps].iy] = 0;
		wzq::wzs[steps].used = false;
		wzq::dc->BitBlt(wzq::wzs[steps].ix*29+7,wzq::wzs[steps].iy*29+7,28,28,wzq::chessboard,wzq::wzs[steps].ix*29+7,wzq::wzs[steps].iy*29+7,SRCCOPY);
		wzq::steps--;
		map[wzq::wzs[steps].ix][wzq::wzs[steps].iy] = 0;
		wzq::wzs[steps].used = false;
		wzq::dc->BitBlt(wzq::wzs[steps].ix*29+7,wzq::wzs[steps].iy*29+7,28,28,wzq::chessboard,wzq::wzs[steps].ix*29+7,wzq::wzs[steps].iy*29+7,SRCCOPY);
	}
	if (wzq::twinner.winner != 0) 
	{
		wzq::twinner.winner = 0; 
		wzq::redraw();
	}
	return false;
}

/*__________________________________________________________________________________________*/
bool wzq::be_hand_out(int nx,int ny)
{
	/*++此处添加禁手控制++*/
		//因为不熟悉五子棋的规则，所以没有设置禁手
	return false;
}

/*__________________________________________________________________________________________*/
CPoint wzq::AiGo(bool color)
{
	CPoint turnback(-1,-1);
	clear(false);					//pc全部置为255
	fillin(color,false,true);
	fillin(!color,false,false);
	wzq::aitype2 = getAItype();
	unsigned char found = 255;
	for (int ix = 0; ix < 15; ix++)
	{
		for (int iy = 0; iy < 15; iy++)
		{
			for (int im = 0; im <= 3; im++)
			{
				if (pc[ix][iy][im] <= found)
				{
					found = pc[ix][iy][im];
					turnback.x = ix,turnback.y = iy;
				}
			}
		}
	}
	if (found <= 23)
		return turnback;
	else
		return getmax(color);
}

/*__________________________________________________________________________________________*/
void wzq::fillin(bool color,bool player,bool type)			//转换为棋谱
{
	int ix,iy;
	for (ix = 0; ix < 15; ix++)
	{
		for (iy = 0  ; iy < 15; iy++)
		{
			if (map[ix][iy] == 0)
			{
				for (int dir = 0; dir <= 3; dir++)			//direction
				{
					get_chess_manual(ix,iy,color,player,dir,type);
				}
			}
		}
	}
}

/*_____________________________________________________________________________________*/
CPoint wzq::getmax(bool color)
{
	CPoint turnback(0,0);
	setall();
	begin:
	bool x = 0;
	int fx = 0, fy = 1;
	for (int ix = 0; ix < 15; ix++)
		{
			for (int iy = 0; iy <15; iy++)
			{
				if (wzq::nicest[ix][iy] == 0)
				{
					if (get_victory2(ix,iy,fx,fy,false) == true)
						fx = ix,fy = iy,x = 1;
				}
			}	
		}
	//找最大
	if (x == 0)
	{
		for (int ix = 0; ix < 15; ix++)
		{
			for (int iy  =0; iy < 15; iy++)
			{
				if (wzq::nicest[ix][iy] != 1/*不输*/)
				{
					if (get_victory2(ix,iy,turnback.x,turnback.y,false) == true)
						turnback.x = ix,turnback.y = iy,x = 1;
				}
			}
		}
		if (x==0)
		{
			for (int ix = 0; ix <= 14; ix++)
			{
				for (int iy = 0; iy <= 14; iy++)
				{
					if (get_victory2(ix,iy,turnback.x,turnback.y,false) == true)
						turnback.x=ix,turnback.y=iy,x=1;
				}
			}
		}
		if (x==0)
			turnback.x =7,turnback.y =7;
		return turnback;
	}//找完
	for (ix = 0; ix < 15; ix++)
	{
		for (int iy = 0; iy < 15; iy++)
		{
			wzq::trygo[ix][iy] = wzq::map[ix][iy];
		}
	}
	//填
	wzq::checkgo(fx,fy, color,1,fx,fy);
	//预测
	if (nicest[fx][fy] == 2)//win
	{
		turnback.x = fx,turnback.y = fy;
		return turnback;
	}
	else
	{
		goto begin;//重来一次
	}
	//判断
}

/*__________________________________________________________________________________________*/
void wzq::get_chess_manual(int nx ,int ny,bool style,bool player,int dir,bool type)
{
	
	bool ok = true;
	int ia,ib;
	int ix,iy;
	int i2i,i2j;
	int tem1,tem2;
	int x;
	int i3;
	int m1,m3;
	int i;
	int wx = nx,wy = ny,tem3 = 0;
	switch (dir)
	{
	case 0:
		i2i = 1,i2j = 0;break;
	case 1:
		i2i = 0,i2j = 1;break;
	case 2:
		i2i = 1,i2j = 1;break;
	case 3:
		i2i = 1,i2j = -1;break;
	}
	unsigned char temp3[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char temp4[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	begin:
	if (map[wx][wy] != 0)
		return;
	i3 = 0;
	ix = i2i;
	iy = i2j;
	ia = 1,ib = 1;
	//right==========================================================================================//
		x = map[wx - ix][wy - iy];
		while(!(x != (int)style + 1 || wx - ix < 0 || wy - iy < 0))
		{
			ia++;
			ix += i2i;
			iy += i2j;
			x = map[wx-ix][wy-iy];

		} 
		ix = i2i,iy = i2j;
	//left====================================================================================//
		x = map[wx + ix][wy + iy];
		while(!(x != (int)style + 1|| wx + ix > 14 || wy+iy > 14))
		{
			ib++;
			ix += i2i;
			iy += i2j;	
			x = map[wx + ix][wy + iy];
		} 
	//偏移=======================================================================================//
		if (ib == 1 && ia == 1)
		{
			if (tem3 == 0)
			{
				wx += i2i,wy += i2j;
				tem3 = 1;
				goto begin;
			}
			else
			{
				if (tem3 == 1)
				{
					wx -= i2i * 2,wy -= i2j * 2;
					tem3 = 2;
					goto begin;
				}
				else
				{
					if (tem3 == 2)return;
				}
			}
			
		}
		ix = 0,iy = 0;
		switch (dir)
		{
			case 0:
				{
					m1 = (ia != 1 && ib == 1),m3 = (ib != 1 && ia == 1);
					for(i = 0; i < 1+ia+ib; i++)
					{
							tem1 = wx - ia + ix - m1;
							if (tem1 < 0 || tem1 > 14)
							{ ix += 1; continue; }
							x = map[tem1][wy];
							temp3[i3] = ntoc(x,type,style);
							ix += 1;
							i3++;
					}
					ix = 0,i3 = 0;
					for (i = 0; i < 1+ia+ib; i++)
					{
							tem1 = wx + ib - ix + m3;
							if (tem1 < 0 || tem1 > 14)
							{ ix += 1; continue; }
							x = map[tem1][wy];
							temp4[i3] = ntoc(x,type,style);
							ix+=1;
							i3++;
					}
					break;
				}
			case 1:
				{
					m1 = (ia != 1 && ib == 1), m3 = (ib != 1 && ia == 1);
					for(i = 0; i < 1+ia+ib; i++)
					{
							tem1 = wy-ia+iy-m1;
							if (tem1 < 0 || tem1 > 14)
							{ iy += 1; continue; }
							x = map[wx][tem1];
							temp3[i3] = ntoc(x,type,style);
							iy += 1;
							i3++;
					}
					iy = 0,i3 = 0;
					for (i = 0; i < 1+ia+ib; i++)
					{
							tem1 = wy+ib-iy+m3;
							if ( tem1 < 0 || tem1 > 14)
							{ iy += 1; continue; }
							x = map[wx][tem1];
							temp4[i3] = ntoc(x,type,style);
							iy += 1;
							i3++;
					}
					break;

				}
			break;
			case 2:
				{
					m1 = (ia != 1 && ib == 1),m3 = (ib != 1 && ia == 1);
					for (i = 0; i < 1+ia+ib; i++)
					{
						tem1 = wx-ia+ix-m1;
						tem2 = wy-ia+iy-m1;
						if (tem1 < 0 || tem1 > 14 || tem2 < 0 || tem2 > 14)
						{ ix += 1;iy += 1; continue; }
						x = map[tem1][tem2];
						temp3[i3] = ntoc(x,type,style);
						iy += 1;
						ix += 1;
						i3++;
					}
					iy = 0,ix = 0,i3 = 0;
					for (i = 0; i < 1+ia+ib; i++)
					{
						tem1 = wx+ib-ix+m3;
						tem2 = wy+ib-iy+m3;
						if (tem1 < 0 || tem1 > 14 || tem2 < 0 || tem2 > 14)
						{ ix += 1,iy += 1; continue; }
						x = map[tem1][tem2];
						temp4[i3] = ntoc(x,type,style);
						iy += 1;
						ix += 1;
						i3++;
					}
					
			break;
				}
			case 3:
				{
					m1 = (ia != 1 && ib == 1),m3 = (ib != 1 && ia == 1);
					for (i = 0; i < 1+ia+ib; i++)
					{
						tem1 = wx-ia+ix-m1;
						tem2 = wy+ia+iy+m1;
						if (tem1 < 0 || tem1 > 14 || tem2 < 0 || tem2 > 14)
						{ ix += 1; iy-=1; continue; }
						x = map[tem1][tem2];
						temp3[i3] = ntoc(x,type,style);
						iy -= 1;
						ix += 1;
						i3++;
					}
					iy = 0,ix = 0,i3 = 0;
					for (i = 0; i < 1+ia+ib; i++)
					{
						tem1 = wx+ib-ix+m3;
						tem2 = wy-ib-iy-m3;
						if (tem1 < 0 || tem1 > 14 || tem2 < 0 || tem2 > 14)
						{ ix += 1; iy += 1; continue; }
						x = map[tem1][tem2];
						temp4[i3] = ntoc(x,type,style);
						iy -= 1;
						ix += 1;
						i3++;
					}
					break;
				}
		};
	//tj===================================================//
	if ( (strcmp("00H0",(const char *)&temp3[1]) == 0 || strcmp("00H0",(const char *)&temp4[1]) == 0 || strcmp("00H0",(const char *)&temp3[0]) == 0 || strcmp("00H0",(const char *)&temp4[0]) == 0) && tem3 != 0)
		return;
	if ( (strcmp("00B0",(const char *)&temp3[1]) == 0 || strcmp("00B0",(const char *)&temp4[1]) == 0 || strcmp("00B0",(const char *)&temp3[0]) == 0 || strcmp("00B0",(const char *)&temp4[0]) == 0) && tem3 != 0)
		return;
	if ( (strcmp("00HHHB",(const char *)&temp3[1]) == 0 || strcmp("00HHHB",(const char *)&temp4[1]) == 0 || strcmp("00HHHB",(const char *)&temp3[0]) == 0 || strcmp("00HHHB",(const char *)&temp4[0]) == 0) && tem3 != 0)
		return;

	/*++此处添加更多的屏蔽++*/
	if (tem3 == 0)
	{
		for (i = 0; i <= 61; i++)
		{
			if (strcmp(wds[i],(const char *)&temp3[1]) == 0 || strcmp(wds[i],(const char *)&temp4[1]) == 0 || strcmp(wds[i],(const char *)&temp3[0]) == 0 || strcmp(wds[i],(const char *)&temp4[0]) == 0)
			{
				if (player == false)
				{
					pc[nx][ny][dir]=i;
					return;
				}	
				else
				{
					user[nx][ny][dir]=i;
					return;
				}
			}
		}
	}
	else
	{
		for (i=0 ; i<=61 ; i++)
		{
			if (strcmp(wds[i],(const char *)&temp3[0])==0||strcmp(wds[i],(const char *)&temp4[0])==0)
			{
				if (player==false)
				{
					pc[nx][ny][dir]=i;
					return;
				}	
				else
				{
					user[nx][ny][dir]=i;
					return;
				}
			}
		}
	}
}

/*__________________________________________________________________________________________*/
void wzq::setall()
{
	for (int ix = 0; ix < 15; ix++)
	{
		for (int iy = 0; iy < 15; iy++)
		{
			wzq::nicest[ix][iy] = 0; 
		}
	}
}

/*____________________________________________________________________________________*/
char wzq::ntoc(char num,bool type,bool style)
{ 
	if (num == 0)
		return '0';
	else if (type == true)
	{
		if (num == (int)style+1)
			return 'H';
		else 
			return 'B';
	}
	else
	{
		if (num!=(int)style+1)
			return 'H';
		else 
			return 'B';
	}
}

/*_____________________________________________________________________________________*/
void wzq::checkgo(int x,int y,bool color,int num,int inx,int iny)//预测函数 
{
	wzq::trygo[x][y] = (char)color + 1;
	clear(true);
	fillin(color,true,true);
	fillin(!color,true,false);
	CPoint temp = get_victory(true);
	bool four1 = false, four2 = false, three1 = false,three2 = false;
	bool four3 = false, four4 = false, three3 = false,three4 = false;
	for (int i = 0; i <= 3; i++)
	{
		if (user[temp.x][temp.y][i] >= 3 && user[temp.x][temp.y][i] <= 5)
		{
			wzq::nicest[inx][iny] = 2;//lose 
			return;
		}
		else
		{
			if (user[temp.x][temp.y][i] < 3)//win
			{
				wzq::nicest[inx][iny] = 1;
				return;
			}
			else
			{
				if (user[temp.x][temp.y][i] >= 6 && user[temp.x][temp.y][i] <= 14)
				{
					if(four1 == true)
						four2=true;
					else 
						four1=true;
				}
				else
				{
					if (user[temp.x][temp.y][i] >= 15 && user[temp.x][temp.y][i] <= 23)
					{
							if(four3==true)
								four4=true;
							else 
								four3=true;
					}
					else
					{
						if (user[temp.x][temp.y][i] == 24 || user[temp.x][temp.y][i] == 25)
						{
								if(three1==true)
									three2=true;
								else 
									three1=true;
						}
						else
						{
							if (user[temp.x][temp.y][i] == 26 || user[temp.x][temp.y][i] == 27)
							{		
								if(three3 == true)
									three4 = true;
								else
									three3 = true;
							}
						}
					}
				}
			}
		}
	}
	/*++此处添加更多的胜败判断++*/
	if (three1 + three2 + four1 + four2 >= 2)
	{
		wzq::nicest[inx][iny] = 1;//lose
		return;
	}
	else
	{
		if (three3+three4+four3+four4>=2)
		{
			wzq::nicest[inx][iny] = 2;//win
			return;
		}
	}
	if (num >= wzq::aitype2)
	{
		wzq::nicest[inx][iny] = 3;
		return;
	}
	int xxx = num + 1;
	checkgo(temp.x,temp.y,!color,xxx,inx,iny);
}

/*_____________________________________________________________________________________*/
CPoint wzq::get_victory(bool style)
{
	CPoint turnback;
	int ix1 = 0,iy1 = 0;
	for (int ix = 0; ix < 15; ix++)
	{
		for (int iy = 0; iy < 15; iy++)
		{
			if (get_victory2(ix,iy,ix1,iy1,style) == true)
			{
				ix1 = ix,iy1 = iy;
			}
		}
	}
	turnback.x = ix1;
	turnback.y = iy1;
	return turnback;
}

/*_____________________________________________________________________________________*/
bool wzq::get_victory2(int x1,int y1,int x2,int y2,bool style)
{
	unsigned char a[4];
	unsigned char b[4];
	unsigned char temp1;
	int i;
	if (style == false)
	{
		for (i=0 ; i<=3 ;i++)
		{
			a[i] = 1;
			a[i] = pc[x1][y1][i];
			b[i] = pc[x2][y2][i];
		}
	}
	else
	{
		for (i = 0; i <= 3; i++)
		{
			a[i] = 1;
			a[i] = user[x1][y1][i];
			b[i] = user[x2][y2][i];
		}

	}
	//...
	for (i = 0; i <= 3; i++)
	{
		for (int i2 = 0; i2 <= 2-i; i2++)
		{
			if (a[i2] > a[i2+1])
			{
				temp1 = a[i2];
				a[i2] = a[i2+1];
				a[i2+1] = temp1;
			}
			if (b[i2] > b[i2+1])
			{
				temp1 = b[i2];
				b[i2] = b[i2+1];
				b[i2+1] = temp1;
			}
		}
	}
	//冒泡排序
	for (i = 0; i <= 3; i++)
	{
		if (a[i] < b[i])
		{
			return true;
		}
		else
		{
			if (a[i] > b[i])
			{
				return false;
			}
		}
	}
	return false;
}

void wzq::clear(bool style)
{
	int ix,iy;
	if (style == false)
	for (ix = 0; ix < 15; ix++)
	{
		for (iy = 0; iy < 15; iy++)
		{
			for (int im = 0; im <= 3; im++)
			{
				wzq::pc[ix][iy][im] = 255; 
			}
		}
	}
	else
	{
		for (ix = 0;ix < 15; ix++)
		{
			for (iy = 0; iy< 15; iy++)
			{
				for (int im = 0; im <= 3; im++)
				{
					wzq::user[ix][iy][im] = 255; 
				}
			}
		}
	}
}

int wzq::getAItype()
{
	if (wzq::AItype == 0)
		return 6;
	else if (wzq::AItype == 1)
		return 10;
	else if (wzq::AItype == 2)
		return 20;
	else
		return 10;
}

void wzq::record(int nx,int ny,bool style)
{
	wzq::wzs[wzq::steps].used = true;
	wzq::wzs[wzq::steps].color = style;
	wzq::wzs[wzq::steps].ix = nx;
	wzq::wzs[wzq::steps].iy = ny;
	wzq::steps++; 
}

bool wzq::bewinner(bool style, int nx, int ny)
{
	int tx1 = 0,tx2 = 0,ty1 = 0,ty2 = 0;
 	int yx1 = 0,yx2 = 0,yy1 = 0,yy2 = 0;
 	int st = (int)style+1;
 	for (int x1 = -5; x1 <= 5; x1++)
	{
		if (map[nx + x1][ny] == st)//竖着
		{
 			tx1++;
 			if (tx1 == 1)	
 				yx1 = x1;
 	
 			if (tx1 >= 5)
 			{
 				twinner.winner =st;
 				twinner.nx1 = nx + yx1;
 				twinner.nx2 = nx + yx1 + 5;
 				twinner.ny1 = ny;
 				twinner.ny2 = ny;
 				return true;
 			}
 		}
 		else 
 		{
 			tx1=0;
 		}
 
 		if (map[nx][ny + x1] == st)//横着
 		{
 			ty1++;
 			if (ty1 == 1)
 				yy1 = x1;
 			if (ty1 >= 5)
 			{
 				twinner.winner = st;
 				twinner.nx1 = nx;
 				twinner.nx2 = nx;
 				twinner.ny1 = ny + yy1;
 				twinner.ny2 = ny + yy1 + 5;
 				return true;
 			}
 		}
 		else 
 		{
 			ty1 = 0;
 		}
 
 		if (map[nx + x1][ny + x1] == st)//左上到右下
 		{
 			tx2++;
 			if (tx2 == 1)	
 				yx2 = x1;
 			if (tx2>=5)
 			{
 				twinner.winner = st;
 				twinner.nx1 = nx + yx2;
 				twinner.nx2 = nx + yx2+5;
				twinner.ny1 = ny + yx2;
 				twinner.ny2 = ny + yx2 + 5;
 				return true;
 			}
		}
 		else
 		{
			tx2 = 0;
 		}
 		if (map[nx+x1][ny-x1] == st)//右上到左下
		{
 			ty2++;
			if (ty2 == 1)
 				yy2 = x1;
 			if (ty2 >= 5)
 			{
 				twinner.winner = st;
 				twinner.nx1 = nx+yy2;
 				twinner.nx2 = nx+yy2+5;
 				twinner.ny1 = ny-yy2;
 				twinner.ny2 = ny-yy2-5;
 				return true;
 			}
		}
 		else 
 		{
 			ty2 = 0;
 		}
 	}
 	return false;
}
