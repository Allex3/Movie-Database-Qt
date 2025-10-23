//
// Created by Alex on 03.05.2025.
//

#include "CSVRepo.h"

#include <utility>
#include <fstream>

CSVRepo::CSVRepo(vector<Movie>& moviesWL,
	vector<Movie>& moviesDB, string fileWL, string fileDB, string fileCSV): DefaultRepo(moviesWL, moviesDB, std::move(fileWL), std::move(fileDB)), fileCSV(std::move(fileCSV)) {

}

void CSVRepo::writeToFileWL() const {
	DefaultRepo::writeToFileWL();
	ofstream f{fileCSV};

	for (auto &movie: moviesWL) {
		f << movie.getTitle() << ",";
		f << movie.getGenre() << ",";
		f << movie.getYear() << ",";
		f << movie.getLikes() << ",";
		f << movie.getTrailer() << ",";
		f << '\n';
	}

	f.close();
}
