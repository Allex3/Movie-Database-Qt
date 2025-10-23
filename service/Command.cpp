//
// Created by axolotl on 6/3/25.
//

#include "Command.h"

AddCommand::AddCommand(IRepo &repo, Movie movie):
movie(std::move(movie)), repo(repo){
}

void AddCommand::undo() const {
	repo.removeDB(movie);
}

void AddCommand::redo() const {
	repo.addDB(movie);
}

AddCommand::~AddCommand() {;
}

RemoveCommand::RemoveCommand(IRepo &repo, Movie movie): movie(std::move(movie)), repo(repo) {
}

void RemoveCommand::undo() const {
	repo.addDB(movie);
}

void RemoveCommand::redo() const {
	repo.removeDB(movie);
}

RemoveCommand::~RemoveCommand() {
	;
}

UpdateCommand::UpdateCommand(IRepo &repo, Movie movie, Movie updatedMovie): movie(std::move(movie)), updatedMovie(std::move(updatedMovie)), repo(repo) {
}

void UpdateCommand::undo() const {
	repo.updateDB(updatedMovie, movie);
}

void UpdateCommand::redo() const {
	repo.updateDB(movie, updatedMovie);
}

UpdateCommand::~UpdateCommand() {
	;
}
