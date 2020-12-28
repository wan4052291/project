#pragma once
#include<vector>
#include<string>
#include<mysql.h>
namespace N{
	class DataBase {
	private:		
		DataBase();
		static DataBase *instance;
		std::vector<std::string> artiList;
	public:
		int n;
		static DataBase* getInstance();
		std::vector<std::string> getArtiList();
		std::string getArti(std::string);
		
	};
}
