#include "../lib/twitwindow.h"
#include <sstream>
#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
using namespace std;


TwitWindow::TwitWindow(TwitEng* parsedFile) : QWidget(NULL)
{
	twit = parsedFile;

	setWindowTitle("Twitter");
	window = new QVBoxLayout();
	

	users_ = twit->getUsers();

	
	//search popup window
	searchWin = new QWidget;
	QVBoxLayout *searchlay = new QVBoxLayout();
	QLabel *instruct1 = new QLabel("=====================================");
	QLabel *instruct2 = new QLabel("Menu: ");
	QLabel *instruct3 = new QLabel("  AND term term ...                  ");
	QLabel *instruct4 = new QLabel("  OR term term ...                   ");
	QLabel *instruct5 = new QLabel("=====================================");
	searchlay->addWidget(instruct1);
	searchlay->addWidget(instruct2);
	searchlay->addWidget(instruct3);
	searchlay->addWidget(instruct4);
	searchlay->addWidget(instruct5);

	QHBoxLayout *buttonsrad = new QHBoxLayout();
	QVBoxLayout *buttonsrad1 = new QVBoxLayout();
	QVBoxLayout *buttonsrad2 = new QVBoxLayout();
	andbutt = new QRadioButton("AND");

	orbutt = new QRadioButton("OR");
	buttonsrad1->addWidget(andbutt);
	buttonsrad1->addWidget(orbutt);
	QLabel *termlabel = new QLabel("Enter term(s):");
	
	term = new QLineEdit();
	//string text_ = term->text().toStdString();
	//cout << text_;

	buttonsrad2->addWidget(termlabel);
	buttonsrad2->addWidget(term);
	buttonsrad->addLayout(buttonsrad2);
	buttonsrad->addLayout(buttonsrad1);
	searchlay->addLayout(buttonsrad);

	QPushButton *termsearch = new QPushButton("&Search");
	searchlay->addWidget(termsearch);

	termdisp = new QListWidget();
	termdisp->addItem(QString::fromStdString("No Matches"));
	searchlay->addWidget(termdisp);

	QObject::connect(termsearch, SIGNAL(pressed()), this, SLOT(search()));
	//QObject::connect(orbutt, SIGNAL(pressed()), this, SLOT(searchor()));

	QPushButton *otherButton = new QPushButton("&Done");
	searchlay->addWidget(otherButton);
	searchWin->setLayout(searchlay);
	QObject::connect(otherButton, SIGNAL(clicked()), this, SLOT(doneClicked()));



	//user select
	QHBoxLayout *setUserLay = new QHBoxLayout();
	QLabel *userSel = new QLabel("Select User:");
	usrdropdwn = new QComboBox();
	map<string, User*>::iterator userit;
	for(userit = users_.begin(); userit != users_.end(); ++userit){
		usrdropdwn->addItem(QString::fromStdString(userit->first));
	}
	setUserLay->addWidget(userSel);
	setUserLay->addWidget(usrdropdwn);
	window->addLayout(setUserLay);

	QLabel *instruct6 = new QLabel(" ");
	window->addWidget(instruct6);

	//following boxes
	QHBoxLayout *followingstuff = new QHBoxLayout();
	
	QVBoxLayout *currfollow = new QVBoxLayout();
	QLabel *currlabel = new QLabel("Currently Following");
	currdisp = new QListWidget();

	User* firstUser = (users_.begin()->second);
	set<User*> tempFollowing = firstUser->following();
	set<User*>::iterator myit;
	for(myit = tempFollowing.begin(); myit != tempFollowing.end(); ++myit){
		currdisp->addItem(QString::fromStdString((*myit)->name()));
	}
	QObject::connect(usrdropdwn, SIGNAL(currentIndexChanged(QString)), this, SLOT(refreshfollowing(QString)));

	currfollow->addWidget(currlabel);
	currfollow->addWidget(currdisp);

	QVBoxLayout *addfollow = new QVBoxLayout();
	QLabel *addlable = new QLabel("Follow User:");
	addbox = new QLineEdit();
	QPushButton *addusr = new QPushButton("&Follow");
	addfollow->addWidget(addlable);
	addfollow->addWidget(addbox);
	addfollow->addWidget(addusr);

	followingstuff->addLayout(currfollow);
	followingstuff->addLayout(addfollow);
	QObject::connect(addusr, SIGNAL(clicked()), this, SLOT(followuser()));
	window->addLayout(followingstuff);

	QLabel *instruct7 = new QLabel(" ");
	window->addWidget(instruct7);


	//add tweet
	QHBoxLayout *addTweet = new QHBoxLayout();
	QLabel *addlabel = new QLabel("Add Tweet");
	tweettext = new QLineEdit();
	QPushButton *tweetgo = new QPushButton("&Post");
	QObject::connect(tweetgo, SIGNAL(clicked()), this, SLOT(tweetadd()));
	addTweet->addWidget(addlabel);
	addTweet->addWidget(tweettext);
	addTweet->addWidget(tweetgo);
	window->addLayout(addTweet);

	QLabel *instruct8 = new QLabel(" ");
	window->addWidget(instruct8);

	//feeds
	QHBoxLayout *feeds = new QHBoxLayout();

	QVBoxLayout *mainfeed = new QVBoxLayout();
	QLabel *mainlabel = new QLabel("User Feed:");
	maindisp = new QListWidget();
	mainfeed->addWidget(mainlabel);
	mainfeed->addWidget(maindisp);

	User* firstUser_ = (users_.begin()->second);
	vector<Tweet*> tempTweet = firstUser_->getFeed();
	stringstream ss;
	//vector<Tweet*>::iterator myit2;
	for(unsigned int i=0; i<tempTweet.size(); ++i){
		ss << (*tempTweet[i]);
		maindisp->addItem(QString::fromStdString(ss.str()));
	}
	QObject::connect(usrdropdwn, SIGNAL(currentIndexChanged(QString)), this, SLOT(refreshmain(QString)));

	QVBoxLayout *menfeed = new QVBoxLayout();
	QLabel *menlabel = new QLabel("Mention Feed:");
	mendisp = new QListWidget();
	menfeed->addWidget(menlabel);
	menfeed->addWidget(mendisp);

	User* firstUsr_ = (users_.begin()->second);
	vector<Tweet*> tempTweet_ = firstUsr_->getMenFeed();
	stringstream ss2;
	for(unsigned int i=0; i<tempTweet_.size(); ++i){
		ss2 << (*tempTweet[i]);
		mendisp->addItem(QString::fromStdString(ss2.str()));
	}
	QObject::connect(usrdropdwn, SIGNAL(currentIndexChanged(QString)), this, SLOT(refreshmen(QString)));

	feeds->addLayout(mainfeed);
	feeds->addLayout(menfeed);
	window->addLayout(feeds);


	//popup button
	QVBoxLayout *searchpoplay = new QVBoxLayout();
	QPushButton *popButton = new QPushButton("&Search Hashtags");
	searchpoplay->addWidget(popButton);
	window->addLayout(searchpoplay);
	QObject::connect(popButton, SIGNAL(clicked()), this, SLOT(popClicked()));

	//final buttons
	QHBoxLayout *finals = new QHBoxLayout();
	QPushButton *savebutt = new QPushButton("Save");
	QPushButton *quitbutt = new QPushButton("&Quit");
	finals->addWidget(savebutt);
	finals->addWidget(quitbutt);
	window->addLayout(finals);
	QObject::connect(savebutt, SIGNAL(clicked()), this, SLOT(SaveFeeds()));
	QObject::connect(quitbutt, SIGNAL(clicked()), this, SLOT(quit()));



	setLayout(window);
}

TwitWindow::~TwitWindow()
{}

void TwitWindow::doneClicked()
{
	searchWin->hide();
}

void TwitWindow::popClicked()
{
	searchWin->show();
}

void TwitWindow::quit() {
	QApplication::exit();
}

void TwitWindow::refreshfollowing(QString qtemp)
{
	currdisp->clear();
	string temp = qtemp.toStdString();
	//users_ = twit->getUsers();

	User* firstUser = ((users_.find(temp))->second);
	set<User*> tempFollowing = firstUser->following();
	set<User*>::iterator myit;
	for(myit = tempFollowing.begin(); myit != tempFollowing.end(); ++myit){
		currdisp->addItem(QString::fromStdString((*myit)->name()));
	}
}

void TwitWindow::refreshmain(QString qtemp)
{
	maindisp->clear();
	string temp = qtemp.toStdString();
	//users_ = twit->getUsers();

	User* firstUser_ = (users_.find(temp)->second);
	vector<Tweet*> tempTweet = firstUser_->getFeed();
	stringstream ss;
	//vector<Tweet*>::iterator myit2;
	for(unsigned int i=0; i<tempTweet.size(); ++i){
		ss << (*tempTweet[i]) << endl;
		maindisp->addItem(QString::fromStdString(ss.str()));
	}
}

void TwitWindow::refreshmen(QString qtemp)
{
	mendisp->clear();
	string temp = qtemp.toStdString();
	//users_ = twit->getUsers();

	User* firstUser_ = (users_.find(temp)->second);
	vector<Tweet*> tempTweet = firstUser_->getMenFeed();
	stringstream ss2;
	//vector<Tweet*>::iterator myit2;
	for(unsigned int i=0; i<tempTweet.size(); ++i){
		ss2 << (*tempTweet[i]) << endl;
		mendisp->addItem(QString::fromStdString(ss2.str()));
	}
}

void TwitWindow::search()
{
	termdisp->clear();
	if (term->text().isEmpty() || (!orbutt->isChecked() && !andbutt->isChecked())){
		return;
	}

	stringstream ss1(term->text().toStdString());
  	string terma;
 	vector<string> terms_;
 	vector<Tweet*> result;
 	 while (ss1 >> terma){
   		//terma = convToLower(terma);
    	terms_.push_back(terma);
  	}

  	term->setText("");
  	if(andbutt->isChecked()){
  		result = twit->search(terms_, 0);
  	}
  	else if(orbutt->isChecked()){
  		result = twit->search(terms_, 1);
  	}
	

	if(!result.empty()){
		stringstream sstxt_;
	  	for(unsigned int i =0; i< result.size(); i++){
	    	//cout << *result[i] << endl;
	    	sstxt_ << (*result[i]) << endl;
	    	termdisp->addItem(QString::fromStdString(sstxt_.str()));
	  	}
	}
	else{
	  //cout << "No Matches." << endl;
		termdisp->addItem(QString::fromStdString("No Matches"));
	}
	
}

void TwitWindow::SaveFeeds()
{
	twit->dumpFeeds();
}

void TwitWindow::tweetadd()
{
	if(tweettext->text().isEmpty()){
		return;
	}


	stringstream ss2(tweettext->text().toStdString());

	  time_t rawtime;
	  struct tm * timeinfo;
	  time (&rawtime);
	  timeinfo = localtime(&rawtime);

	string name;
	ss2 >> name;


	string twxt;
	string txt = "";
	while(ss2 >> twxt){
		txt = txt + " " + twxt;
	}

	tweettext->setText("");

	DateTime* dt = new DateTime(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,timeinfo->tm_year + 1900, timeinfo->tm_mon,  timeinfo->tm_mday);
	twit->addTweet(name, *dt, txt);
}

void TwitWindow::followuser()
{
	if(addbox->text().isEmpty()){
		return;
	}

	User* tempusr;

	string usr_ = addbox->text().toStdString();
	map<string, User*>::iterator useit = users_.find(usr_);
	if(useit != users_.end()){
		tempusr = useit->second;
	}
	else{
		tempusr = new User(usr_);
		users_.insert(make_pair(usr_, tempusr));
	}

	string currusr = usrdropdwn->currentText().toStdString();
	map<string, User*>::iterator mapit = users_.find(currusr);
	(mapit->second)->addFollowing(tempusr);
	refreshfollowing(QString::fromStdString(currusr));
	

}
