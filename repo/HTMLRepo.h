//
// Created by Alex on 03.05.2025.
//

#ifndef HTMLREPO_H
#define HTMLREPO_H
#include "DefaultRepo.h"


class HTMLRepo final : public DefaultRepo {
private:
	string fileHTML;
public:
	HTMLRepo(vector<Movie>& moviesWL,
	vector<Movie>& moviesDB, string fileWL, string fileDB, string fileHTML);

	void writeToFileWL() const override;
};




#endif //HTMLREPO_H
