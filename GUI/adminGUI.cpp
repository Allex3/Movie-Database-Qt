//
// Created by Alex on 18.05.2025.
//

#include "adminGUI.h"

#include <qapplication.h>
#include <qlineedit.h>
#include <qtextlayout.h>

// initialise its parent as a window widget given by the widget parent
// which will be the mainMenu here, being another window
AdminGUI::AdminGUI(Service &service, QWidget *parent): QWidget(
	parent, Qt::Window), service(service) {
	init();
	connectSignalsAndSlots();
	this->setAttribute(Qt::WA_DeleteOnClose);
}

AdminGUI::~AdminGUI() {
	this->parentWidget()->show();
	delete &service;
}

void AdminGUI::init() {
	const auto screen = QApplication::primaryScreen();
	const auto rect = screen->geometry();
	int height = 200;
	int width = 600;
	this->setGeometry(rect.width() / 2 - 200, rect.height() / 2 - 100, width,
	                  height);
	QApplication::setFont(QFont("Verdana", 11));

	this->setWindowTitle("Admin Menu");
	// set the main layout of our admin GUI
	mainLayout = new QVBoxLayout(this);

	// initialise the input buttons section using a horizontal layout, having 3 buttons
	inputButtonsSection = new QWidget();
	inputButtonsLayout = new QHBoxLayout(inputButtonsSection);
	addFormButton = new QPushButton("&Add");
	removeFormButton = new QPushButton("&Remove");
	updateFormButton = new QPushButton("&Update");
	inputButtonsLayout->addWidget(addFormButton);
	//also becomes child of parent of layout i think
	inputButtonsLayout->addWidget(removeFormButton);
	inputButtonsLayout->addWidget(updateFormButton);

	// initialise the error label
	errorLabel = new QLabel("Error text");
	errorLabel->setStyleSheet("color: red");
	errorLabel->hide(); //hide until there's an error

	// initialise the movie list that will show the movies.txt
	moviesList = new QListWidget();


	mainLayout->addWidget(inputButtonsSection);


	inputSection = new QWidget();
	inputSectionLayout = new QHBoxLayout(inputSection);
	// inputbuttonssection will be hidden and this will be shown
	//so they are bascially in the same place
	mainLayout->addWidget(inputSection);
	inputSection->hide();

	// intiialise the UNDO/REDO section
	undoRedoSection = new QWidget();
	undoRedoSectionLayout = new QHBoxLayout(undoRedoSection);
	undoButton = new QPushButton("Undo");
	redoButton = new QPushButton("Redo");
	undoRedoSectionLayout->addWidget(undoButton);
	undoRedoSectionLayout->addWidget(redoButton);

	// init the actions
	undoAction = new QAction{this};
	redoAction = new QAction{this};
	undoAction->setShortcut(QKeySequence::Undo);
	redoAction->setShortcut(QKeySequence::Redo);
	this->addAction(undoAction);
	this->addAction(redoAction);


	mainLayout->addWidget(undoRedoSection);

	mainLayout->addWidget(errorLabel);
	// align the error text in the center of the line
	mainLayout->setAlignment(errorLabel, Qt::AlignCenter);
	mainLayout->addWidget(moviesList);

	//(QWidget is like a div in html)
	// init the input section, with one/two forms and the button to add/remove/up[date
	// for add/remove -> 1 form, 1 button horizontal box
	// for update -> 2 forms, 1 button, in a hbox

	//when you press a button add/remove/update in the main menu it will
	//show the inputSection, and hide the inputButtonsSection
	// when we finish the CRUD Operation it will hide and show again the buttons


	// initialise the first form
	inputForm = new QWidget(); //the first input form using a qformlayout
	// form layout is like a vertical grid, with columns
	inputFormLayout = new QFormLayout(inputForm);
	//inputForm->setLayout(inputFormLayout)
	titleLabel = new QLabel("Title: ");
	titleField = new QLineEdit();
	titleLabel->setBuddy(titleField);
	genreLabel = new QLabel("Genre: ");
	genreField = new QLineEdit();
	genreLabel->setBuddy(genreField);
	yearLabel = new QLabel("Year: ");
	yearField = new QLineEdit();
	yearLabel->setBuddy(yearField);
	likesLabel = new QLabel("Likes: ");
	likesField = new QLineEdit();
	likesLabel->setBuddy(likesField);
	linkLabel = new QLabel("Trailer: ");
	linkField = new QLineEdit();
	linkLabel->setBuddy(linkField);

	inputFormLayout->addRow(titleLabel, titleField);
	inputFormLayout->addRow(genreLabel, genreField);
	inputFormLayout->addRow(yearLabel, yearField);
	inputFormLayout->addRow(likesLabel, likesField);
	inputFormLayout->addRow(linkLabel, linkField);

	// now the updated form for the update operation
	uinputForm = new QWidget(); //the first input form using a qformlayout
	// form layout is like a vertical grid, with columns
	uinputFormLayout = new QFormLayout(uinputForm);
	//inputForm->setLayout(inputFormLayout)
	utitleLabel = new QLabel("Title: ");
	utitleField = new QLineEdit();
	utitleLabel->setBuddy(utitleField);
	ugenreLabel = new QLabel("Genre: ");
	ugenreField = new QLineEdit();
	ugenreLabel->setBuddy(ugenreField);
	uyearLabel = new QLabel("Year: ");
	uyearField = new QLineEdit();
	uyearLabel->setBuddy(uyearField);
	ulikesLabel = new QLabel("Likes: ");
	ulikesField = new QLineEdit();
	ulikesLabel->setBuddy(ulikesField);
	ulinkLabel = new QLabel("Trailer: ");
	ulinkField = new QLineEdit();
	ulinkLabel->setBuddy(ulinkField);

	uinputFormLayout->addRow(utitleLabel, utitleField);
	uinputFormLayout->addRow(ugenreLabel, ugenreField);
	uinputFormLayout->addRow(uyearLabel, uyearField);
	uinputFormLayout->addRow(ulikesLabel, ulikesField);
	uinputFormLayout->addRow(ulinkLabel, ulinkField);

	// initialise the possible buttons associated to the forms
	addButton = new QPushButton("Add Movie");
	removeButton = new QPushButton("Remove Movie");
	updateButton = new QPushButton("Update Movie");


	inputSectionLayout->addWidget(inputForm);
	//input form will be added to the inputSection
	inputSectionLayout->addWidget(uinputForm);
	inputSectionLayout->addWidget(addButton);
	inputSectionLayout->addWidget(removeButton);
	inputSectionLayout->addWidget(updateButton);
	// when we select a section, only one of them will be show'ed, the others hide'd

	updateMoviesDB();
}

void AdminGUI::connectSignalsAndSlots() {
	// connect the main buttons with the main menus
	connect(addFormButton, &QPushButton::clicked, this,
	        &AdminGUI::handleAddMovieForm);
	connect(removeFormButton, &QPushButton::clicked, this,
	        &AdminGUI::handleRemoveMovieForm);
	connect(updateFormButton, &QPushButton::clicked, this,
	        &AdminGUI::handleUpdateMovieForm);

	// connect the form buttons with their respective actions that will be reflected in the DB
	connect(addButton, &QPushButton::clicked, this, &AdminGUI::handleAddMovie);
	connect(removeButton, &QPushButton::clicked, this,
	        &AdminGUI::handleRemoveMovie);
	connect(updateButton, &QPushButton::clicked, this,
	        &AdminGUI::handleUpdateMovie);

	connect(undoButton, &QPushButton::clicked, this, &AdminGUI::handleUndo);
	connect(redoButton, &QPushButton::clicked, this, &AdminGUI::handleRedo);

	connect(undoAction, &QAction::triggered, this, &AdminGUI::handleUndo);
	connect(redoAction, &QAction::triggered, this, &AdminGUI::handleRedo);
}

void AdminGUI::handleAddMovieForm() const {
	errorLabel->hide(); //hide any error
	inputButtonsSection->hide(); //hide the up buttons
	inputSection->show(); //show the input section
	uinputForm->hide(); //hide the update input form
	addButton->show(); //show the add button and hide the rest
	removeButton->hide();
	updateButton->hide();
}

void AdminGUI::handleAddMovie() const {
	errorLabel->hide();
	string title = titleField->text().toStdString();
	string genre = genreField->text().toStdString();
	string year = yearField->text().toStdString();
	string likes = likesField->text().toStdString();
	string link = linkField->text().toStdString();
	try {
		// validate the fields (string->numbers works)
		Validator::validate({title, genre, year, likes, link});
		Movie m{title, genre, stoi(year), stoi(likes), link};
		// validate the movie (good format for link, year, likes)
		Validator::validateMovie(m);
		// each of the above validations can throw an exception, or the one when adding below!
		service.addDB(m);
	} catch (exception &e) {
		errorLabel->setText(e.what());
		errorLabel->show();
	}
	// go back, even if there was an error or not
	addButton->hide();
	inputSection->hide();
	inputButtonsSection->show();
	updateMoviesDB();
}

void AdminGUI::handleRemoveMovie() {
	errorLabel->hide();
	string title = titleField->text().toStdString();
	string genre = genreField->text().toStdString();
	string year = yearField->text().toStdString();
	string likes = likesField->text().toStdString();
	string link = linkField->text().toStdString();
	try {
		Validator::validate({title, genre, year, likes, link});
		Movie m{title, genre, stoi(year), stoi(likes), link};
		Validator::validateMovie(m);
		service.removeDB(m);
	} catch (exception &e) {
		errorLabel->setText(e.what());
		errorLabel->show();
	}
	// go back, even if there was an error or not
	removeButton->hide();
	inputSection->hide();
	inputButtonsSection->show();
	updateMoviesDB();
}

void AdminGUI::handleUpdateMovie() {
	errorLabel->hide();
	string title = titleField->text().toStdString();
	string genre = genreField->text().toStdString();
	string year = yearField->text().toStdString();
	string likes = likesField->text().toStdString();
	string link = linkField->text().toStdString();
	string utitle = utitleField->text().toStdString();
	string ugenre = ugenreField->text().toStdString();
	string uyear = uyearField->text().toStdString();
	string ulikes = ulikesField->text().toStdString();
	string ulink = ulinkField->text().toStdString();
	try {
		Validator::validate({title, genre, year, likes, link});
		Movie m{title, genre, stoi(year), stoi(likes), link};
		Validator::validateMovie(m);

		Validator::validate({utitle, ugenre, uyear, ulikes, ulink});
		Movie um{utitle, ugenre, stoi(uyear), stoi(ulikes), ulink};
		Validator::validateMovie(m);

		service.updateDB(m, um);
	} catch (exception &e) {
		errorLabel->setText(e.what());
		errorLabel->show();
	}
	// go back, even if there was an error or not
	updateButton->hide();
	inputSection->hide();
	inputButtonsSection->show();
	updateMoviesDB();
}

void AdminGUI::handleRemoveMovieForm() const {
	errorLabel->hide(); //hide any error
	inputButtonsSection->hide(); //hide the up buttons
	inputSection->show(); //show the input section
	uinputForm->hide(); //hide the update input form
	addButton->hide(); //show the add button and hide the rest
	removeButton->show();
	updateButton->hide();
}

void AdminGUI::handleUpdateMovieForm() const {
	errorLabel->hide(); //hide any error
	inputButtonsSection->hide(); //hide the up buttons
	inputSection->show(); //show the input section
	uinputForm->show(); //hide the update input form
	addButton->hide(); //show the add button and hide the rest
	removeButton->hide();
	updateButton->show();
}

void AdminGUI::updateMoviesDB() const {
	const vector<Movie> &movies = service.getMoviesDB();
	moviesList->clear();
	for (const auto &movie: movies)
		moviesList->addItem(QString::fromStdString(movie.toStr()));
}

void AdminGUI::handleUndo() {
	errorLabel->hide();
	try {
		service.undo();
		updateMoviesDB();
	}
	catch (exception& e) {
		errorLabel->setText(e.what());
		errorLabel->show();
	}
}

void AdminGUI::handleRedo() {
	errorLabel->hide();
	try {
		service.redo();
		updateMoviesDB();
	}
	catch (exception& e) {
		errorLabel->setText(e.what());
		errorLabel->show();
	}
}
