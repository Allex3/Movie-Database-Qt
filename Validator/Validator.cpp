//
// Created by Alex on 08.05.2025.
//

#include "Validator.h"


void Validator::validateMovie(Movie& m) {
	string errors;
	if (m.getLikes() < 0)
		errors += "Likes should be an integer > 0\n";
	// !(a or b) = !a and !b
	if (!(m.getTrailer()[0] == 'w' && m.getTrailer()[1] == 'w' && m.getTrailer()[2] == 'w') &&
		!(m.getTrailer()[0] == 'h' && m.getTrailer()[1] == 't' && m.getTrailer()[2] == 't' && m.getTrailer()[3] == 'p'))
		errors +="The trailer should start with www or http\n";

	if (!errors.empty())
		throw ValidatorException(errors);

}

void Validator::validate(const vector<string>& dataPoints) {
	string errors;

	std::string::const_iterator it = dataPoints[2].begin();
	while (it != dataPoints[2].end() && isdigit(*it)) ++it;
	if (it != dataPoints[2].end() || dataPoints[2].empty()) //not a number, found a digit
		errors+= "The year should be a number (2000-3000)";

	it = dataPoints[3].begin();
	while (it != dataPoints[3].end() && isdigit(*it)) ++it;
	if (it != dataPoints[3].end() || dataPoints[3].empty()) //not a number, found a digit
		errors += "The likes should be a number bigger than zero";

	if (!errors.empty()) //errors regarding the numbers (cannot run stoi)
		throw ValidatorException(errors);

	int likes = stoi(dataPoints[3]);
	int year = stoi(dataPoints[2]);

	if (! (2000<=year && year <= 3000))
		errors+= "The year should be between 2000-3000.";

	if (likes < 0)
		errors += "Likes should be an integer > 0\n";

	if (!errors.empty())
		throw ValidatorException(errors);

}