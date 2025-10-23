//
// Created by axolotl on 6/4/25.
//

#include "MovieTableModel.h"

MovieTableModel::MovieTableModel(vector<Movie> &movies,
                                 QObject *parent): QAbstractTableModel(parent),
                                                   movies(movies) {
}

MovieTableModel::MovieTableModel(const MovieTableModel &otherModel): movies(
	otherModel.getWatchList()) {
}

vector<Movie> &MovieTableModel::getWatchList() const {
	return movies;
}

void MovieTableModel::addNewItem(Movie newMovie) {
	// since we are using model/view programming, having a reference to a vector of our movies here

	movies.push_back(newMovie);
	const int row = rowCount(QModelIndex()) - 1;

	setData(index(row, 0), QVariant(QString::fromStdString(newMovie.getTitle())));
	setData(index(row, 1), QVariant(QString::fromStdString(newMovie.getGenre())));
	QString year = QString::number(newMovie.getYear());
	setData(index(row, 2), QVariant(year));
	QString likes = QString::number(newMovie.getLikes());
	setData(index(row, 3), QVariant(likes));
	setData(index(row, 4), QVariant(QString::fromStdString(newMovie.getTrailer())));
}

int MovieTableModel::rowCount(const QModelIndex &parent) const {
	return movies.size(); //there are as many rows as movies
}

int MovieTableModel::columnCount(const QModelIndex &parent) const {
	return 5; //always 5 fields for a movie
}

QVariant MovieTableModel::data(const QModelIndex &index, int role) const {
	int row = index.row();
	int column = index.column();

	if (role != Qt::DisplayRole)
		return QVariant();

	switch (column) {
		case 0: {
			string title = movies[row].getTitle();
			return QString::fromStdString(title);
		}
		case 1: {
			string genre = movies[row].getGenre();
			return QString::fromStdString(genre);
		}
		case 2: {
			return QString::number(movies[row].getYear());
		}
		case 3: {
			return QString::number(movies[row].getLikes());
		}
		case 4: {
			string link = movies[row].getTrailer();
			return QString::fromStdString(link);
		}
	}


	return QVariant();
}

bool MovieTableModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
	if (role != Qt::EditRole)
		return false;

	if (!checkIndex(index))
		return false;


	emit dataChanged(index, index);
	return true;
}

QVariant MovieTableModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return QVariant();

	switch (section) {
		case 0:
			return QString("Title");
		case 1:
			return QString("Genre");
		case 2:
			return QString("Year of release");
		case 3:
			return QString("Likes");
		case 4:
			return QString("Trailer");
	}


}
