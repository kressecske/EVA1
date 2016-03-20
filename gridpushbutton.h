#ifndef COORDINATEPUSHBUTTON_H
#define COORDINATEPUSHBUTTON_H

#include <QPushButton>
#include "coordinate.h"

class GridPushButton : public QPushButton
   // a rácsba helyezendő nyomógomb típusa, amely rendelkezik koordinátával
{
    Q_OBJECT
public:
    explicit GridPushButton(Coordinate coordinate, QWidget *parent = 0);
    Coordinate coordinate() const { return _coordinate; }

protected:
    Coordinate _coordinate;
};

#endif // COORDINATEPUSHBUTTON_H
