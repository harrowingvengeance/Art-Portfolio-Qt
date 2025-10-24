
#include <QApplication>
#include "UI/RepoSelectorWindow.h"
#include "tests/tests.h"
int main(int argc, char *argv[]) {
    // Tests::testRepo();
    // Tests::testServiceUndoRedo();
    // Tests::testFiltering();

    QApplication app(argc, argv);

    RepoSelectorWindow selector;
    selector.show();

    return app.exec();
}
