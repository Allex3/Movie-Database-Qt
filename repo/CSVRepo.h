//
// Created by Alex on 03.05.2025.
//

#ifndef CSVREPO_H
#define CSVREPO_H

#include "DefaultRepo.h"

class CSVRepo final : public DefaultRepo {
private:
	string fileCSV;

public:
	CSVRepo(vector<Movie> &moviesWL,
	        vector<Movie> &moviesDB, string fileWL, string fileDB,
	        string fileCSV);

	void writeToFileWL() const override;
};


#endif //CSVREPO_H
