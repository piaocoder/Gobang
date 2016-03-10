// CDC2.h: interface for the CDC2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDC2_H__5BACBA48_AA67_41EB_AD17_70C81F0B8FC1__INCLUDED_)
#define AFX_CDC2_H__5BACBA48_AA67_41EB_AD17_70C81F0B8FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//CDC类是用来管理设备的，画图基本上都用这个类完成的
class CDC2 : public CDC  
{
public:
	CDC2();
	virtual ~CDC2();
	CSize GetSize();
	void SetSize(CSize size);
	CSize msize;
};
#endif // !defined(AFX_CDC2_H__5BACBA48_AA67_41EB_AD17_70C81F0B8FC1__INCLUDED_)
