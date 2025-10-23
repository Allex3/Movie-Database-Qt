//
// Created by Alex on 24.03.2025.
//

#include "tests.h"
#include <cassert>

#include "DefaultRepo.h"
#include "Movie.h"
#include "Service.h"

void Tests::testMovie() {
	Movie m;
	m.setGenre("dsff");
	assert(m.getGenre() == "dsff");
	m.setTitle("newtt");
	assert(m.getTitle() == "newtt");
	m.setYear(2051);
	assert(m.getYear()==2051);
	m.setLikes(11);
	assert(m.getLikes() == 11);
	m.setTrailer("www.example.com");
	assert(m.getTrailer() == "www.example.com");
}

void Tests::testAddDB() {
	 auto* moviesWL = new vector<Movie>;
	 auto* moviesDB = new vector<Movie>;
	 auto *repo = new DefaultRepo{*moviesWL, *moviesDB, "../testusermovies.txt", "../testmovies.txt"};
	 auto *ss = new Service{*repo};
	 auto &s = *ss;


	s.addDB(Movie{"abc", "def", 2010, 51, "www.com"});
	s.addDB(Movie{"abfdac", "deafsf", 2005, 12, "www.codgm"});
	s.addDB(Movie{"The", "Horror", 2001, 91, "no"});
	try {
		s.addDB(Movie{"abc", "def", 2010, 51, "www.com"}); //already exists
		// equal when title and year are the same
		assert(false);
	} catch (DBException &e) {
		assert(true);
	}
	try {
		s.addDB(Movie{
			"abc", "dgfdef", 2015, 11, "www.com"
		}); //already exists
		assert(true);
	} catch (DBException &e) {
		assert(false);
	}
	try {
		s.addDB(Movie{"agsdfbc", "dgfdef", 2010, 11, "www.com"}); //already exists
		assert(true);
	} catch (DBException &e) {
		assert(false);
	}std::ofstream f("../testmovies.txt");
	f << "";
	f.close();
	f.open("../testusermovies.txt");
	f << "";
	f.close();

	delete moviesDB;
	delete moviesWL;
	delete ss;
}

void Tests::testRemoveDB() {
	auto* moviesWL = new vector<Movie>;
	auto* moviesDB = new vector<Movie>;
	auto *repo = new DefaultRepo{*moviesWL, *moviesDB, "../testusermovies.txt", "../testmovies.txt"};
	auto *ss = new Service{*repo};
	auto &s = *ss;


	s.addDB(Movie{"abc", "def", 2010, 51, "www.com"});
	s.addDB(Movie{"abfdac", "deafsf", 2005, 12, "www.codgm"});
	s.addDB(Movie{"The", "Horror", 2001, 91, "no"});
	try {
		s.removeDB(Movie{"abc", "dgfdef", 2010, 11, "www.com"}); //already exists
		// does not exist
		assert(false);
	} catch (DBException &e) {
		e.what();
		assert(true);
	}
	try {
		s.removeDB(Movie{"The", "Horror", 2001, 91, "no"});
		assert(true);
	} catch (DBException &e) {
		assert(false);
	}std::ofstream f("../testmovies.txt");
	f << "";
	f.close();
	f.open("../testusermovies.txt");
	f << "";
	f.close();
	delete moviesDB;
	delete moviesWL;
	delete ss;
}

void Tests::testUpdateDB() {
	auto* moviesWL = new vector<Movie>;
	auto* moviesDB = new vector<Movie>;
	auto *repo = new DefaultRepo{*moviesWL, *moviesDB, "../testusermovies.txt", "../testmovies.txt"};
	auto *ss = new Service{*repo};
	auto &s = *ss;

	s.addDB(Movie{"abc", "def", 2010, 51, "www.com"});
	s.addDB(Movie{"abfdac", "deafsf", 2005, 12, "www.codgm"});
	s.addDB(Movie{"The", "Horror", 2001, 91, "no"});
	try {
		s.updateDB(Movie{"abc", "dgfdef", 2010, 11, "www.com"}, Movie{"newt", "newg", 1031, 45, "gfsdg"});
		//already exists
		// movie does not exist
		assert(false);
	} catch (DBException &e) {
		assert(true);
	}
	try {
		s.updateDB(Movie{"The", "Horror", 2001, 91, "no"}, Movie{"dgas", "gd", 1000, 541, "hdfdgsd"}); //already exists
		// movie exists
		assert(true);
	} catch (DBException &e) {
		assert(false);
	}
	std::ofstream f("../testmovies.txt");
	f << "";
	f.close();
	f.open("../testusermovies.txt");
	f << "";
	f.close();
	delete moviesDB;
	delete moviesWL;
	delete ss;
}

void Tests::testAddWL() {
	auto* moviesWL = new vector<Movie>;
	auto* moviesDB = new vector<Movie>;
	auto *repo = new DefaultRepo{*moviesWL, *moviesDB, "../testusermovies.txt", "../testmovies.txt"};
	auto *ss = new Service{*repo};
	auto &s = *ss;
	Movie m1("The", "Horror", 2001, 91, "no");

	s.addDB(Movie{"abc", "def", 2010, 51, "www.com"});
	s.addDB(Movie{"abfdac", "deafsf", 2005, 12, "www.codgm"});
	s.addDB(Movie{"The", "Horror", 2001, 91, "no"});
	try {
		s.addWL(m1); //should add m1 from the DB
		assert(true);
	} catch (WLException &e) {
		assert(false);
	}
	try {
		s.addWL(m1); //should throw exception cuz it exists
		assert(false);
	} catch (WLException &e) {
		assert(true);
	}
	std::ofstream f("../testmovies.txt");
	f << "";
	f.close();
	f.open("../testusermovies.txt");
	f << "";
	f.close();
	delete moviesDB;
	delete moviesWL;
	delete ss;
}

void Tests::testRemoveWL() {
	auto* moviesWL = new vector<Movie>;
	auto* moviesDB = new vector<Movie>;
	auto *repo = new DefaultRepo{*moviesWL, *moviesDB, "../testusermovies.txt", "../testmovies.txt"};
	auto *ss = new Service{*repo};
	auto &s = *ss;

	Movie m1("The", "Horror", 2001, 0, "no");
	Movie m2("abc", "def", 2010, 0, "www.com");
	s.addDB(Movie{"abc", "def", 2010, 0, "www.com"});
	s.addDB(Movie{"abfdac", "deafsf", 2005, 12, "www.codgm"});
	s.addDB(Movie{"The", "Horror", 2001, 0, "no"});
	try {
		s.addWL(m1); //should add m1 from the DB
		s.removeWL(m1, true);
		Movie mdb = s.getMovieFromDB(m1); //get the movie form db according to m1
		assert(mdb.getLikes() == 1);
	} catch (WLException &e) {
		assert(false);
	}
	try {
		s.addWL(m2); //should throw exception cuz it exists
		s.removeWL(m2, false);
		Movie mdb = s.getMovieFromDB(m2); //get the movie form db according to m1
		assert(mdb.getLikes() == 0);
	} catch (WLException &e) {
		assert(false);
	}
	try {
		s.removeWL(m2, false);
		assert(false);
	} catch (WLException &e) {
		e.what();
		assert(true);
	}
	std::ofstream f("../testmovies.txt");
	f << "";
	f.close();
	f.open("../testusermovies.txt");
	f << "";
	f.close();
	delete moviesDB;
	delete moviesWL;
	delete ss;
}

void Tests::testGetMovies() {
	auto* moviesWL = new vector<Movie>;
	auto* moviesDB = new vector<Movie>;
	auto *repo = new DefaultRepo{*moviesWL, *moviesDB, "../testusermovies.txt", "../testmovies.txt"};
	auto *ss = new Service{*repo};
	auto &s = *ss;

	auto &moviesdb = s.getMoviesDB();
	auto &user = s.getMoviesUser();
	Movie m("a", "b", 0, 0, "c");
	s.getMovieFromDB(m);

	std::ofstream f("../testmovies.txt");
	f << "";
	f.close();
	f.open("../testusermovies.txt");
	f << "";
	f.close();
	delete moviesDB;
	delete moviesWL;
	delete ss;
}
