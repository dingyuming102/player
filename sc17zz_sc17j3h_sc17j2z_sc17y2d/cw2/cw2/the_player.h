//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>
#include <Qslider>
#include <QMouseEvent>
#include <QCoreApplication>

using namespace std;
class qSlider : public QSlider

{

	Q_OBJECT

public:

	qSlider(QWidget* parent = 0) : QSlider(parent) {};
signals:
	void mmSliderClicked();

protected:

	void mousePressEvent(QMouseEvent* ev);



};

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
    }
	qSlider *slider;
    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

	bool m_bReLoad;
private slots:


    void playStateChanged (QMediaPlayer::State ms);

public slots:
	void barchange();
	void progressclicked();
	void progressmoved();
	void getslider(qSlider *slider);
	void OnSetMediaFile();
    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
	void setLineEditValue(int i);
};

#endif //CW2_THE_PLAYER_H
