//
// Created by Alex on 03.05.2025.
//

#ifndef DEFAULTREPO_H
#define DEFAULTREPO_H
#include <utility>

#include "IRepo.h"


class DefaultRepo : public IRepo {
protected:
	vector<Movie>& moviesWL;
	vector<Movie>& moviesDB;
	string fileWL;
	string fileDB;
public:
	DefaultRepo(vector<Movie>& moviesWL,
	vector<Movie>& moviesDB, string fileWL, string fileDB);

	void addWL(const Movie &m) const override;

	void removeWL(Movie &m, bool like) const override;

	[[nodiscard]] vector<Movie> &getMoviesWL() const override;

	void readFileWL() const override;

	void writeToFileWL() const override;

	void addDB(const Movie &movie) const override;

	void removeDB(const Movie &movie) const override;

	void updateDB(const Movie &movie, const Movie &updatedMovie) const override;

	[[nodiscard]] Movie &getDB(const string &title, const string &genre, int year, int likes, const string &trailer) const override;

	[[nodiscard]] vector<Movie> &getMoviesDB() const override;

	void readFileDB() const override;

	void writeToFileDB() const override;

	~DefaultRepo() override ;
};



#endif //DEFAULTREPO_H
