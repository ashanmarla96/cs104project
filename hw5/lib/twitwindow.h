#ifndef TWITWINDOW_H
#define TWITWINDOW_H
#include "twiteng.h"
#include <QLabel>
#include <QString>
#include <QListWidget>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class TwitWindow : public QWidget
{
	Q_OBJECT

public: 
	TwitWindow(TwitEng* parsed_file);
	~TwitWindow();

private slots:
	//void SearchWindow();
	void SaveFeeds();
	void doneClicked();
	void popClicked();
	void quit();
	void refreshfollowing(QString);
	void refreshmain(QString);
	void refreshmen(QString);
	void searchand();
	void searchor();
	void tweetadd();

private:
	TwitEng* twit;
	std::map<std::string, User*> users_;

	QWidget *searchWin;
	QVBoxLayout *window;

	QLineEdit *tweettext;

	QListWidget *currdisp;

	QListWidget *maindisp;

	QListWidget *mendisp;

	QListWidget *termdisp;
	QLineEdit *term;

};
#endif
