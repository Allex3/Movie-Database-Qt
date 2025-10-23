//
// Created by Alex on 03.05.2025.
//



#ifndef IREPO_H
#define IREPO_H

#include "Movie.h"
#include <vector>
using namespace std;

using std::exception;

class DBException final : public exception {
	const char *s;
public:
	const char *what() const noexcept override {
		return s;
	}

	explicit DBException(const char *s): s(s) { ; }
};


class WLException final : public exception {
private:
	const char *s;
public:
	const char *what() const noexcept override {
		return s;
	}

	explicit WLException(const char *s): s(s) { ; }
};


class IRepo {
public:
	// Adds a movie to the watch list of the user
	virtual void addWL(const Movie& m) const = 0;

	// Delete a movie from the watch list
	// Also choose when removing it, if you want to like it
	// The likes will be added in the database
	virtual void removeWL(Movie &m, bool like) const = 0;

	// Get the list of movies of the watch list of the user
	virtual vector<Movie>& getMoviesWL() const = 0;

	virtual void readFileWL() const = 0;

	virtual void writeToFileWL() const = 0;

	// Adds a movie to the database
	// :movie: The movie to add
	virtual void addDB(const Movie& movie) const = 0;

	// Removes a movie from the database
	// :movie: The movie to be removed
	virtual void removeDB(const Movie& movie) const = 0;

	// Updates a movie from the database
	// :movie: The movie to be updated
	// :updatedMovie: The updated version of the movie
	virtual void updateDB(const Movie &movie, const Movie &updatedMovie) const = 0;

	virtual Movie& getDB(const string &title, const string &genre, int year, int likes, const string &trailer) const = 0;

	virtual vector<Movie>& getMoviesDB() const = 0;

	virtual void readFileDB() const = 0;
	virtual void writeToFileDB() const = 0;

	virtual ~IRepo() = default;
};



#endif //IREPO_H
