/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for no reason
 *
 * 2811 cw2 November 2019 by twak
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QImageReader>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include<qslider.h>
#include<file_button.h>


using namespace std;






vector<FileButtonInfo>* getFileInfoIn(string loc) {

	vector<FileButtonInfo> *out = new vector<FileButtonInfo>();
	QDirIterator it(QString::fromStdString(loc), QDir::Files);

	while (it.hasNext()) { // for all files

		QString f = it.next();
		if (!f.contains(".png")) { // if it isn't an image
			QString thumb = f.left(f.length() - 4) + ".png";
			if (QFile(thumb).exists()) { // but a png thumbnail exists
				QImageReader *imageReader = new QImageReader(thumb);
				QImage sprite = imageReader->read(); // read the thumbnail
				if (!sprite.isNull()) {
					QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
					QUrl* url = new QUrl(QUrl::fromLocalFile(f));
					out->push_back(FileButtonInfo(url, ico)); // add to the output list
				}
				else
					qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb;
			}
			else
				qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb;
		}
	}

	return out;//a set of button info
}




// read in videos and thumbnails to this directory
vector<TheButtonInfo>* getInfoIn (string loc) {

    vector<TheButtonInfo> *out = new vector<TheButtonInfo>();
    QDirIterator it(QString::fromStdString(loc), QDir::Files);

    while (it.hasNext()) { // for all files

		QString f = it.next();

        if (!f.contains(".png")) { // if it isn't an image
            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // but a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
					if (!sprite.isNull()) {
						QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
						QUrl* url = new QUrl(QUrl::fromLocalFile(f)); // convert the file location to a generic url
						out->push_back(TheButtonInfo(url, ico)); // add to the output list
					}
					else
						qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb ;
            }
            else
				qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb;
        }
    }

    return out;
}

QVideoWidget *video() {
	QVideoWidget* videoWidget = new QVideoWidget;
	//videoWidget->setFixedSize(800, 400);
	return videoWidget;
}

QWidget *getUrl(string url) {
	vector<TheButtonInfo>* videos = getInfoIn(url);
	if (videos->size() == 0) {
		qDebug() << "no videos found";
		exit(-1);
	}
	//定义区块
	QWidget *buttonWidget = new QWidget();
	vector<TheButton*> *buttons=new vector<TheButton*>;

	QHBoxLayout *file = new QHBoxLayout();
	QScrollArea* fileArea = new QScrollArea();

	QVBoxLayout *layout = new QVBoxLayout();
	QVBoxLayout *videoWW = new QVBoxLayout();
	QHBoxLayout *ALL = new QHBoxLayout();
	QHBoxLayout *BUTTON = new QHBoxLayout();
	QScrollArea* scrollArea = new QScrollArea();
	QScrollArea* scrollAreaTwo = new QScrollArea();
	QWidget* scrollContents = new QWidget();
	QWidget* scrollContentsBT = new QWidget();
	ThePlayer *player = new ThePlayer;
	QVideoWidget *videoWidget = video();
	//定义按钮
	QPushButton* play = new QPushButton("Play");
	QPushButton* stop = new QPushButton("Stop");
	QPushButton* pause = new QPushButton("Pause");
	QPushButton* load = new QPushButton("Load");
	QSlider* slider = new QSlider(Qt::Horizontal);
	qSlider *Slider = new qSlider();
	QTimer *timer = new QTimer();
	//声音进度条
	slider->setMinimum(0);
	slider->setMaximum(100);
	slider->setValue(0);
	//按钮和进度条信号
	QObject::connect(play, SIGNAL(clicked()), player, SLOT(play()));
	QObject::connect(pause, SIGNAL(clicked()), player, SLOT(pause()));
	QObject::connect(stop, SIGNAL(clicked()), player, SLOT(stop()));
	QObject::connect(load, SIGNAL(clicked()),player, SLOT(OnSetMediaFile()));
	QObject::connect(slider, SIGNAL(valueChanged(int)), player, SLOT(setLineEditValue(int)));
	Slider->connect(timer, SIGNAL(timeout()), player, SLOT(barchange()));
	player->setVideoOutput(videoWidget);
	//button
	for (int i = 0; i < videos->size(); i++) {
		TheButton *button = new TheButton(buttonWidget);
		button->connect(button, SIGNAL(jumpTo(TheButtonInfo*)), player, SLOT(jumpTo(TheButtonInfo*)));
		buttons->push_back(button);
		layout->addWidget(button);
		button->init(&videos->at(i));
	}
	//folder
	for (int i = 0; i < videos->size(); i++) {

		QPushButton* btn = new QPushButton(QIcon::fromTheme("folder", QIcon("./Resources/video/a.png")), "Folder");
		btn->setFixedSize(200, 90);
		btn->setGeometry(i * 200, 0, 180, 90);
		file->addWidget(btn);
	}
	//add everything to scrollarea
	QWidget* X = new QWidget;
	X->setLayout(file);
	fileArea->setWidget(X);

	player->getslider(Slider);
	Slider->setGeometry(70, 20, 600, 20);
	
	Slider->setOrientation(Qt::Horizontal);
	Slider->connect(Slider, SIGNAL(mmSliderClicked()), player, SLOT(progressclicked()));
	Slider->connect(Slider, SIGNAL(sliderMoved(int)), player, SLOT(progressmoved()));
	timer->start();
	timer->setInterval(100);


	player->setContent(buttons, videos);
	videoWW->addWidget(videoWidget);
	BUTTON->addWidget(play);
	BUTTON->addWidget(pause);
	BUTTON->addWidget(stop);
	BUTTON->addWidget(load);
	BUTTON->addWidget(slider);
	scrollContentsBT->setLayout(BUTTON);
	videoWW->addWidget(Slider);
	videoWW->addWidget(scrollContentsBT);
	scrollContents->setLayout(layout);
	scrollArea->setWidget(scrollContents);


	ALL->addLayout(videoWW,800);
	ALL->addWidget(scrollArea,200);
	scrollAreaTwo->setLayout(ALL);
	QVBoxLayout* containAll = new QVBoxLayout();
	containAll->addWidget(scrollAreaTwo,650);
	containAll->addWidget(fileArea,150);
	QWidget* out = new QWidget;
	out->setLayout(containAll);

	return out;
}





int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
	qDebug() << "Qt version: " << QT_VERSION_STR;

    // create the Qt Application
    QApplication app(argc, argv);
    // create the main window and layout
    QWidget window;
    QGridLayout *top = new QGridLayout();
    window.setLayout(top);
    window.setWindowTitle("tomeo");
	string url = ".\\Resources\\video";
    // add the video and the buttons to the top level widget

    top->addWidget(getUrl(url));
	window.setFixedSize(1444, 968);
	window.setGeometry(230,30, 1444, 918);


    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
