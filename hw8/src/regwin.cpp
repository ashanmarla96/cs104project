#include "regwin.h"
#include <QApplication>
using namespace std;

RegWin::RegWin(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle(QString::fromStdString("Create an Account!"));
	
	//declare labels
	userLabel = new QLabel(QString::fromStdString("Enter a username:"));
	passLabel = new QLabel(QString::fromStdString("Enter a password:"));
	
	//declare buttons
	btnClose = new QPushButton("&Close");
	btnSubmit = new QPushButton("&Submit");
	
	//declare text boxes
	username = new QLineEdit();
	password = new QLineEdit();


	window = new QFormLayout;
	
	//create layout
	window->addRow(userLabel, username);
	window->addRow(passLabel, password);
	window->addRow(btnSubmit, btnClose);

	connect(btnClose, SIGNAL(clicked()), this, SLOT(quit()));
	//connect(btnSubmit, SIGNAL(clicked()), this, SLOT(checkInput()));
}

RegWin::~RegWin() {}


void RegWin::quit()
{
	this->close();
}