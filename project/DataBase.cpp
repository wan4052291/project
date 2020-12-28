#include<iostream>
#include"DataBase.h"
using namespace std;
using namespace N;
DataBase* DataBase::getInstance() {
	if (instance == NULL) {
		instance = new DataBase();
	}
	return instance;
}
DataBase* DataBase::instance = 0;
DataBase::DataBase() {

}