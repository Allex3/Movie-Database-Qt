//
// Created by axolotl on 6/5/25.
//

#include "MovieTableView.h"

void MovieTableView::init() {
	setGeometry(300, 300, 800, 400);
	mainLayout = new QVBoxLayout(this);
	watchListView = new QTableView{};
	watchListView->setModel(&model);
	mainLayout->addWidget(watchListView);
}

MovieTableView::MovieTableView(MovieTableModel &model, QWidget *parent):
model(model), QWidget(parent, Qt::Window){
	this->setAttribute(Qt::WA_DeleteOnClose);
	init();
}

MovieTableView::~MovieTableView() {
	parentWidget()->show();
}
