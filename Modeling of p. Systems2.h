
// Modeling of p. Systems2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CModelingofpSystems2App:
// Сведения о реализации этого класса: Modeling of p. Systems2.cpp
//

class CModelingofpSystems2App : public CWinApp
{
public:
	CModelingofpSystems2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CModelingofpSystems2App theApp;
