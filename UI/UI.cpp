//
// Created by Alex on 23.03.2025.
//

#include "UI.h"

#include <iostream>


using std::exception;
using std::cin;
using std::cout;

char UI::getOption() {
	char option;
	cout << "Option: ";
	std::cin >> option;
	return option;
}

void UI::printAdminMenu() const {
	std::cout << admin;
}

void UI::printUserMenu() const {
	cout << user;
}

void UI::addMovieDBMenu() const {
	try {
		Movie m;
		cout << "Input the movie you wish to update in the format 'title;genre;year;likes;trailer'\n";
		cin.ignore();
		if (!(cin >> m)) {
			cout << "Input is invalid.\n";
			return;
		}
		v.validateMovie(m);
		this->service.addDB(m);
		cout << "Movie was successfully added to the database\n";
	} catch (exception &e) {
		cout << e.what() << '\n';
	}
}

void UI::removeMovieDBMenu() const {
	try {
		Movie m;
		cout << "Input the movie you wish to update in the format 'title;genre;year;likes;trailer'\n";
		cin.ignore();
		if (!(cin >> m)) {
			cout << "Input is invalid.\n";
			return;
		}
		v.validateMovie(m);
		this->service.removeDB(m);
		cout << "Movie was successfully removed from the database\n";
	} catch (exception &e) {
		cout << e.what() << '\n';
	}
}

void UI::updateMovieDBMenu() const {
	try {
		Movie m, um;
		cout << "Input the movie you wish to update in the format 'title;genre;year;likes;trailer'\n";
		cin.ignore();
		if (!(cin >> m)) {
			cout << "Input is invalid.\n";
			return;
		}

		cout << "Now input the new movie in the format 'title;genre;year;likes;trailer'\n";
		cin.ignore();
		if (!(cin >> um)) {
			cout << "Input is invalid.\n";
			return;
		}
		v.validateMovie(m);
		v.validateMovie(um);
		this->service.updateDB(m, um);
		cout << "Movie was successfully updated\n";
	} catch (exception &e) {
		cout << e.what() << '\n';
	}
}


void UI::printMoviesDB() const {
	vector<Movie> &movies = this->service.getMoviesDB();
	for (auto &movie: movies) {
		std::cout << movie;
	}
}

void UI::moviesWLMenu() const {
	vector<Movie> &movies = this->service.getMoviesUser();
	int i = 0;
	while (i != movies.size()) {
		Movie &curr = movies[i];
		std::cout << curr;

		cout << userWL;
		char option;
		cout << "Option: ";
		cin >> option;
		switch (option) {
			case '1':
				deleteMovieWLMenu(curr);
				break;
			case '2':
				i++;
				break;
			default:
				cout << invalidOption;
		}
	}
}

void UI::addMovieWL(Movie &curr) const {
	while (true) {
		cout << userADD;
		const char option = getOption();
		switch (option) {
			case '1':
				try {
					service.addWL(curr);
					cout << "Movie added to the watch list\n";
				} catch (WLException &e) {
					cout << e.what() << '\n';
				}
				return;
			case '2':
				return;
			default:
				cout << invalidOption;
		}
	}
}


void UI::addMovieWLMenu() const {
	string genre;
	cin.ignore();
	std::cout << "Genre: ";
	getline(cin, genre);


	vector<Movie> movies = this->service.getMoviesGenre(genre);
	for (auto &movie: movies) {
		std::cout << movie << '\n';
		addMovieWL(movie);
	}
}

void UI::deleteMovieWLMenu(Movie &m) const {
	cout << "Did you like it? (Y/y or N/n)\n";
	cout << "Option: ";
	char option;
	cin >> option;
	if (option == 'Y' || option == 'y') {
		try {
			service.removeWL(m, true);
			cout << "Movie successfully removed.";
		} catch (WLException &e) {
			cout << e.what();
		}
		return;
	}
	if (option == 'N' || option == 'n') {
		try {
			service.removeWL(m, false);
			cout << "Movie successfully removed.";
		} catch (WLException &e) {
			cout << e.what();
		}
		return;
	}
	cout << invalidOption;
	deleteMovieWLMenu(m);
}

void UI::chooseMenu() const {
	while (true) {
		std::cout << chooseMode;
		const char option = getOption();

		switch (option) {
			case '1':
				adminMenu();
				break;
			case '2':
				userMenu();
				break;
			case '0':
				return;
			default:
				std::cout << invalidOption;
		}
	}
}

void UI::adminMenu() const {
	while (true) {
		printAdminMenu();
		const char option = getOption();

		switch (option) {
			case '1':
				addMovieDBMenu();
				break;
			case '2':
				removeMovieDBMenu();
				break;
			case '3':
				updateMovieDBMenu();
				break;
			case '4':
				printMoviesDB();
				break;
			case '0':
				return;
			default:
				std::cout << invalidOption;
		}
	}
}

void UI::userMenu() const {
	while (true) {
		printUserMenu();
		const char option = getOption();

		switch (option) {
			case '1':
				addMovieWLMenu();
				break;
			case '2':
				moviesWLMenu();
				break;
			case '3':
				if (this->mode == "HTML")
					service.updateWLDisplay(), system("start firefox ../user.html");
				else
					service.updateWLDisplay(), system("..\\user.csv");
			case '0':
				return;
			default:
				std::cout << invalidOption;
		}
	}
}

UI::~UI() {
	delete &service;
}
