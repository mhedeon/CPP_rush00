//
// Created by Nickolay PIATIKOP on 2019-06-29.
//

#include "Colors.hpp"
#include "Squad.hpp"
#include "Fighter.hpp"
#include "Interceptor.hpp"
#include "Bomber.hpp"
#include "Raptor.hpp"

Squad::Squad() :_count(10){
	srand(time(NULL));
	this->_squad = new Marine *[this->_count];
	this->learnMarines();
	for (int i = 0; i < this->_count; ++i) {
		this->_squad[i] = this->_source[rand() % 4]->clone();
	}
}

Squad::~Squad() {
	for (int i = 0; i < 4; ++i) {
		delete (this->_source[i]);
	}
	for (int j = 0; j < this->_count; ++j) {
		delete this->_squad[j];
	}
	delete[](this->_squad);
}

Squad::Squad(const Squad &) {

}

Squad &Squad::operator=(Squad const &) {
	return *this;
}

void Squad::drawSquad() {
	for (int i = 0; i < this->_count; ++i) {
		this->_squad[i]->drawmarine();
	}

}

void Squad::learnMarines() {
	this->_source[0] = new Fighter();
	this->_source[1] = new Interceptor();
	this->_source[2] = new Bomber();
	this->_source[3] = new Raptor();
}

void Squad::action() {
	for (int i = 0; i < this->_count; ++i) {
		this->_squad[i]->movemarine();
		this->_squad[i]->attack();
	}
}

void Squad::popMarine(Marine *marine) {
	Marine **tmp = this->_squad;

	this->_squad = new Marine *[this->_count - 1];
	for (int j = 0, k = 0; j < this->_count; j++) {
		if (tmp[j] != marine){
			this->_squad[k] = tmp[j];
			++k;
		} else{
			mvprintw(71, 10, "deleted:[%p]", tmp[j]);
			delete tmp[j];
		}
	}
	delete[](tmp);
	this->_count--;
}

void Squad::dellDeadMarines() {
	for (int i = 0; i < this->_count; ++i) {
		if (this->_squad[i]->getX() == 0 || this->_squad[i]->getX() > X){
			popMarine(this->_squad[i]);
		}
	}
	mvprintw(72, 10, "count:[%d]", this->_count);
}
void Squad::pushMarine(Marine *newMarine) {

	Marine **tmp = this->_squad;

	this->_squad = new Marine *[this->_count + 1];
	for (int i = 0; i < this->_count; ++i) {
		this->_squad[i] = tmp[i];
	}
	this->_squad[this->_count] = newMarine;
	this->_count++;
	delete[](tmp);
}
int Squad::searchInterseption() {
	int tmp = 0;

	for (int i = 0; i < this->_count; ++i) {
		for (int j = i + 1; j < this->_count; ++j) {
			if (this->_squad[i]->getX() == this->_squad[j]->getX() &&
				this->_squad[i]->getY() == this->_squad[j]->getY()) {
				if ((!(this->_squad[i]->getType().compare("bullet")) &&
					 !(this->_squad[j]->getType().compare("pirate"))) ||
					(!(this->_squad[j]->getType().compare("bullet")) &&
					 !(this->_squad[i]->getType().compare("pirate")))) {
					mvprintw(66, 10, "squad[j] = %s", &(this->_squad[j]->getType())[0]);
					mvprintw(67, 10, "squad[j] = %s", &(this->_squad[i]->getType())[0]);
					this->popMarine(this->_squad[i]);
					this->popMarine(this->_squad[j - 1]);
					tmp += 20;
					i--;
					break;
				}
				if ((!(this->_squad[i]->getType().compare("bullet")) &&
					 !(this->_squad[j]->getType().compare("enemybullet"))) ||
					(!(this->_squad[j]->getType().compare("bullet")) &&
					 !(this->_squad[i]->getType().compare("enemybullet")))) {
					mvprintw(66, 10, "squad[j] = %s", &(this->_squad[j]->getType())[0]);
					mvprintw(67, 10, "squad[j] = %s", &(this->_squad[i]->getType())[0]);
					this->popMarine(this->_squad[i]);
					this->popMarine(this->_squad[j - 1]);
					tmp += 5;
					i--;
					break;
				}

			}
		}
	}
	return tmp;
}
