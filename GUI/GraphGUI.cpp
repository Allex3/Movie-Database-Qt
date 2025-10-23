//
// Created by axolotl on 6/4/25.
//

#include "GraphGUI.h"

GraphGUI::GraphGUI(QWidget *parent, Service &service): QWidget(parent, Qt::Window), service(service) {
	setAttribute(Qt::WA_DeleteOnClose);
	init();
}

void GraphGUI::init() {
	const auto screen = QApplication::primaryScreen();
	const auto rect = screen->geometry();
	int height = 500;
	int width = 800;
	this->setGeometry(rect.width()/2-300, rect.height()/2-300, width, height);
	QApplication::setFont(QFont("Verdana", 11));

	auto& movies = service.getMoviesDB();

	vector<string> genresv;
	for (auto& movie: movies)
		genresv.push_back(movie.getGenre());
	const set<string> genres(genresv.begin(), genresv.end());

	vector<QBarSet*> sets;
	series = new QBarSeries{};
	for (string genre: genres) {
		sets.emplace_back(new QBarSet(genre.data()));
		*(sets.back()) << service.getMoviesGenre(genre).size(); //number of movies with this genre for the bar height
		series->append(sets.back()); //append the current genre data to the series
	}

	chart = new QChart;
	chart->addSeries(series);
	chart->setTitle("Genre Statistics");

	// create the "category" which is just "genre", put below the Ox axis
	axisX = new QBarCategoryAxis;
	axisX->append(QString::fromStdString("Genre"));
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	// y-axis with number values
	axisY = new QValueAxis;
	axisY->setRange(0, 10);
	chart->addAxis(axisY, Qt::AlignLeft); //left oriented basis
	series->attachAxis(axisY);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	chart->setAnimationOptions(QChart::SeriesAnimations);


	chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->show();

	mainLayout = new QHBoxLayout{this};
	mainLayout->addWidget(chartView);
}

GraphGUI::~GraphGUI() {
	delete &service;
	parentWidget()->show();
}
