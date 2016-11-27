#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenu>
#include "headerwrapper.h"
#include "ai.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void bindAIToUI(AI *, MainWindow *);

private:
    Ui::MainWindow *ui;
//    QAction *actionWithName(const char *);
    void createMenuWithNameAndActions(const char *, QList<QAction *>);

    QMenu *gameOptionsMenu;
    QMenu *moreOptionsMenu;
    QActionGroup *alignmentGroupOfGame;
    QActionGroup *alignmentGroupOfMore;
    QAction *newGameAct;
    QAction *restartAct;
    QAction *preferencesAct;
    QAction *aboutAct;

signals:
    void newWindowPopped();

public slots:
    void openAboutPage();
    void openPreferencesPage();
//    void sendNewGameSignal();
    void showWinningResults();
    void showFailure();
    void refreshUI();
//    void newGame();
//    void restart();

protected:
//    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // MAINWINDOW_H
