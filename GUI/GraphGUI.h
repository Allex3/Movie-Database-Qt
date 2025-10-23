//
// Created by axolotl on 6/4/25.
//

#ifndef GRAPHGUI_H
#define GRAPHGUI_H

#include <QtWidgets>
#include <QtCharts>

#include "Service.h"

class GraphGUI final : public QWidget{
	Q_OBJECT
public:
	GraphGUI(QWidget* parent, Service& service);
private:
	Service& service;

	QChart* chart;
	QBarSeries* series;
	QValueAxis* axisY;
	QBarCategoryAxis* axisX;
	QChartView* chartView; //the chart view to be shown
	QHBoxLayout* mainLayout;

	void init();
	~GraphGUI();

};



#endif //GRAPHGUI_H
