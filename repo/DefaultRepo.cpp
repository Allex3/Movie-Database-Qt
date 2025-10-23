//
// Created by Alex on 23.03.2025.
//

#include "DefaultRepo.h"

#include <exception>
using namespace std;


DefaultRepo::DefaultRepo(vector<Movie>& moviesWL,
	vector<Movie>& moviesDB, string fileWL, string fileDB): moviesWL(moviesWL),
                                                        moviesDB(moviesDB),
                                                        fileWL(
                                                        std::move(
                                                        fileWL)),
                                                        fileDB(
                                                        std::move(
                                                        fileDB)) {
	moviesDB.clear();
	moviesWL.clear();
	DefaultRepo::readFileDB();
	DefaultRepo::readFileWL();
}

void DefaultRepo::addWL(const Movie &m) const {
	const auto it = std::find(this->moviesWL.begin(), this->moviesWL.end(), m);
	if (it != moviesWL.end())
		throw WLException("Movie exists already!");
	moviesWL.push_back(m);
	writeToFileWL();
}

void DefaultRepo::removeWL(Movie &m, const bool like) const {
	const auto it = std::find(this->moviesWL.begin(), this->moviesWL.end(), m);
	if (it == moviesWL.end())
		throw WLException("Movie does not exist in the watchlist.");
	// if it exists, remove it from the watchlist and also add likes to it in the DB
	auto itdb = std::find(this->moviesDB.begin(), this->moviesDB.end(), m);
	if (like)
		m.setLikes(m.getLikes() + 1), *itdb = m;
	moviesWL.erase(it);
	writeToFileWL();
}

vector<Movie> &DefaultRepo::getMoviesWL() const {
	return moviesWL;
}

void DefaultRepo::readFileWL() const {
	ifstream f(fileWL);
	if (!f.is_open())
		throw WLException("File does not exist. Will close the program...");

	Movie m{};
	while (f >> m) {
		this->moviesWL.push_back(m);
	}

	f.close();
}

void DefaultRepo::writeToFileWL() const {
	ofstream f{fileWL};

	for (const auto &m: moviesWL)
		f << m;

	f.close();
}

void DefaultRepo::addDB(const Movie &movie) const {
	if (std::find(moviesDB.begin(), moviesDB.end(), movie) != moviesDB.end())
		throw DBException("Movie exists already.");
	this->moviesDB.emplace_back(movie);
	writeToFileDB();
}

void DefaultRepo::removeDB(const Movie &movie) const {
	const auto it = std::find(moviesDB.begin(), moviesDB.end(), movie);
	if (it == moviesDB.end()) // did not find movie to remove
		throw DBException("Movie does not exist.");
	moviesDB.erase(it);
	writeToFileDB();
}

void DefaultRepo::updateDB(const Movie &movie, const Movie &updatedMovie) const {
	const auto it = std::find(moviesDB.begin(), moviesDB.end(), movie);
	if (it == moviesDB.end()) // did not find movie to update
		throw DBException("Movie to update does NOT exist.");

	moviesDB.erase(it); // Remove old movie
	moviesDB.emplace_back(updatedMovie); // emplace_back the updated movie
	writeToFileDB();
}

Movie &DefaultRepo::getDB(const string &title, const string &genre, const int year, const int likes,
                          const string &trailer) const {
	const auto it = std::find(moviesDB.begin(), moviesDB.end(), Movie(title, genre, year, likes, trailer));
	if (it == moviesDB.end())
		throw DBException("There is no movie with this title in the database");
	return *it;
}

vector<Movie> &DefaultRepo::getMoviesDB() const {
	return moviesDB;
}

void DefaultRepo::readFileDB() const {
	ifstream f(fileDB);
	if (!f.is_open())
		throw DBException("File does not exist. Will close the program...");

	Movie m{};
	while (f >> m) {
		this->moviesDB.push_back(m);
	}

	f.close();
}

void DefaultRepo::writeToFileDB() const {
	ofstream f{fileDB};

	for (auto &m: moviesDB)
		f << m;

	f.close();
}

DefaultRepo::~DefaultRepo() {
}
