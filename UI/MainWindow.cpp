
#include "MainWindow.h"
#include "../UI/MainWindow.h"
#include "../service/filter.h"
#include <QMessageBox>
#include "../exceptions/exception.h"
#include "../validator/ArtworkValidator.h"
#include <QPalette>

MainWindow::MainWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setupUI();
    connectSignalsAndSlots();
    refreshTable(service.returnContentsOfDatabase());
}

void MainWindow::setupUI() {
    artworkTable = new QTableWidget(this);
    artworkTable->setColumnCount(5);
    artworkTable->setHorizontalHeaderLabels({ "Title", "Medium", "Technique", "Width", "Height" });
    artworkTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->errorLabel = new QLabel{"This shouldn't be seen!"};
    titleEdit = new QLineEdit(this);
    mediumEdit = new QLineEdit(this);
    techniqueEdit = new QLineEdit(this);
    widthEdit = new QLineEdit(this);
    heightEdit = new QLineEdit(this);

    filterMediumEdit = new QLineEdit(this);
    filterTechniqueEdit = new QLineEdit(this);

    addButton = new QPushButton("Add", this);
    removeButton = new QPushButton("Remove", this);
    updateButton = new QPushButton("Update", this);
    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);
    filterButton = new QPushButton("Filter", this);

    errorUndoLabel = new QLabel;
    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Title:", titleEdit);
    formLayout->addRow("Medium:", mediumEdit);
    formLayout->addRow("Technique:", techniqueEdit);
    formLayout->addRow("Width:", widthEdit);
    formLayout->addRow("Height:", heightEdit);

    QFormLayout* filterLayout = new QFormLayout;
    filterLayout->addRow("Medium filter:", filterMediumEdit);
    filterLayout->addRow("Technique filter:", filterTechniqueEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);
    buttonLayout->addWidget(filterButton);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(artworkTable);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(errorLabel);
    mainLayout->addWidget(errorUndoLabel);
    errorUndoLabel->hide();

    errorPalette.setColor(QPalette::WindowText, Qt::red);
    errorLabel->setPalette(errorPalette);
    errorUndoLabel->setPalette(errorPalette);
    this->errorLabel->hide();
    mainLayout->setAlignment(this->errorLabel, Qt::AlignCenter);
    mainLayout->setAlignment(this->errorUndoLabel, Qt::AlignCenter);

    setLayout(mainLayout);
    setWindowTitle("Art Portfolio Catalog");
}

void MainWindow::connectSignalsAndSlots() {
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateClicked);
    connect(undoButton, &QPushButton::clicked, this, &MainWindow::onUndoClicked);
    connect(redoButton, &QPushButton::clicked, this, &MainWindow::onRedoClicked);
    connect(filterButton, &QPushButton::clicked, this, &MainWindow::onFilterClicked);
}

void MainWindow::refreshTable(const std::vector<Artwork>& artworks) {
    artworkTable->setRowCount(artworks.size());
    for (int row = 0; row < artworks.size(); ++row) {
        const auto& a = artworks[row];
        artworkTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(a.getTitle())));
        artworkTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getMedium())));
        artworkTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getTechnique())));
        artworkTable->setItem(row, 3, new QTableWidgetItem(QString::number(a.getDimension().first)));
        artworkTable->setItem(row, 4, new QTableWidgetItem(QString::number(a.getDimension().second)));
    }
}


void MainWindow::onAddClicked() {
    const string title = this->titleEdit->text().toStdString();
    const string medium = this->mediumEdit->text().toStdString();
    const string technique = this->techniqueEdit->text().toStdString();
    const string width = this->widthEdit->text().toStdString();
    const string height = this->heightEdit->text().toStdString();
    vector dataPoints{title, medium, technique, width, height};
    try {
        ArtworkValidator::validateDataPoints(dataPoints);
        const aDimension dimension{std::stoi(width), std::stoi(height)};
        const Artwork newArtwork{titleEdit->text().toStdString(),mediumEdit->text().toStdString(),techniqueEdit->text().toStdString(),dimension};
        service.addArtwork(newArtwork);
        refreshTable(service.returnContentsOfDatabase());
        this->errorLabel->hide();
        this->errorUndoLabel->hide();
    } catch (ArtworkValidationException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }catch (ArtworkWithSameAttributesException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }
}

void MainWindow::onRemoveClicked() {
    const string title = this->titleEdit->text().toStdString();
    const string medium = this->mediumEdit->text().toStdString();
    const string technique = this->techniqueEdit->text().toStdString();
    const string width = this->widthEdit->text().toStdString();
    const string height = this->heightEdit->text().toStdString();
    vector dataPoints{title, medium, technique, width, height};
    try {
        ArtworkValidator::validateDataPoints(dataPoints);
        const aDimension dimension{std::stoi(width), std::stoi(height)};
        const Artwork newArtwork{titleEdit->text().toStdString(),mediumEdit->text().toStdString(),techniqueEdit->text().toStdString(),dimension};
        service.removeArtwork(newArtwork);
        refreshTable(service.returnContentsOfDatabase());
        this->errorLabel->hide();
        this->errorUndoLabel->hide();
    }catch (ArtworkValidationException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }catch (ArtworkNotFoundException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }
}



void MainWindow::onUpdateClicked() {
    const string title = this->titleEdit->text().toStdString();
    const string medium = this->mediumEdit->text().toStdString();
    const string technique = this->techniqueEdit->text().toStdString();
    const string width = this->widthEdit->text().toStdString();
    const string height = this->heightEdit->text().toStdString();
    vector dataPoints{title, medium, technique, width, height};
    try {
        ArtworkValidator::validateDataPoints(dataPoints);
        const aDimension dimension ={std::stoi(widthEdit->text().toStdString()), std::stoi(heightEdit->text().toStdString())};
        const Artwork newArtwork{titleEdit->text().toStdString(),mediumEdit->text().toStdString(),techniqueEdit->text().toStdString(),dimension};
        service.updateArtwork(newArtwork, newArtwork);
        refreshTable(service.returnContentsOfDatabase());


    } catch (ArtworkValidationException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    } catch (ArtworkNotFoundException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }


}

void MainWindow::onUndoClicked() {
    try {
            service.undoOperation();
            refreshTable(service.returnContentsOfDatabase());
            errorUndoLabel->hide();
    } catch (const UndoRedoException& excep) {
        this->errorUndoLabel->setText(QString::fromStdString(excep.what()));
        this->errorUndoLabel->show();
    }
}

void MainWindow::onRedoClicked() {
    try {
            service.redoOperation();
            refreshTable(service.returnContentsOfDatabase());
    } catch (const UndoRedoException& excep) {
        this->errorUndoLabel->setText(QString::fromStdString(excep.what()));
        this->errorUndoLabel->show();
    }
}

void MainWindow::onFilterClicked() {

            std::vector<std::shared_ptr<Filter>> filters;
            if (!filterMediumEdit->text().isEmpty()) {
                filters.push_back(std::make_shared<FilterByMedium>(filterMediumEdit->text().toStdString()));
            }
            refreshTable(service.filter(filters));

             if (!filterTechniqueEdit->text().isEmpty()) {
             filters.push_back(std::make_shared<FilterByTechnique>(filterTechniqueEdit->text().toStdString()));
             }
            refreshTable(service.filter(filters));

}


