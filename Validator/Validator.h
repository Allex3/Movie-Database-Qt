//
// Created by Alex on 08.05.2025.
//

#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <utility>

#include "DefaultRepo.h"

class ValidatorException final: public exception {
private:
	string m;
public:
	explicit ValidatorException(string m): m(std::move(m)){}
	[[nodiscard]] const char* what() const noexcept override {
		return m.c_str();
	}
};

class Validator {
public:
	Validator() = default;

	// validate a movie given by its data points (fields) in GUI
	static void validate(const vector<string> &dataPoints);

	// validate a movie already created, with the "being numbers" already handled in the istream >> operator
	// (for console UI)
	static void validateMovie(Movie& m);
};



#endif //VALIDATOR_H
