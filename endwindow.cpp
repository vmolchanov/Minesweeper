#include "endwindow.h"

EndWindow::EndWindow(QWidget *parent) : QDialog(parent, Qt::WindowSystemMenuHint)
{
    this->setStyleSheet(
                " QDialog {                      "
                "    background-color: Lavender; "
                " }                              "
                "                                "
                " QPushButton {                  "
                "    font-size: 20px;            "
                " }                              "
                        );
    this->setModal(true); // Dialog window is modal.

    newGame = new QPushButton("&New Game");
    exit    = new QPushButton("&Exit"    );
    lbl = new QLabel;
    down = new QHBoxLayout;
    full = new QVBoxLayout;

    down->addWidget(newGame);
    down->addWidget(exit   );
    full->addWidget(lbl);
    full->addLayout(down);

    setLayout(full);

    windowIcon = QIcon(":/image/Picture/bomb.png");
    this->setWindowIcon(windowIcon);

    connect(exit,    &QPushButton::clicked, this, &EndWindow::clicked_exit   );
    connect(newGame, &QPushButton::clicked, this, &EndWindow::clicked_newGame);
}

EndWindow::~EndWindow()
{
}

void EndWindow::win_lbl()
{
    QString style_lbl("QLabel {color: green;}");
    lbl->setStyleSheet(style_lbl);
    lbl->setText("<h2 align=\"center\">You Winner!</h2>");
}

void EndWindow::lose_lbl()
{
    QString style_lbl("QLabel {color: red;}");
    lbl->setStyleSheet(style_lbl);
    lbl->setText("<h2 align=\"center\">You Loser!</h2>");
}

void EndWindow::clicked_exit()
{
    std::exit(1);
}

bool EndWindow::clicked_newGame()
{
    this->close();
    return true;
}
