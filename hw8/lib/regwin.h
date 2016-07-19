#ifndef REGWIN_H
#define REGWIN_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include "twiteng.h"
#include <QLineEdit>
#include <string>
#include <QMetaObject>
#include <QMessageBox>
#include <iostream>

class RegWin : public QMainWindow
{
	Q_OBJECT

	public:
		RegWin(QWidget* parent = 0);
		~RegWin();

	public slots:
		//void checkInput(); 
		void quit();

	signals:

	private:	
		TwitEng* twit;

		QLabel* userLabel;
		QLabel* passLabel;


		QLineEdit* username;
		QLineEdit* password;
		

		QPushButton* btnSubmit;
		QPushButton* btnClose;

		QFormLayout* window;

};

#endif