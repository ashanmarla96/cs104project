#include <iostream>
#include <sstream>
#include <string>
//#include <stdlib>
#include <ctime>
#include "lib/user.h"
#include "lib/tweet.h"
#include "lib/twitwindow.h"
#include "lib/twiteng.h"
#include "lib/datetime.h"
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc < 2){
    	cerr << "Please provide the twitter data file" << endl;
    	return 1;
  	}
  	
  	TwitEng twit;

  if( twit.parse(argv[1]) ){
    cerr << "Unable to parse " << argv[1] << endl;
    return 1;
  }


  // cout << "here" << endl;

	QApplication app(argc, argv);

  TwitWindow win(&twit);
  win.show();

	return app.exec();
}