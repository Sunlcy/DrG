#include "stdafx.h"
#include "Ellipse.h"

IMPLEMENT_SERIAL(CEllipse, CElement, VERSION_NUMBER)
CEllipse::CEllipse()
{
}


CEllipse::~CEllipse()
{
}

void CEllipse::Draw(CDC * pDC, std::shared_ptr<CElement> pElement)
{
	//创建一个画笔并初始化
	CPen aPen;
	CreatePen(aPen, pElement);
	CBrush aBrush;
	CreateBrush(aBrush, pElement);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	CBrush* pOldBrush;
	//如果按下填充按钮则选择实心画刷，否则选择空画刷
	if (Filler)
	{
		pOldBrush = pDC->SelectObject(&aBrush);
	}
	else
	{
		pOldBrush = dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));
	}

	//画圆
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y,
		m_BottomRight.x, m_BottomRight.y);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void CEllipse::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_BottomRight += aSize;
	m_EnclosingRect += aSize;
}

CEllipse::CEllipse(const CPoint & center, const CPoint & end, COLORREF color, int PenWidth) :
	CElement{ center, color, PenWidth }
{
	//创建包围椭圆的矩形
	int halfWidth{ abs(center.x - end.x) };		//得到矩形的宽的一半
	int halfHeight{ abs(center.y - end.y) };	//得到矩形的高的一半

	m_StartPoint = m_BottomRight = center;
	m_StartPoint.Offset(-halfWidth, -halfHeight);
	m_BottomRight.Offset(halfWidth, halfHeight);

	//大小至少为2
	if (m_StartPoint.x - m_BottomRight.x < 2)
	{
		m_BottomRight.x += 2;
	}
	if (m_StartPoint.y - m_BottomRight.y < 2)
	{
		m_BottomRight.y += 2;
	}
	int width = { PenWidth == 0 ? 1 : PenWidth };
	//定义边界矩形
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(width, width);
}


void CEllipse::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);
	if (ar.IsStoring())
	{	// storing code
		ar << m_BottomRight;
	}
	else
	{	// loading code
		ar >> m_BottomRight;
	}
}
