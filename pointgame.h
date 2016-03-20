#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "gridpushbutton.h"
#include "gridsizedialog.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QActionGroup>


class PointGame : public QWidget
{
    Q_OBJECT

public:
    explicit PointGame(QWidget *parent = 0);
    ~PointGame();
private slots:
    void buttonClicked();
    void newGameButtonClicked();
    void resizeAccepted();
    void resizeCancelled();
private:
    QVector<GridPushButton*> buttons;
    QMenuBar *_menu;
    QAction *_newMenu;
    QAction *_resizeMenu;
    //QMenu *_reSizeMenu;
    int _size;
    QActionGroup *_sizesMenu;
    QAction *_3x3;
    QAction *_5x5;
    QAction *_7x7;
    QAction *_exitMenu;
    QGridLayout* _gridLayout;
    QVBoxLayout* _VBoxLayout;
    QHBoxLayout* _upperLayout;
    QHBoxLayout* _menuLayout;
    QPushButton* _newGame;
    QPushButton* _reSize;
    QPushButton* _exit;
    GridSizeDialog* _gridSizeDialog;
    QLabel *PlayerTurn;
    QLabel *PlayerA;
    QLabel *PlayerB;
    int player;
    int _BluePoint;
    int _RedPoint;

    void createMenus();
    void createGrid();
    void checkGame();
    void newGame();

};

#endif // WIDGET_H
