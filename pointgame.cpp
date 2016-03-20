#include "pointgame.h"
#include "ui_widget.h"
#include <QLabel>
#include <QMessageBox>
#include <QAction>
PointGame::PointGame(QWidget *parent) :
    QWidget(parent)
{
    //Window
    setWindowTitle(trUtf8("Szerezd meg hát mind a 4 pontot!"));
    _menu = new QMenuBar();
    //Layout
    _VBoxLayout = new QVBoxLayout(this);
    _upperLayout = new QHBoxLayout();
    _gridLayout = new QGridLayout();
    _menuLayout = new QHBoxLayout();

    PlayerA = new QLabel();
    PlayerB = new QLabel();
    PlayerTurn = new QLabel();

    _gridSizeDialog = new GridSizeDialog();
    //Game
    _size=3;
    newGame();
    //Menu
    createMenus();


    _upperLayout->addWidget(PlayerA);
    _upperLayout->addWidget(PlayerB);
    _upperLayout->addWidget(PlayerTurn);
    _gridLayout->addWidget(PlayerA,1,0);
    _gridLayout->addWidget(PlayerB,1,2);
    _gridLayout->addWidget(PlayerTurn,1,1);

    _VBoxLayout->setMenuBar(_menu);
    _VBoxLayout->addLayout(_menuLayout);
    _VBoxLayout->addLayout(_upperLayout);
    _VBoxLayout->addLayout(_gridLayout);
    setLayout(_VBoxLayout);

}

PointGame::~PointGame()
{
    delete _VBoxLayout;
}

void PointGame::buttonClicked(){
    GridPushButton* senderButton = qobject_cast<GridPushButton*>(sender());
    Coordinate coordinate = senderButton->coordinate();
    if(senderButton->text()=="4") return;
    foreach(GridPushButton* _actButton, buttons){
        if((_actButton->coordinate().x() == coordinate.x() &&
                       (_actButton->coordinate().y() == coordinate.y() ||
                        _actButton->coordinate().y() == coordinate.y()+1 ||
                        _actButton->coordinate().y() == coordinate.y()-1))||
            (_actButton->coordinate().y() == coordinate.y() &&
                       (_actButton->coordinate().x() == coordinate.x() ||
                        _actButton->coordinate().x() == coordinate.x()+1 ||
                        _actButton->coordinate().x() == coordinate.x()-1)))
        {
            int i = _actButton->text().toInt();
            if(i<4){
                QString s = QString::number(i+1);
                _actButton->setText(s);
                if(i+1 == 4){
                    if(player == 0){
                        _actButton->setStyleSheet("background-color: DeepSkyBlue;");
                        _BluePoint +=1;
                        PlayerA->setText("Blue: " + QString::number(_BluePoint));
                    }
                    else{
                        _actButton->setStyleSheet("background-color: red;");
                        _RedPoint +=1;
                        PlayerB->setText("Red: " + QString::number(_RedPoint));

                    }
                }
            }
        }
    }
    player = (player + 1) % 2;
    if(player%2 ==0){
        PlayerTurn->setText("Blue's turn");
        PlayerTurn->setStyleSheet("color: blue");
    }else{
        PlayerTurn->setText("Red's turn");
        PlayerTurn->setStyleSheet("color: red");
    }
    checkGame();
}

void PointGame::createGrid(){
    foreach(GridPushButton* button, buttons)
    {
        _gridLayout->removeWidget(button);
        delete button;
    }
    buttons.clear();


    for(int i=0;i<_size;i++){
        for(int j=0;j<_size;j++){
                GridPushButton* button = new GridPushButton(Coordinate(i, j));
                button->setText("0");
                button->setMinimumHeight(50);
                //button->setMaximumHeight(50);
                button->setMinimumWidth(50);
                //button->setMaximumWidth(50);
                buttons.append(button);
                connect(button, SIGNAL(clicked()),this,SLOT(buttonClicked()));
                _gridLayout->addWidget(button,i+2,j);
        }
    }
}

void PointGame::createMenus(){
    /*
     * MENÜ SOR PUSBUTTONOKKAL
     _newGame = new QPushButton();
    _newGame->setText("NewGame");
    _reSize = new QPushButton();
    _reSize->setText("Resize");
    _exit = new QPushButton();
    _exit->setText("Exit");


    _menuLayout->addWidget(_newGame);
    _menuLayout->addWidget(_reSize);
    _menuLayout->addWidget(_exit);

    connect(_exit,SIGNAL(clicked()),QApplication::instance(),SLOT(quit()));
    connect(_newGame,SIGNAL(clicked()),this,SLOT(newGameButtonClicked()));
    connect(_reSize,SIGNAL(clicked()),_gridSizeDialog,SLOT(exec()));
    connect(_gridSizeDialog, SIGNAL(accepted()), this, SLOT(newGameButtonClicked()));
*/
    //MENÜ SOR QMENU_VEL
    _newMenu = new QAction(_menu);
    _newMenu->setText("New game");

    _resizeMenu = new QAction(_menu);
    _resizeMenu->setText("Resize");

    _exitMenu = new QAction(_menu);
    _exitMenu->setText("Exit");

    _menu->addAction(_newMenu);
    _menu->addAction(_resizeMenu);
    //_menu->addMenu(_reSizeMenu);
    _menu->addAction(_exitMenu);

    /*
     * _reSizeMenu = new QMenu();
    _reSizeMenu->setTitle("Resize");

    _3x3 = new QAction(_menu);
    _5x5 = new QAction(_menu);
    _7x7 = new QAction(_menu);

    _3x3->setText("3x3");
    _3x3->setCheckable(true);
    _5x5->setText("5x5");
    _5x5->setCheckable(true);
    _7x7->setText("7x7");
    _7x7->setCheckable(true);

    _sizesMenu = new QActionGroup(_menu);
    _sizesMenu->addAction(_3x3);
    _sizesMenu->addAction(_5x5);
    _sizesMenu->addAction(_7x7);

    _reSizeMenu->addAction(_3x3);
    _reSizeMenu->addAction(_5x5);
    _reSizeMenu->addAction(_7x7);
    */
    connect(_newMenu,SIGNAL(triggered()),this,SLOT(newGameButtonClicked()));
    connect(_resizeMenu,SIGNAL(triggered()),_gridSizeDialog,SLOT(exec()));
    connect(_gridSizeDialog, SIGNAL(accepted()), this, SLOT(resizeAccepted()));
    connect(_exitMenu,SIGNAL(triggered()),QApplication::instance(),SLOT(quit()));


}
void PointGame::resizeAccepted(){
    _size=_gridSizeDialog->gridSize();
    newGame();
}
void PointGame::resizeCancelled(){

}


void PointGame::newGame(){
    setBaseSize(300,300);
    player = 0;
    _BluePoint = 0;
    _RedPoint = 0;
    PlayerA->setText("Blue: " + QString::number(_BluePoint));
    PlayerB->setText("Red: " + QString::number(_RedPoint));
    PlayerTurn->setText("Blue's turn");
    PlayerTurn->setStyleSheet("color: blue");

    createGrid();
}

void PointGame::newGameButtonClicked(){
    newGame();
}
void PointGame::checkGame(){
    int db=0;
    foreach(GridPushButton* button, buttons){
        if(button->text()=="4") db++;
    }
    if(db == _gridSizeDialog->gridSize()*_gridSizeDialog->gridSize()){
        if(_BluePoint > _RedPoint){
            QMessageBox::information(this, trUtf8("Game over!"), trUtf8("Blue player won!"));
            newGame();
        }else{
            QMessageBox::information(this, trUtf8("Game over!"), trUtf8("Red player won!"));
            newGame();
        }
    }
}
