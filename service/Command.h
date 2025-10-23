//
// Created by axolotl on 6/3/25.
//

#ifndef COMMAND_H
#define COMMAND_H

#include "ICommand.h"
#include "IRepo.h"
#define ADD 0
#define REMOVE 1
#define UPDATE 2



class AddCommand final : public Command{
protected:
	Movie movie;
	IRepo& repo;
public:
	explicit AddCommand(IRepo& repo, Movie movie); // default value is null for um because it's not necessarily update
	void undo() const override;
	void redo() const override;
	~AddCommand() override;
};

class RemoveCommand final :public Command{
protected:
	Movie movie;
	IRepo& repo;
public:
	RemoveCommand(IRepo& repo, Movie movie); // default value is null for um because it's not necessarily update
	void undo() const override;
	void redo() const override;
	~RemoveCommand() override;
};


class UpdateCommand final : public Command{
protected:
	Movie movie;
	Movie updatedMovie;
	IRepo& repo;

public:
	UpdateCommand(IRepo& repo, Movie movie, Movie updatedMovie); // default value is null for um because it's not necessarily update
	void undo() const override;
	void redo() const override;
	~UpdateCommand() override;
};



#endif //COMMAND_H
