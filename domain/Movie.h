//
// Created by Alex on 23.03.2025.
//

#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <algorithm>

using std::string;

class MovieException final : public std::exception {
	const char *s;
public:
	const char *what() const noexcept override {
		return s;
	}

	explicit MovieException(const char *s): s(s) { ; }
};

class Movie {
private:
	string title;
	string genre;
	int yearOfRelease;
	int likes;
	string trailer;

public:
	explicit Movie(string title, string genre, int yearOfRelease, int likes, string trailer);

	Movie();

	string getTitle();

	string getGenre();

	int getYear() const;

	int getLikes() const;

	string getTrailer();

	bool operator==(const Movie &m) const;

	void setTitle(string title);

	void setGenre(string genre);

	void setYear(int year);

	void setLikes(int likes);

	void setTrailer(string trailer);

	string toStr() const;
	
	friend std::istream& operator>>(std::istream& is, Movie& m);
	friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};


#endif //MOVIE_H
