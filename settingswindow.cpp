#include "settingswindow.h"
#include "game.h"

SettingsWindow::SettingsWindow(int &sizeField, int &countMines, QWidget *parent) : QDialog(parent, Qt::WindowCloseButtonHint)
{
    up_left = new QVBoxLayout;
    up_right = new QVBoxLayout;
    up = new QHBoxLayout;
    down = new QHBoxLayout;
    full = new QVBoxLayout;
    special_size = new QHBoxLayout;
    special_countOfMines = new QHBoxLayout;
    rb_easy = new QRadioButton("Easy");
    rb_medium = new QRadioButton("Medium");
    rb_hard = new QRadioButton("Hard");
    rb_special = new QRadioButton("Special");
    pb_ok = new QPushButton("&Ok");
    pb_cancel = new QPushButton("&Cancel");
    le_size = new QLineEdit;
    le_countOfMines = new QLineEdit;

    le_size->setStyleSheet(
                "QLineEdit {"
                "    width: 40px;"
                "}"
                           );
    le_countOfMines->setStyleSheet(
                "QLineEdit {"
                "    width: 40px;"
                "}"
                                   );

    special_size->addWidget(new QLabel("Size"), 1);
    special_size->addWidget(le_size);
    special_countOfMines->addWidget(new QLabel("Count of mines"), 1);
    special_countOfMines->addWidget(le_countOfMines);
    up_left->addWidget(rb_easy);
    up_left->addWidget(rb_medium);
    up_left->addWidget(rb_hard);
    up_right->addWidget(rb_special);
    up_right->addLayout(special_size);
    up_right->addLayout(special_countOfMines);
    up->addLayout(up_left);
    up->addStretch(50);
    up->addLayout(up_right);
    down->addWidget(pb_ok);
    down->addWidget(pb_cancel);
    full->addLayout(up);
    full->addLayout(down);
    setLayout(full);

    if (sizeField == 9 && countMines == 10)
        rb_easy->setChecked(true);
    else if (sizeField == 16 && countMines == 40)
        rb_medium->setChecked(true);
    else if (sizeField == 25 && countMines == 120)
        rb_hard->setChecked(true);
    else
        rb_special->setChecked(true);

    if (!rb_special->isChecked())
    {
        le_size->setEnabled(false);
        le_countOfMines->setEnabled(false);
    }

    connect(pb_ok,     &QPushButton::clicked, this, &SettingsWindow::clicked_ok    );
    connect(pb_cancel, &QPushButton::clicked, this, &SettingsWindow::clicked_cancel);
}

SettingsWindow::~SettingsWindow()
{
}

void SettingsWindow::clicked_cancel()
{
    this->close();
}

void SettingsWindow::clicked_ok()
{
    if (rb_easy->isChecked())
    {
        sizeField = 9;
        countMines = 10;
    }
    if (rb_medium->isChecked())
    {
        sizeField = 16;
        countMines = 40;
    }
    if (rb_hard->isChecked())
    {
        sizeField = 25;
        countMines = 120;
    }
    if (rb_special->isChecked())
    {
        QString size, mines;
        size = le_size->text();
        sizeField = size.toInt();
        mines = le_countOfMines->text();
        countMines = mines.toInt();
    }
    this->close();
}

