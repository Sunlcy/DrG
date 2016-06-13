#include "stdafx.h"
#include "Circle.h"
#include <cmath>

CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

void CCircle::Draw(CDC * pDC)
{
	//创建一个笔然后初始化
	CPen aPen;
	CreatePen(aPen);
	CPen *pOldPen{ pDC->SelectObject(&aPen) };  //选择一个笔

	//选择一个空的画笔，然后强制转化成CBrush*型
	CBrush *pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	//使用短轴和长轴相等的椭圆来绘制圆
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	//保存以前的笔和画笔
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color) :
	CElement{ start, color }
{
	//计算圆的半径
	long radius{ static_cast<long> (sqrt(
		static_cast<double>((end.x - start.x) * (end.x - start.x) +
		(end.y - start.y) * (end.y - start.y)))) };
	if (radius < 1L)
	{
		radius = 1L;	//圆的半径必须大于1
	}

	//Define left-top and right-bottom points of rectangle for MM_TEXT mode
	m_StartPoint = CPoint{ start.x - radius, start.y - radius };
	m_BottomRight = CPoint{ start.x + radius, start.y + radius };

	//Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}
