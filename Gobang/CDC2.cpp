// CDC2.cpp: implementation of the CDC2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Gobang.h"
#include "CDC2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDC2::CDC2()
{
	this->msize.cx = 0 ;
	this->msize.cy = 0 ;
}

CDC2::~CDC2()
{

}

CSize CDC2::GetSize()
{
	return (this->msize); 	
}

void CDC2::SetSize(CSize size)
{	
	this->msize.cx =size.cx ;
	this->msize.cy =size.cy;
}
