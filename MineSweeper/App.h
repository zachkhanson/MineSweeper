#pragma once
#include "wx/wx.h"
#include "MainWindow.h"

class App : public wxApp
{
public:
	App();
	~App();
	virtual bool OnInit();
private:
	MainWindow* mainWindow = nullptr;
};

