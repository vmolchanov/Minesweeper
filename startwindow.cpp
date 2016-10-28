#include "startwindow.h"


StartWindow::StartWindow(QWidget *parent) : QDialog(parent, Qt::WindowCloseButtonHint)
{
    this->setStyleSheet(
                " QDialog {                      "
                "    background-color: Lavender; "
                " }                              "
                "                                "
                " QRadioButton {                 "
                "    font-size: 15px;            "
                " }                              "
                "                                "
                " QPushButton {                  "
                "    font-size: 20px;            "
                " }                              "
                       );

    easy =   new QRadioButton("Easy"  );
    medium = new QRadioButton("Medium");
    hard =   new QRadioButton("Hard"  );
    start =  new QPushButton ("&Start" );
    start->setEnabled(false);
    exit =  new  QPushButton ("&Exit"  );

    levelsOfComplexity = new QVBoxLayout;
    levelsOfComplexity->addWidget(easy  );
    levelsOfComplexity->addWidget(medium);
    levelsOfComplexity->addWidget(hard  );

    buttons = new QHBoxLayout;
    buttons->addWidget(start);
    buttons->addWidget(exit );

    full = new QVBoxLayout;
    full->addLayout(levelsOfComplexity);
    full->addLayout(buttons);

    setLayout(full);

    windowIcon = QIcon(":/image/Picture/bomb.png");
    this->setWindowIcon(windowIcon);

    connect(easy,   &QRadioButton::clicked, this, &StartWindow::unlockingButton);
    connect(medium, &QRadioButton::clicked, this, &StartWindow::unlockingButton);
    connect(hard,   &QRadioButton::clicked, this, &StartWindow::unlockingButton);
    connect(start,  &QPushButton ::clicked, this, &StartWindow::clicked_start  );
    connect(exit,   &QPushButton ::clicked, this, &StartWindow::clicked_exit   );
}

StartWindow::~StartWindow()
{
}

void StartWindow::unlockingButton()
{
    start->setEnabled(true);
}

int StartWindow::clicked_start()
{
    this->close();
    int complexity = easy->isChecked() ? 1 : (medium->isChecked() ? 2 : (hard->isChecked() ? 3 : 4));
    return complexity;
}

bool StartWindow::clicked_exit()
{
    std::exit(1);
}
