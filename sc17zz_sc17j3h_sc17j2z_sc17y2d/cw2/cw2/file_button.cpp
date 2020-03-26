//
// Created by twak on 11/11/2019.
//

#include "file_button.h"


void TheFileButton::init(FileButtonInfo* i) {
	setIcon(*(i->icon));
	info = i;
}


