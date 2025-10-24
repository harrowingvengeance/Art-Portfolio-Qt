
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "../service/service.h"
#include <QHeaderView>
#include <QLabel>
class MainWindow : public QWidget {
    Q_OBJECT

private:
    Service& service;

    QTableWidget* artworkTable;
    QLineEdit* titleEdit;
    QLineEdit* mediumEdit;
    QLineEdit* techniqueEdit;
    QLineEdit* widthEdit;
    QLineEdit* heightEdit;

    QLineEdit* filterMediumEdit;
    QLineEdit* filterTechniqueEdit;

    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QLabel* errorLabel;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QLabel *errorUndoLabel;
    QPushButton* filterButton;

    QPalette errorPalette;
    void setupUI();
    void connectSignalsAndSlots();
    void refreshTable(const std::vector<Artwork>& artworks);

private slots:
    void onAddClicked();
    void onRemoveClicked();
    void onUpdateClicked();
    void onUndoClicked();
    void onRedoClicked();
    void onFilterClicked();

public:
    explicit MainWindow(Service& service, QWidget* parent = nullptr);
};

#endif // MAINWINDOW_H
