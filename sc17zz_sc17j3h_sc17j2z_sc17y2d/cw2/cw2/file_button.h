//
// Created by twak on 11/11/2019.
//

#ifndef CW2_FILE_BUTTON_H
#define CW2_FILE_BUTTON_H


#include <QtWidgets/QPushButton>


//
// Created by twak on 11/11/2019.
//


class FileButtonInfo {

public:
	QUrl* url; // video file to play
	QIcon* icon; // icon to display

	FileButtonInfo(QUrl* url, QIcon* icon) : url(url), icon(icon) {}
};

class TheFileButton : public QPushButton {
	Q_OBJECT

public:
	FileButtonInfo* info;

	TheFileButton(QWidget *parent) : QPushButton(parent) {
		setIconSize(QSize(200, 110));
		//connect(this, SIGNAL(released()), this, SLOT(clicked())); // if QPushButton clicked...then run clicked() below
	}

	void init(FileButtonInfo* i);

/*private slots:
	void clicked();*/



};
#endif //CW2_THE_BUTTON_H

/*
class TheFileButton : public QPushButton {
	Q_OBJECT

public:
	QUrl* url; // video file to play
	QIcon* icon; // icon to display

	TheFileButton(QUrl* url, QIcon* icon) : url(url), icon(icon) {}
	

	TheFileButton(QWidget *parent) : QPushButton(parent) {

		setIconSize(QSize(200, 110));
		connect(this, SIGNAL(released()), this, SLOT(clicked())); // if QPushButton clicked...then run clicked() below
	}
	void init();
private slots:
	void clicked();
};


*/