//
// Created by axolotl on 6/5/25.
//

#ifndef MOVIETABLEVIEW_H
#define MOVIETABLEVIEW_H

#include <QtWidgets>

#include "MovieTableModel.h"

class MovieTableView: public QWidget {
Q_OBJECT
private:
	QVBoxLayout* mainLayout;
	QTableView* watchListView;
	MovieTableModel& model;

	void init();
public:
	MovieTableView(MovieTableModel& model, QWidget* parent = nullptr);
	~MovieTableView() override;
};



#endif //MOVIETABLEVIEW_H
