//
// Created by Alex on 18.05.2025.
//

#ifndef ADMINGUI_H
#define ADMINGUI_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QFormLayout>

#include "Validator.h"

#include "Service.h"

class AdminGUI final : public QWidget {
	Q_OBJECT

public:
	explicit AdminGUI(Service &service, QWidget *parent = nullptr);

	~AdminGUI() override;

private:
	Service &service;

	QVBoxLayout *mainLayout; //main layout that holds the admin menu

	QLabel *errorLabel;

	QPushButton *addFormButton;
	QPushButton *removeFormButton;
	QPushButton *updateFormButton;
	QWidget *inputButtonsSection;
	QHBoxLayout *inputButtonsLayout; //layout of the buttons

	// the update section and layout, that's before the listwidget
	QWidget *undoRedoSection;
	QHBoxLayout* undoRedoSectionLayout;
	QPushButton *undoButton;
	QPushButton *redoButton;

	QAction* undoAction;
	QAction* redoAction;

	QListWidget *moviesList; //the list of the movies

	// this will show up when we press a button from the inputButtons widget
	QWidget *inputSection; //a widget representing the input section
	// the inputForm on the left, and the button on the right
	// and they will be in an HBoxlayout
	QHBoxLayout *inputSectionLayout;

	QFormLayout *inputFormLayout;
	QWidget *inputForm;
	//the widget which contains the form for the input of a Movie


	QLineEdit *titleField;
	QLabel *titleLabel;
	QLineEdit *genreField;
	QLabel *genreLabel;
	QLineEdit *likesField;
	QLabel *likesLabel;
	QLineEdit *yearField;
	QLabel *yearLabel;
	QLineEdit *linkField;
	QLabel *linkLabel;

	QFormLayout *uinputFormLayout;
	QWidget *uinputForm;

	QLineEdit *utitleField;
	QLabel *utitleLabel;
	QLineEdit *ugenreField;
	QLabel *ugenreLabel;
	QLineEdit *ulikesField;
	QLabel *ulikesLabel;
	QLineEdit *uyearField;
	QLabel *uyearLabel;
	QLineEdit *ulinkField;
	QLabel *ulinkLabel;

	// one of these buttons will be on the right
	QPushButton *addButton;
	QPushButton *removeButton;
	QPushButton *updateButton;

	void init();

	void connectSignalsAndSlots();

	void handleAddMovieForm() const;

	void handleAddMovie() const;

	void handleRemoveMovieForm() const;

	void handleRemoveMovie();

	void handleUpdateMovieForm() const;

	void handleUpdateMovie();

	void updateMoviesDB() const;

	void handleUndo();

	void handleRedo();
};


#endif //ADMINGUI_H
