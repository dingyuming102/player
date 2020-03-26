//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include <QFileDialog>

QTimer * timer;
int maxValue = 1000;
// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i){
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            pause(); // starting playing again
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    pause();
}
//load button
void ThePlayer::OnSetMediaFile(void)
{
	QFileDialog dialog;
	dialog.setFileMode(QFileDialog::AnyFile);
	QStringList fileNames;
	ThePlayer *player = new ThePlayer;
	if (dialog.exec())
		fileNames = dialog.selectedFiles();

	if (!fileNames.empty())
	{
		player->setMedia(QUrl::fromLocalFile(fileNames[0]));
	}
}
//volumn
void ThePlayer::setLineEditValue(int value) {
	setVolume(value);

}

void  ThePlayer::barchange()//ÿ��������仯�¼�
{
	if (this->duration() != 0)
		slider->setValue(this->position() * 100 / this->duration());

}
void ThePlayer::progressclicked()//�������ᴥ���Ĳۺ���
{

	this->setPosition(slider->value() * this->duration() / 100);
	this->play();
}
void ThePlayer::progressmoved()//qslider���϶��󴥷��Ĳۺ���
{

}
void ThePlayer::getslider(qSlider *slider) {
	this->slider = slider;
}

void qSlider::mousePressEvent(QMouseEvent* event)
{
	QSlider::mousePressEvent(event);

	double mousepos = event->pos().x() / (double)width();

	setValue(mousepos * (maximum() - minimum()) + minimum());
	emit mmSliderClicked();//�����Զ����ź�
}