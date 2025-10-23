//
// Created by Alex on 23.03.2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "IRepo.h"

#include "ICommand.h"

class UndoException final : public exception {
	const char *s;
public:
	[[nodiscard]] const char *what() const noexcept override {
		return s;
	}

	explicit UndoException(const char *s): s(s) { ; }
};

class Service {
private:
	IRepo &repo;
	vector<Command*> undoStack;
	int stackIndex;
public:
	explicit Service(IRepo &repo);


	void undo();
	void redo();

	void addDB(const Movie& m) ;

	void removeDB(const Movie& m) ;

	void updateDB(const Movie& m, const Movie& um) ;

	vector<Movie> &getMoviesDB() const;

	vector<Movie> getMoviesGenre(const string &genre) const;

	void addWL(Movie& m) const;
	void removeWL(Movie& m, bool like) const;
	vector<Movie> &getMoviesUser() const;

	Movie getMovieFromDB(const Movie &m) const;

	void updateWLDisplay() const;

	~Service();
};



#endif //SERVICE_H
