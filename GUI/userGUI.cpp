//
// Created by Alex on 18.05.2025.
//

#include "userGUI.h"

#include <qapplication.h>
#include <qlineedit.h>
#include <qscreen.h>

UserGUI::UserGUI(Service &service, MovieTableModel& watchListModel, QWidget *parent, bool isHTML):
QWidget(parent, Qt::Window), service(service), watchListModel(watchListModel), isHTML(isHTML) {
	init();
	connectSignalsAndSlots();
	this->setAttribute(Qt::WA_DeleteOnClose);
}

UserGUI::~UserGUI() {
	this->parentWidget()->show();
	delete &service;
}

void UserGUI::init() {

	const auto screen = QApplication::primaryScreen();
	const auto rect = screen->geometry();
	int height = 400;
	int width = 600;
	this->setGeometry(rect.width()/2-200, rect.height()/2-100, width, height);
	QApplication::setFont(QFont("Verdana", 11));

	mainLayout = new QVBoxLayout(this);

	WLSection = new QWidget();
	WLSectionLayout = new QVBoxLayout(WLSection);
	genreSection = new QWidget();

	errorLabel = new QLabel("Error");
	errorLabel->setStyleSheet("color: red");
	WLTableButton = new QPushButton("See watch list as a table");

	watchListView = new QTableView();
	watchListView->setModel(&watchListModel);

	mainLayout->addWidget(WLSection);
	mainLayout->addWidget(errorLabel);
	errorLabel->hide();
	mainLayout->addWidget(WLTableButton);
	mainLayout->addWidget(watchListView);

	// set up the WLSection
	addMoviesGenreButton = new QPushButton("Add Movies by genre");
	seeWatchListButton = new QPushButton("See watch list and mark movies");

	// set up the sections

	WLSectionLayout->addWidget(addMoviesGenreButton);
	WLSectionLayout->addWidget(genreSection);
	WLSectionLayout->addWidget(seeWatchListButton);


	// set up genre searching
	genreLayout = new QHBoxLayout(genreSection);
	genreToSearchField = new QLineEdit();
	genreToSearchLabel = new QLabel("&Genre: ");
	genreToSearchLabel->setBuddy(genreToSearchField);
	searchGenreButton = new QPushButton("Search");

	genreLayout->addWidget(genreToSearchLabel);
	genreLayout->addWidget(genreToSearchField);
	genreLayout->addWidget(searchGenreButton);

	genreSection->hide();

	addMoviesGenreSection = new QWidget(this, Qt::Window);
	addMoviesGenreSection->hide();
	addMoviesGenreLayout = new QHBoxLayout(addMoviesGenreSection);

	movieForm = new QWidget(); //the first input form using a qformlayout
	// form layout is like a vertical grid, with columns
	movieLayout = new QFormLayout(movieForm);

	titleLabel = new QLabel("Title: ");
	titleField = new QLineEdit();
	titleField->setReadOnly(true);
	titleLabel->setBuddy(titleField);
	genreLabel = new QLabel("Genre: ");
	genreField = new QLineEdit();
	genreField->setReadOnly(true);
	genreLabel->setBuddy(genreField);
	yearLabel = new QLabel("Year: ");
	yearField = new QLineEdit();
	yearField->setReadOnly(true);
	yearLabel->setBuddy(yearField);
	likesLabel = new QLabel("Likes: ");
	likesField = new QLineEdit();
	likesField->setReadOnly(true);
	likesLabel->setBuddy(likesField);
	linkLabel = new QLabel("Trailer: ");
	linkField = new QLineEdit();
	linkField->setReadOnly(true);
	linkLabel->setBuddy(linkField);


	movieLayout->addRow(titleLabel, titleField);
	movieLayout->addRow(genreLabel, genreField);
	movieLayout->addRow(yearLabel, yearField);
	movieLayout->addRow(likesLabel, likesField);
	movieLayout->addRow(linkLabel, linkField);


	addMoviesGenreLayout->addWidget(movieForm);
	nextMovie = new QPushButton("Next");
	likeMovie = new QPushButton("Like");
	addMovie = new QPushButton("Add");
	nextMovieWL = new QPushButton("Next");
	addMoviesGenreLayout->addWidget(nextMovie);
	addMoviesGenreLayout->addWidget(nextMovieWL);

	addMoviesGenreLayout->addWidget(likeMovie);
	likeMovie->hide();
	addMoviesGenreLayout->addWidget(addMovie);


}

void UserGUI::connectSignalsAndSlots() {
	connect(addMoviesGenreButton, &QPushButton::clicked, this, &UserGUI::handleSearchGenreButton);
	connect(searchGenreButton, &QPushButton::clicked, this, &UserGUI::handleSearchGenre);
	connect(nextMovie, &QPushButton::clicked, this, &UserGUI::handleNextGenreMovie);
	connect(addMovie, &QPushButton::clicked, this, &UserGUI::handleAddMovieGenre);
	connect(seeWatchListButton, &QPushButton::clicked, this, &UserGUI::handleWLButton);
	connect(nextMovieWL, &QPushButton::clicked, this, &UserGUI::handleNextMovieWL);
	connect(likeMovie, &QPushButton::clicked, this, &UserGUI::handleLikeMovie);
	connect(WLTableButton,&QPushButton::clicked, this, &UserGUI::handleTable);

}

void UserGUI::handleSearchGenreButton() const {
	errorLabel->hide();
	addMoviesGenreButton->hide();
	seeWatchListButton->hide();
	genreSection->show();
}

void UserGUI::handleSearchGenre() {
	string genre = genreToSearchField->text().toStdString();

	vector<Movie> movies = service.getMoviesGenre(genre);

	if (movies.empty()) {
		addMoviesGenreButton->show();
		genreSection->hide();
		errorLabel->setText("There are no movies with that genre");
		errorLabel->show();
		return;
	}
	currentGenreMovie = 0;
	Movie m = movies[0];
	titleField->setText(m.getTitle().data());
	genreField->setText(m.getGenre().data());
	stringstream ss;
	ss << m.getLikes();
	likesField->setText(ss.str().data());
	stringstream sy;
	sy << m.getYear();
	yearField->setText(sy.str().data());
	linkField->setText(m.getTrailer().data());

	genreSection->hide();
	addMoviesGenreSection->show(); //show the widget with each movie
	addMovie->show();
	nextMovie->show();
	nextMovieWL->hide();
	likeMovie->hide();
	// handle ONLY the first movie
}

void UserGUI::handleNextGenreMovie() {
	string genre = genreToSearchField->text().toStdString();
	vector<Movie> movies = service.getMoviesGenre(genre);

	if (currentGenreMovie + 1 == movies.size()) {
		addMoviesGenreSection->hide();
		genreSection->hide();
		addMoviesGenreButton->show();
		seeWatchListButton->show();
		return;
	}
	currentGenreMovie++;
	Movie m = movies[currentGenreMovie];
	titleField->setText(m.getTitle().data());
	genreField->setText(m.getGenre().data());
	stringstream ss;
	ss << m.getLikes();
	likesField->setText(ss.str().data());
	stringstream sy;
	sy << m.getYear();
	yearField->setText(sy.str().data());
	linkField->setText(m.getTrailer().data());

}

void UserGUI::handleAddMovieGenre() {
	string title = titleField->text().toStdString();
	string genre = genreField->text().toStdString();
	string year = yearField->text().toStdString();
	string likes = likesField->text().toStdString();
	string link = linkField->text().toStdString();

	try {

		Movie m{title, genre, stoi(year), stoi(likes), link};
		// each of the above validations can throw an exception, or the one when adding below!
		service.addWL(m);
	}
	catch (exception& e) {
		errorLabel->setText(e.what());
		errorLabel->show();
	}
	vector<Movie> emptyVector;
	MovieTableModel empty(emptyVector);
	watchListView->setModel(&empty);
	watchListView->setModel(&watchListModel);
	handleNextGenreMovie();
}


void UserGUI::handleLikeMovie() {
	string title = titleField->text().toStdString();
	string genre = genreField->text().toStdString();
	string year = yearField->text().toStdString();
	string likes = likesField->text().toStdString();
	string link = linkField->text().toStdString();

	try {
		Movie m{title, genre, stoi(year), stoi(likes), link};
		// each of the above validations can throw an exception, or the one when adding below!
		service.removeWL(m, true);
	}
	catch (exception& e) {
		errorLabel->setText(e.what());
		errorLabel->show();
	}
	currentGenreMovie--;
	handleNextMovieWL();
}

void UserGUI::handleNextMovieWL() {
	vector<Movie> movies = service.getMoviesUser();

	cout<<movies.size();
	if (currentGenreMovie + 1 >= movies.size()) {
		addMoviesGenreSection->hide();
		genreSection->hide();
		seeWatchListButton->show();
		addMoviesGenreButton->show();
		return;
	}
	currentGenreMovie++;
	Movie m = movies[currentGenreMovie];
	titleField->setText(m.getTitle().data());
	genreField->setText(m.getGenre().data());
	stringstream ss;
	ss << m.getLikes();
	likesField->setText(ss.str().data());
	stringstream sy;
	sy << m.getYear();
	yearField->setText(sy.str().data());
	linkField->setText(m.getTrailer().data());

}

void UserGUI::handleWLButton() {

	vector<Movie> movies = service.getMoviesUser();

	errorLabel->hide();
	if (movies.empty()) {
		errorLabel->setText("There are no movies that the user has yet");
		errorLabel->show();
		return;
	}
	currentGenreMovie = 0;
	seeWatchListButton->hide();
	addMoviesGenreButton->hide();
	addMoviesGenreSection->show();
	addMovie->hide();
	nextMovie->hide();
	nextMovieWL->show();
	likeMovie->show();

	currentGenreMovie = 0;
	Movie m = movies[0];
	titleField->setText(m.getTitle().data());
	genreField->setText(m.getGenre().data());
	stringstream ss;
	ss << m.getLikes();
	likesField->setText(ss.str().data());
	stringstream sy;
	sy << m.getYear();
	yearField->setText(sy.str().data());
	linkField->setText(m.getTrailer().data());

	addMoviesGenreSection->show(); //show the widget with each movie
	// handle ONLY the first movie

}

void UserGUI::handleTable() {
	service.updateWLDisplay();
	if (isHTML)
		system("open ../user.html");
	else
		system("libreoffice ../user.csv");
}
