#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QDialog>
#include <QtWidgets>


class EndWindow : public QDialog
{
public:
    explicit EndWindow(QWidget *parent = 0);
    ~EndWindow();

    QPushButton *newGame, *exit;
    QLabel *lbl;
    QHBoxLayout *down;
    QVBoxLayout *full;

    void win_lbl();
    void lose_lbl();

    QIcon windowIcon;

public slots:
    void clicked_exit();
    bool clicked_newGame();
};

#endif // ENDWINDOW_H
