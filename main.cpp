//
// Created by Alex on 23.03.2025.
//

#include "CSVRepo.h"
#include "HTMLRepo.h"
#include "GUI/mainGUI.h"
#include <QtWidgets/QApplication>
#include "tests.h"
#include "UI/UI.h"

void runTests() {
	Tests::testMovie();
	Tests::testAddDB();
	Tests::testRemoveDB();
	Tests::testUpdateDB();
	Tests::testAddWL();
	Tests::testRemoveWL();
	Tests::testGetMovies();
}

/*
 std::pair<IRepo*, string> chooseMode() {
	IRepo* repo;
	while (true) {
		cout << "Choose between (1) HTML and (2) CSV to see the watch list when you want to see it. Or (0) to exit the program.\n";
		char option;
		cout << "Option: ";
		std::cin >> option;
		switch (option) {
			case '1':
				repo = new HTMLRepo{"../usermovies.txt", "../movies.txt", "../user.html"};
				return {repo, "HTML"};
			case '2':
				repo = new CSVRepo{"../usermovies.txt", "../movies.txt", "../user.csv"};
				return {repo, "CSV"};
			case '0':
				exit(0);
			default:
				std::cout << "Your option should be 1 or 2 or 0.\n";
		}
	}
}
*/
int main(int argc, char** argv) {
	runTests();


	/*
	std::pair<IRepo*, string> p = chooseMode();

	auto *s = new Service{*(p.first)};
	const auto *ui = new UI{*s, p.second};
	ui->chooseMenu();

	delete ui;
	*/
	QApplication app{argc, argv};


	MainGUI mainGUI{};
	mainGUI.show();

	return app.exec();

}
