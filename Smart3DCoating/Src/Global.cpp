//===================================================================================================
// Summary:
//		SmartDoctor内部使用的公共函数
// Date:
//		2010-12-08
// Author:
//		YangXuefeng(yxf4640084@sina.com.cn)
//===================================================================================================

#include "stdafx.h"
#include "Global.h"

//===================================================================================================

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//===================================================================================================

// 启动是是否自动连接服务器
BOOL g_bAutoConServer = FALSE;

//===================================================================================================

// 从注册表中读取选项信息
BOOL ReadOptionInfo()
{
	BOOL bResult = TRUE;

	CBpRegKey rk;
	CString strPath = APABI_USERINFO_KEYROOT;
	strPath += REGISTRY_KEY_OPTION;
	if (rk.Open(HKEY_CURRENT_USER, strPath) == ERROR_SUCCESS)
	{
		// 自动连接服务器
		rk.Read(REGISTRY_KEY_CONSERVER, g_bAutoConServer);
		rk.Close();
	}
	else
		bResult = FALSE;

	return bResult;
}

// 将选项信息写入注册表中
BOOL WriteOptionInfo()
{
	BOOL bResult = TRUE;

	CBpRegKey rk;
	CString strPath = APABI_USERINFO_KEYROOT;
	strPath += REGISTRY_KEY_OPTION;
	if (rk.Open(HKEY_CURRENT_USER, strPath) == ERROR_SUCCESS)
	{
		// 自动连接服务器
		rk.Write(REGISTRY_KEY_CONSERVER, g_bAutoConServer);

		rk.Close();
	}
	else
		bResult = FALSE;

	return bResult;
}

// 在Log图上显示内部版本号
void DisplayBuildVersionText(CDC* pDC, CPoint ptPos)
{
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT)); 
	lf.lfHeight = 12;    
	lstrcpy(lf.lfFaceName, _T("宋体"));

	font.CreateFontIndirect(&lf);

	CFont *pOldFont = pDC->SelectObject(&font);

	CString strVersionNum = _T("1.0.0.1002");
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));

	CString strText	= L"产品版本: ";
	strText += strVersionNum;
	pDC->TextOut(ptPos.x, ptPos.y, strText);

	if (!GetUserName().IsEmpty())
	{
		strText = L"授权用户：";
		strText += GetUserName();

		ptPos.y += 18;
		pDC->TextOut(ptPos.x, ptPos.y, strText);
	}

	if (!GetCopyRight().IsEmpty())
	{
		strText = L"版权所有：";
		strText += GetCopyRight();

		ptPos.y += 18;
		pDC->TextOut(ptPos.x, ptPos.y, strText);
	}

	pDC->SelectObject(pOldFont);

	font.DeleteObject();
}
