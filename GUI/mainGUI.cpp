//
// Created by Alex on 18.05.2025.
//

#include "CSVRepo.h"
#include "HTMLRepo.h"
#include "mainGUI.h"

#include "MovieTableView.h"

MainGUI::MainGUI(QWidget *parent): QWidget(parent),
                                   moviesDB(*new vector<Movie>),
                                   moviesWL(*new vector<Movie>) {
	repo = new DefaultRepo(moviesWL, moviesDB, "../usermovies.txt", "../movies.txt");
	watchListModel = new MovieTableModel{moviesWL};
	init();
	connectSignalsAndSlots();
}

MainGUI::~MainGUI() {
	delete repo;
}

void MainGUI::init() {
	this->setWindowTitle("Movie Database Main Menu");

	const auto screen = QApplication::primaryScreen();
	const auto rect = screen->geometry();
	int height = 100;
	int width = 150;
	this->setGeometry(rect.width() / 2 - 200, rect.height() / 2 - 100, width,
	                  height);
	QApplication::setFont(QFont("Verdana", 11));

	layout = new QVBoxLayout(this); //this->setLayout(layout)

	choice = new QLabel(
		"Choose in what format to display the user watch list (HTML/CSV)");
	HTMLChoice = new QRadioButton("HTML");
	HTMLChoice->setChecked(true);
	CSVChoice = new QRadioButton("CSV");
	adminButton = new QPushButton("Admin Menu");
	userButton = new QPushButton("User Menu");
	chartButton = new QPushButton("Genre Chart");
	showWatchListButton = new QPushButton{"Show watchlist"};

	layout->addWidget(choice);
	layout->addWidget(HTMLChoice);
	layout->addWidget(CSVChoice);
	layout->addWidget(adminButton);
	layout->addWidget(userButton);
	layout->addWidget(chartButton);
	layout->addWidget(showWatchListButton);

	this->setLayout(layout);
}

void MainGUI::connectSignalsAndSlots() {
	connect(adminButton, &QPushButton::clicked, this, &MainGUI::initAdminGUI);
	connect(userButton, &QPushButton::clicked, this, &MainGUI::initUserGUI);
	connect(HTMLChoice, &QPushButton::clicked, this,
	        &MainGUI::handleHTMLChoice);
	connect(CSVChoice, &QPushButton::clicked, this, &MainGUI::handleCSVChoice);
	connect(chartButton, &QPushButton::clicked, this, &MainGUI::handleChart);
	connect(showWatchListButton, &QPushButton::clicked, this,
	        &MainGUI::handleWL);
}

void MainGUI::handleHTMLChoice() {
	isHTML = true;
}

void MainGUI::handleCSVChoice() {
	isHTML = false;
}

void MainGUI::handleWL() {
	repo = new DefaultRepo{
		moviesWL, moviesDB,
		"../usermovies.txt", "../movies.txt"
	};
	// update the model ..

	auto *WLView = new MovieTableView{*watchListModel, this};
	WLView->show();
	this->hide();
}


// genre chart
void MainGUI::handleChart() {
	repo = new DefaultRepo{
		moviesWL, moviesDB, "../usermovies.txt", "../movies.txt"
	};
	auto *service = new Service{*repo};

	graphGUI = new GraphGUI{this, *service};
	graphGUI->show();
	this->hide();
}

void MainGUI::initAdminGUI() {
	repo = new DefaultRepo{
		moviesWL, moviesDB, "../usermovies.txt", "../movies.txt"
	};
	auto *service = new Service{*repo};

	adminGUI = new AdminGUI{*service, this};
	adminGUI->show();
	this->hide();
}

void MainGUI::initUserGUI() {
	if (isHTML)
		repo = new HTMLRepo{
			moviesWL, moviesDB, "../usermovies.txt", "../movies.txt",
			"../user.html"
		};
	else
		repo = new CSVRepo{
			moviesWL, moviesDB, "../usermovies.txt", "../movies.txt",
			"../user.csv"
		};

	auto *service = new Service{*repo};

	userGUI = new UserGUI{*service, *watchListModel, this, isHTML};
	userGUI->show();
	this->hide();
}
