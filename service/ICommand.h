//
// Created by axolotl on 6/3/25.
//

#ifndef ICOMMAND_H
#define ICOMMAND_H



class  Command {
public:
	virtual ~Command() = default;

	virtual void undo() const = 0;
	virtual void redo() const = 0;

};



#endif //ICOMMAND_H
