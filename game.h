#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "startwindow.h"
#include "mybutton.h"
#include "endwindow.h"
#include "settingswindow.h"
#include <QMainWindow>
#include <QtWidgets>
#include <qsizepolicy.h>
#include <QMouseEvent>

extern int sizeField;
extern int countMines;

class Game : public QMainWindow
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);
    ~Game();
private:
    QSizePolicy *policy;

    StartWindow *startWindow;
    EndWindow *endWindow;
    SettingsWindow *settingsWindow;
    MyButton **buttons;
    QWidget *widget;
    QMenu *menu_file, *menu_help;
    QAction *menu_file_newGame, *menu_file_settings;
    QLineEdit *le_timer, *le_countOfMines;
    QLabel *lbl_timer, *lbl_countOfMines;
    QTimer *timer;
    int **mines;
    bool **flags;
    bool firstCheck;
    int timerCount;
    int countMinesForLineEdit;

    QIcon windowIcon;
    QIcon zero, one, two, three, four, five, six, seven, eight;
    QIcon bomb;
    QIcon flag;

    int findAround(int, int);
    void createField(int, int);
    void openField(int, int);
    bool isEmpty(int, int);
    void start_window();
    void end_window();
    void minesOpen(bool);
    void newGame();
    void smartOpen(int, int);
    void paintIcons(int, int);
    int findFlags(int, int);
    void newField();
public slots:
    void left_click();
    void right_click();
    void double_click();
    void menu_newGame();
    void menu_settings();
    void timeOut();
};

#endif // MAINWINDOW_H
