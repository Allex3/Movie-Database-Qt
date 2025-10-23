//
// Created by Alex on 23.03.2025.
//

#include "Service.h"

#include "Command.h"
#include "HTMLRepo.h"

Service::Service(IRepo& repo): repo(repo) {
	stackIndex = 0; //stack is currently at the element which can be redone
	// = after the last element which was "done" or "redone"
	// so the previous pointer on the stack is the next action to be undone
}

void Service::undo() {
	if (stackIndex <= 0)
		throw UndoException("There is no action to undo.\n");

	undoStack[--stackIndex]->undo();

}

void Service::redo() {
	// if it's beyond the stack, we are up to date fully (5 in stack, this will be 5, so after the 5 elements index wise)
	if (stackIndex == undoStack.size() || stackIndex < 0)
		throw UndoException("There is no action to redo.\n");

	undoStack[stackIndex++]->redo();
}

void Service::addDB(const Movie& m) {
	// NOT on the heap, makes a copy when added to the array, then discards it when we exit addDB
	// the line below MAY throw an exception if the movie exists, which is good
	this->repo.addDB(m);
	Command *addC = new AddCommand{repo, m};
	undoStack.push_back(addC);
	stackIndex = undoStack.size();
}

void Service::removeDB(const Movie& m) {
	//throw exception if movie is not found anyway
	this->repo.removeDB(m);
	Command *removeC = new RemoveCommand{repo, m};
	undoStack.push_back(removeC);
	stackIndex = undoStack.size();
}

void Service::updateDB(const Movie& m, const Movie& um) {
	//throw an exception if movie is not found so dw
	this->repo.updateDB(m, um);
	Command *updateC = new UpdateCommand{repo, m, um};
	undoStack.push_back(updateC);
	stackIndex = undoStack.size();
}

vector<Movie> &Service::getMoviesDB() const {
	return this->repo.getMoviesDB();
}

vector<Movie> Service::getMoviesGenre(const string &genre) const {
	vector<Movie> movgenre;
	std::copy_if(repo.getMoviesDB().begin(), repo.getMoviesDB().end(), std::back_inserter(movgenre),
		[genre](Movie x) {return x.getGenre() == genre;});
	return movgenre;
}

void Service::addWL(Movie &m) const {
	repo.addWL(m);
}

void Service::removeWL(Movie &m, const bool like) const {
	repo.removeWL(m, like);
	repo.writeToFileDB();
}

vector<Movie> &Service::getMoviesUser() const {
	return this->repo.getMoviesWL();
}

// only used for tests
Movie Service::getMovieFromDB(const Movie &m) const {
	const auto moviePos = std::find(this->repo.getMoviesDB().begin(), this->repo.getMoviesDB().end(), m);
	if (moviePos != repo.getMoviesDB().end())
		return *moviePos;

	return Movie("", "", -1, -1, "");
}

void Service::updateWLDisplay() const {
	repo.writeToFileWL();
}

Service::~Service() {
	for (Command* command: undoStack)
		delete command;
	delete &repo;
}
