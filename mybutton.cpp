#include "mybutton.h"
#include <iostream>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{
}

MyButton::~MyButton()
{
}

void MyButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        emit rightClicked();
    if (event->button() == Qt::LeftButton)
        emit leftClicked();
    if (event->button() == Qt::MiddleButton)
        emit doubleClicked();
}

void MyButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit doubleClicked();
}

