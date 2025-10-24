
#include "RepoSelectorWindow.h"

RepoSelectorWindow::RepoSelectorWindow(QWidget* parent) : QWidget(parent) {
    csvButton = new QRadioButton("CSV file", this);
    jsonButton = new QRadioButton("JSON file", this);
    confirmButton = new QPushButton("Continue", this);
    question = new QLabel("How do you want your artworks to be stored?");
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(question);
    layout->addWidget(csvButton);
    layout->addWidget(jsonButton);
    layout->addWidget(confirmButton);
    setLayout(layout);
    setWindowTitle("Storage Selector");
    csvButton->setChecked(true);

    connect(confirmButton, &QPushButton::clicked, this, &RepoSelectorWindow::onConfirmClicked);
}

void RepoSelectorWindow::onConfirmClicked() {
    repoInterface* repo = nullptr;

    if (csvButton->isChecked()) {
        repo = new CSVrepo("artworks.csv");
        repo->readFile();
    } else if (jsonButton->isChecked()) {
        repo = new JSONrepo("artworks.json");
        repo->readFile();
    } else {
        return; // No option selected
    }

    Service* service = new Service(*repo, opStack);
    MainWindow* mainWin = new MainWindow(*service);
    mainWin->show();
    this->close();
}
