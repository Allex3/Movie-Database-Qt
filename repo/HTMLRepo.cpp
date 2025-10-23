//
// Created by Alex on 03.05.2025.
//

#include "HTMLRepo.h"

#include <utility>
#include <fstream>

HTMLRepo::HTMLRepo(vector<Movie>& moviesWL,
	vector<Movie>& moviesDB, string fileWL, string fileDB, string fileHTML): DefaultRepo(moviesWL, moviesDB, std::move(fileWL), std::move(fileDB)), fileHTML(std::move(fileHTML)) {

}

void HTMLRepo::writeToFileWL() const {
	DefaultRepo::writeToFileWL();
	ofstream f{fileHTML};

	f << "<!DOCTYPE html>\n";
	f << "<html>\n";
	f << "<head>\n";
	f << "<title>Movie Watch List</title>\n";
	f << "</head>\n";

	f << "<body>\n";
	f << "<table border=\"1\">\n";
	f << "<tr>\n<td>Title</td>\n<td>Genre</td>\n<td>Year of release</td>\n<td>Likes</td>\n<td>Trailer</td>\n</tr>\n";

	for (auto &movie: moviesWL) {
		f << "<tr>\n";
		f << "<td>" << movie.getTitle() << "</td>\n";
		f << "<td>" << movie.getGenre() << "</td>\n";
		f << "<td>" << movie.getYear() << "</td>\n";
		f << "<td>" << movie.getLikes() << "</td>\n";
		f << "<td><a href=\"" << movie.getTrailer() << "\">Link</a></td>\n";
		f<<"</tr>\n";
	}

	f<< "</table>\n</body>\n</html>";

	f.close();
}

