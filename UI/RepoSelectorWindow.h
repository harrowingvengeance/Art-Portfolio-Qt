
#ifndef REPOSELECTORWINDOW_H
#define REPOSELECTORWINDOW_H

#include <QWidget>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include "../operations/operationStack.h"
#include "../service/service.h"
#include "../repository/CSVrepo.h"
#include "../repository/JSONrepo.h"
#include "MainWindow.h"

class RepoSelectorWindow : public QWidget {
    Q_OBJECT

private:
    QRadioButton* csvButton;
    QRadioButton* jsonButton;
    QPushButton* confirmButton;
    QLabel* question;

    operationStack opStack;

public:
    explicit RepoSelectorWindow(QWidget* parent = nullptr);

private slots:
    void onConfirmClicked();
};

#endif // REPOSELECTORWINDOW_H
