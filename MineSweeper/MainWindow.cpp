#include "MainWindow.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
wxEND_EVENT_TABLE()
MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Mine Sweeper", wxPoint(30, 30), wxSize(800, 600)) {

	mBtn = new wxButton * [fieldWidth * fieldHeight];
	wxGridSizer* grid = new wxGridSizer(fieldWidth, fieldHeight, 0, 0);

	mField = new int[fieldWidth * fieldHeight];

	for (int x = 0; x < fieldWidth; x++) {
		for (int y = 0; y < fieldHeight; y++) {
			mBtn[y * fieldWidth + x] = new wxButton(this, 10000 + (y * fieldWidth + x));
			grid->Add(mBtn[y * fieldWidth + x], 1, wxEXPAND | wxALL);

			mBtn[y*fieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &MainWindow::OnButtonClicked, this);
			mField[y * fieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}


MainWindow::~MainWindow() {
	delete[]mBtn;
}

void MainWindow::OnButtonClicked(wxCommandEvent& evt) {
	
	//Get Coordinate of button
	int x = (evt.GetId() - 10000 % fieldWidth);
	int y = (evt.GetId() - 10000 / fieldWidth);

	if (firstClick) {
		int mines = 30;

		while (mines) {
			int rx = rand() % fieldWidth;
			int ry = rand() % fieldHeight;

			if (mField[ry * fieldWidth + rx] == 0 && rx != x && ry != y) {
				mField[ry * fieldWidth + rx] = -1;
				mines--;
			}
		}
		firstClick = false;
	}

	//Disables Button From Being Pressed Again
	mBtn[y * fieldWidth + x]->Enable(false);

	//Check If Player Hit a Mine
	if (mField[y * fieldWidth + x] == -1) {
		wxMessageBox("BOOOOOOM!! - GAME OVER");

		//Reset Game
		firstClick = true;
		for (int x = 0; x < fieldWidth; x++) {
			for (int y = 0; y < fieldHeight; y++) {
				mField[y * fieldWidth + x] = 0;
				mBtn[y * fieldWidth + x]->SetLabel("");
				mBtn[y * fieldWidth + x]->Enable(true);
			}
		}
	}
	else {

		//Counting Neighboring Mines
		int mineCount = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (x + i >= 0 && x + i < fieldWidth && y + j >= 0 && y + j < fieldHeight) {
					if (mField[(y + j) * fieldWidth + (x + i)] == -1) {
						mineCount++;
					}
				}
			}
		}

		//Update Buttons Label To Show Mine Count if > 0 
		if (mineCount > 0) {
			mBtn[y * fieldWidth + x]->SetLabel(std::to_string(mineCount));
		}
	}
	evt.Skip();
}

