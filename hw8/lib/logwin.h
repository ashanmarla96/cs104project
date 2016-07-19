#ifndef LOGWIN_H
#define LOGWIN_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QFormLayout>
#include <map>
#include "twiteng.h"
#include "twitwindow.h"

class LogWin : public QMainWindow
{
	Q_OBJECT

	public:
		LogWin(std::string input, std::string adfile, std::string billfile, QWidget* parent = 0);
		~LogWin();

	private slots:
		void create();	
		void write(std::string userIn, std::string passIn);
		void checkInfo();
		void openMainWin();

	signals:
		void success();

	
	private:
		TwitEng* twit;

		QLabel* topdisplay; 

		QLineEdit* username; 
		QLineEdit* password;

		QLabel* userLabel;
		QLabel* passLabel;

		QPushButton* btnQuit; 
		QPushButton* btnSubmit; 
		QPushButton* btnCreate;

		std::map<std::string, std::string>* accounts;

		QFormLayout* winLayout;
		QWidget* centerWidget;
		MainWin* tempWindow;

		std::string _input;
		std::string _adfile;
		std::string _billfile;
		bool MainWinOpened;
};

#endif