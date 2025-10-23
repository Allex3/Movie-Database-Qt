//
// Created by Alex on 23.03.2025.
//

#ifndef UI_H
#define UI_H
#include "Service.h"
#include "Validator.h"

class UI {
private:
	Validator v;
	Service &service;
	string mode;
	const char *invalidOption = "Your option is invalid. Try again.\n";
	const char *chooseMode = "(1) Administrator\n(2) User\n(0) Exit.\n";
	const char *admin =
			"(1) Add a new movie.\n(2) Remove a movie.\n(3) Update a movie.\n(4) Display all movies.\n(0) Exit.\n";
	const char *user = "(1) View movies with a specific genre to add\n(2) View your watch list to mark as watched\n (3) View your watch list as a table\n(0) Exit\n";
	const char *userWL = "(1) Remove the current movie from the watch list\n(2) Next\n(0) Exit\n";
	const char *userADD = "(1) Add movie to your watch list :3\n(2) Next\n(0) Exit\n";

public:
	explicit UI(Service &service, string mode) : service(service), mode(std::move(mode)) { v = Validator(); }

	static char getOption();

	void printAdminMenu() const;

	void printUserMenu() const;


	void addMovieDBMenu() const;

	void removeMovieDBMenu() const;

	void updateMovieDBMenu() const;

	void printMoviesDB() const;

	/*
	 * See the movies in the database having a specific genre, one by one
	 * If the user likes the movie, they can add it to their watch list.
	 * If not, they can go to the next one..
	 */
	void moviesWLMenu() const;

	void addMovieWLMenu() const;

	void addMovieWL(Movie &curr) const;

	// Delete movie after the user watched it
	// Also they can choose to like it or not
	void deleteMovieWLMenu(Movie &m) const;

	void chooseMenu() const;

	void adminMenu() const;

	void userMenu() const;

	~UI();
};


#endif //UI_H
