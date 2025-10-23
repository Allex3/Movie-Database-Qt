//
// Created by axolotl on 6/4/25.
//

#ifndef MOVIETABLEMODEL_H
#define MOVIETABLEMODEL_H
#include <QAbstractTableModel>

#include "Movie.h"
#include <vector>
using std::vector;

class MovieTableModel final : public QAbstractTableModel {
	Q_OBJECT
private:
	vector<Movie>& movies;
public:
	explicit MovieTableModel(vector<Movie>& movies, QObject* parent = nullptr);

	MovieTableModel(const MovieTableModel& otherModel);
	vector<Movie>& getWatchList() const;
	void addNewItem(Movie newMovie);

	int rowCount(const QModelIndex &parent) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};



#endif //MOVIETABLEMODEL_H
