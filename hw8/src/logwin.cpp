#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <QApplication>
#include "../lib/logwin.h"
#include "regwin.h"
using namespace std;

LogWin::LogWin(TwitEng* parsedFile, QWidget* parent) : QMainWindow(parent)
{
	MainWinOpened = false;
	twit = parsedFile;
	
	setWindowTitle(QString::fromStdString("Login!"));	
	
	//declare labels
	userLabel = new QLabel(QString::fromStdString("Username:"));
	passLabel = new QLabel(QString::fromStdString("Password:"));
	
	//declare buttons
	btnSubmit = new QPushButton("&Submit");
	btnQuit = new QPushButton("&Quit");
	btnCreate = new QPushButton("&Create Account");
	
	//declare line text boxes
	username = new QLineEdit();
	password = new QLineEdit();
	winLayout = new QFormLayout;
	
	//create the layout
	winLayout -> addRow(userLabel, username);
	winLayout -> addRow(passLabel, password);
	winLayout -> addRow(btnSubmit, btnQuit);
	winLayout -> addRow(btnCreate);

	/*centerWidget = new QWidget(this);
	centerWidget -> setLayout(winLayout);
	this -> setCentralWidget(centerWidget);*/
	
	//connections
	connect(btnQuit, SIGNAL(clicked()), qApp, SLOT(quit())); 
	//connect(btnCreate, SIGNAL(clicked()), this, SLOT(create())); 
	//connect(btnSubmit, SIGNAL(clicked()), this, SLOT(checkInfo()));
	
	//connect(this, SIGNAL(success()), this, SLOT(openMainWin()));
}

LogWin::~LogWin() {
	if (MainWinOpened == true){
		delete tempWindow;
	}
}





void LogWin::openMainWin(){
	tempWindow = new MainWin(_input, _adfile, _billfile, username->text().toStdString(), 0);
	MainWinOpened = true;

	tempWindow -> show();
}