#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QtWidgets>


class StartWindow : public QDialog
{
public:
     StartWindow(QWidget *parent = 0);
    ~StartWindow();

    QRadioButton *easy, *medium, *hard;
    QPushButton *start, *exit;
    QVBoxLayout *levelsOfComplexity, *full;
    QHBoxLayout *buttons;

    QIcon windowIcon;

public slots:
    void unlockingButton();
    int clicked_start();
    bool clicked_exit();
};

#endif // STARTWINDOW_H
