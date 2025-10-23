//
// Created by Alex on 18.05.2025.
//

#ifndef USERGUI_H
#define USERGUI_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QFormLayout>

#include "MovieTableView.h"
#include "Service.h"

class UserGUI final : public QWidget {
	Q_OBJECT

public:
	UserGUI(Service &service, MovieTableModel& watchListModel, QWidget *parent, bool isHTML);

	~UserGUI() override;

private:
	bool isHTML;
	Service &service;

	// main layout of the user GUI are 3 sections vertically
	QVBoxLayout* mainLayout;

	QVBoxLayout* WLSectionLayout;
	QWidget* WLSection; //section for the watchlist, either to add movies or see your watch list
	QLabel* errorLabel; // label for errors
	QPushButton* WLTableButton; // see WL as table -> HTML/CSS

	// buttons in the WL Section
	QPushButton* addMoviesGenreButton;
	QPushButton* seeWatchListButton;

	// Sections that appear when you push a button from the WL Section
	QWidget* addMoviesGenreSection;
	QHBoxLayout* addMoviesGenreLayout;
	QFormLayout* movieLayout;
	QWidget* movieForm; // this form will be put in the addmoviesgenresection

	// the movies genre section to add will have a field to decide the genre, and a button to see them
	// then the field and button will disappear and the movies will pop up
	QWidget* genreSection;
	QHBoxLayout* genreLayout;
	QLineEdit* genreToSearchField;
	QLabel* genreToSearchLabel;
	QPushButton* searchGenreButton;
	// we also need what happens when we search a genre, show the movies, one by one

	QPushButton* addMovie;
	QPushButton* nextMovie;

	int currentGenreMovie = -1;


	QLineEdit *titleField;
	QLabel *titleLabel;
	QLineEdit *genreField;
	QLabel *genreLabel;
	QLineEdit *likesField;
	QLabel *likesLabel;
	QLineEdit *yearField;
	QLabel *yearLabel;
	QLineEdit *linkField;
	QLabel *linkLabel;

	QWidget* seeWatchListSection;
	QHBoxLayout* seeWatchListLayout;

	QPushButton* nextMovieWL; // does not add movie
	QPushButton* likeMovie;

	MovieTableModel& watchListModel;
	QTableView* watchListView;






	// functions to initialise, connect signals and slots
	// and what happens when you press the buttons

	void init();

	void connectSignalsAndSlots();

	void handleSearchGenre();

	void handleSearchGenreButton() const;

	void handleNextGenreMovie();

	void handleAddMovieGenre();

	void handleLikeMovie();

	void handleNextMovieWL();

	void handleWLButton();

	void handleTable();
};


#endif //USERGUI_H
