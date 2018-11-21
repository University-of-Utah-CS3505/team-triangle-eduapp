#ifndef QTSFMLBOX2DWIDGET_H
#define QTSFMLBOX2DWIDGET_H
#include "SFML/Graphics.hpp"
#include <QWidget>
#include <Box2D/Box2D.h>


class QTSFMLBOX2DWidget:public QWidget, public sf::RenderWindow, public
{
public:
    QTSFMLBOX2DWidget();
};

#endif // QTSFMLBOX2DWIDGET_H
