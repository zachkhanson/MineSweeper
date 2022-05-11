#pragma once
#include "wx/wx.h"

class MainWindow : public wxFrame
{
public:
	MainWindow();
	~MainWindow();

public:
	int fieldWidth = 10;
	int fieldHeight = 10;
	wxButton** mBtn;
	int* mField = nullptr;
	bool firstClick = true;
	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

