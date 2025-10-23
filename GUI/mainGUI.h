//
// Created by Alex on 18.05.2025.
//

#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts>

#include "Service.h"
#include "adminGUI.h"
#include "userGUI.h"
#include "GraphGUI.h"
#include "MovieTableModel.h"


class MainGUI final : public QWidget {
	Q_OBJECT
public:
	explicit MainGUI(QWidget* parent = nullptr);
	~MainGUI() override;
private:

	IRepo* repo;
	vector<Movie>& moviesDB;
	vector<Movie>& moviesWL;

	QVBoxLayout* layout;

	QLabel* choice;

	AdminGUI* adminGUI;
	UserGUI* userGUI;

	QRadioButton* HTMLChoice;
	QRadioButton* CSVChoice;
	QPushButton* adminButton;
	QPushButton* userButton;
	QPushButton* chartButton;
	QPushButton* showWatchListButton;

	MovieTableModel* watchListModel;


	GraphGUI* graphGUI;

	bool isHTML = true;

	void init();
	void connectSignalsAndSlots();
	void handleHTMLChoice();
	void handleCSVChoice();
	void handleWL();
	void handleChart();
	void initAdminGUI();
	void initUserGUI();

};



#endif //MAINGUI_H
