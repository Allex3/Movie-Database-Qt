//
// Created by Alex on 23.03.2025.
//

#include "Movie.h"

#include <cstdio>
#include <utility>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

Movie::Movie(string title, string genre, const int yearOfRelease, const int likes, string trailer) {
	this->title = std::move(title);
	this->genre = std::move(genre);
	this->yearOfRelease = yearOfRelease;
	this->likes = likes;
	this->trailer = std::move(trailer);
}


Movie::Movie() {
	this->title = "";
	this->genre = "";
	this->yearOfRelease = 0;
	this->likes = 0;
	this->trailer = "";
}

string Movie::getTitle() {
	return title;
}

string Movie::getGenre() {
	return genre;
}

int Movie::getYear() const {
	return yearOfRelease;
}

int Movie::getLikes() const {
	return likes;
}

string Movie::getTrailer() {
	return trailer;
}

bool Movie::operator==(const Movie &m) const {
	if (m.title == title && m.genre == genre && m.yearOfRelease == yearOfRelease
		&& m.trailer == trailer)
		return true;
	return false;
}

void Movie::setTitle(string title) {
	this->title = std::move(title);
}

void Movie::setGenre(string genre) {
	this->genre = std::move(genre);
}

void Movie::setYear(const int year) {
	this->yearOfRelease = year;
}

void Movie::setLikes(const int likes) {
	this->likes = likes;
}

void Movie::setTrailer(string trailer) {
	this->trailer = std::move(trailer);
}

string Movie::toStr() const{
	stringstream os;
	os<<title<<";";
	os<<genre<<";";
	os<<yearOfRelease<<";";
	os<<likes<<";";
	os<<trailer<<"\n";
	return os.str();
}

vector<string> tokenize(const string& str, const char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

std::istream & operator>>(std::istream &is, Movie &m) {
	string line; //for our movie, each "line" is delimited by ;, returning 5 tokens
	getline(is, line);

	vector<string> tokens = tokenize(line, ';');
	if (tokens.size() != 5)
		return is;

	m.setTitle(tokens[0]);
	m.setGenre(tokens[1]);

	stringstream number;
	std::string::const_iterator it = tokens[2].begin();
	while (it != tokens[2].end() && isdigit(*it)) ++it;
	if (it != tokens[2].end()) //not a number, found a digit
		throw MovieException("The year should be a number (2000-3000)");
	number << tokens[2];
	number >> m.yearOfRelease;

	it = tokens[3].begin();
	while (it != tokens[3].end() && isdigit(*it)) ++it;
	if (it != tokens[3].end()) //not a number, found a digit
		throw MovieException("The year should be a number (2000-3000)");

	number.str(string());
	number.clear();
	number <<tokens[3];
	number >> m.likes;

	m.trailer = tokens[4];

	return is;
}

ostream& operator<<(ostream& os, const Movie& m) {
	os<<m.title<<";";
	os<<m.genre<<";";
	os<<m.yearOfRelease<<";";
	os<<m.likes<<";";
	os<<m.trailer<<"\n";
	return os;

}


