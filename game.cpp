#include "game.h"
#include "startwindow.h"
#include <QtWidgets>
#include <ctime>


Game::Game(QWidget *parent) : QMainWindow(parent)
{
    // Initialize variables.
    policy = new QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    menu_file = new QMenu("&File");
    menu_help = new QMenu("&Help");
    menu_file_newGame = new QAction("&New game", menu_file);
    menu_file_settings = new QAction("&Settings", menu_file);
    le_timer = new QLineEdit("0");
    le_countOfMines = new QLineEdit;
    lbl_timer = new QLabel;
    lbl_countOfMines = new QLabel;

    // Show start window.
    start_window();

    // Set style and properties.
    this->setStyleSheet(
                " QMainWindow {               "
                "    background-color: black; " // MediumPurple
                " }                           "
                        );
    le_timer->setStyleSheet(
                " QLineEdit {"
                "     width: 18px;"
                "     font-size: 20px;"
                "     border-width: 5px;"
                " }"
                            );
    le_countOfMines->setStyleSheet(
                " QLineEdit {"
                "     width: 18px;"
                "     font-size: 20px;"
                "     border-width: 5px;"
                " }"
                            );
    this->move(300, 0);
    this->show();

    // Create new field.
    newField();

    // Set menu bar.
    menu_file->addAction(menu_file_newGame);
    menu_file->addAction(menu_file_settings);
    menu_file->addSeparator();
    menu_file->addAction("&Exit", qApp, SLOT(quit()));
    menu_file_newGame ->setShortcut(QKeySequence(Qt::Key_F2));
    menu_file_settings->setShortcut(QKeySequence(Qt::Key_F5));
    menu_help->addAction("&About Qt", qApp, SLOT(aboutQt()), Qt::Key_F1);
    menuBar()->addMenu(menu_file);
    menuBar()->addMenu(menu_help);

    // Set widgets to form.
    QGridLayout *layout_field = new QGridLayout;
    layout_field->setSpacing(0);
    int k = 0;
    for (int i = 0; i < sizeField; i++)
        for (int j = 0; j < sizeField; j++)
            layout_field->addWidget(buttons[k++], i, j);

    QHBoxLayout *layout_lineEdits = new QHBoxLayout;
    layout_lineEdits->addWidget(lbl_timer);
    layout_lineEdits->addWidget(le_timer);
    layout_lineEdits->addStretch(10);
    layout_lineEdits->addWidget(lbl_countOfMines);
    layout_lineEdits->addWidget(le_countOfMines);

    QVBoxLayout *full = new QVBoxLayout;
    full->addLayout(layout_field);
    full->addLayout(layout_lineEdits);

    widget = new QWidget;
    widget->setLayout(full);
    setCentralWidget(widget);

    // Set images to timer and count of mines.
    QPixmap pix;
    pix.load(":/image/Picture/clock.ico");
    lbl_timer->resize(pix.size());
    lbl_timer->setPixmap(pix);
    pix.load(":/image/Picture/bomb_6231.ico");
    lbl_countOfMines->resize(pix.size());
    lbl_countOfMines->setPixmap(pix);

    // Read icons.
    firstCheck = false;
    flag =  QIcon(":/image/Picture/flag_green.png");
    bomb =  QIcon(":/image/Picture/bomb.png");
    one =   QIcon(":/image/Picture/one.png");
    two =   QIcon(":/image/Picture/two.png");
    three = QIcon(":/image/Picture/three.png");
    four =  QIcon(":/image/Picture/four.png");
    five =  QIcon(":/image/Picture/five.png");
    six =   QIcon(":/image/Picture/six.png");
    seven = QIcon(":/image/Picture/seven.png");
    eight = QIcon(":/image/Picture/eight.png");

    le_countOfMines->setReadOnly(true);
    le_timer->setReadOnly(true);
    timerCount = 0;
    le_countOfMines->setText(QString::number(countMinesForLineEdit = countMines));

    for (int i = 0; i < sizeField*sizeField; i++)
    {
        connect(buttons[i], &MyButton::leftClicked,   this, &Game::left_click  );
        connect(buttons[i], &MyButton::rightClicked,  this, &Game::right_click );
        connect(buttons[i], &MyButton::doubleClicked, this, &Game::double_click);

    }
    connect(menu_file_newGame,  &QAction::triggered, this, &Game::menu_newGame );
    connect(menu_file_settings, &QAction::triggered, this, &Game::menu_settings);
}

Game::~Game()
{
}

int Game::findAround(int i, int j)
{
    int count = 0;

    if (i-1 >= 0        && j-1 >= 0        && mines[i-1][j-1] == 9) count++;
    if (i-1 >= 0        &&                    mines[i-1][j]   == 9) count++;
    if (i-1 >= 0        && j+1 < sizeField && mines[i-1][j+1] == 9) count++;
    if (j-1 >= 0        &&                    mines[i][j-1]   == 9) count++;
    if (j+1 < sizeField &&                    mines[i][j+1]   == 9) count++;
    if (i+1 < sizeField && j-1 >= 0        && mines[i+1][j-1] == 9) count++;
    if (i+1 < sizeField &&                    mines[i+1][j]   == 9) count++;
    if (i+1 < sizeField && j+1 < sizeField && mines[i+1][j+1] == 9) count++;

    return count;
}

void Game::createField(int i_first, int j_first)
{
    while (mines[i_first][j_first] != 0)
    {
        for (int i = 0; i < sizeField; i++)
            for (int j = 0; j < sizeField; j++)
                mines[i][j] = 0;
        srand(time(NULL));
        int count = 0;
        while (count != countMines)
        {
            int i = rand() % sizeField, j = rand() % sizeField;
            if (mines[i][j] == 9)
                continue;
            if (mines[i][j] != 9)
                mines[i][j]  = 9;
            if (findAround(i_first, j_first) == 0)
                count++;
            else
                mines[i][j] = 0;
        }
        for (int i = 0; i < sizeField; i++)
                for (int j = 0; j < sizeField; j++)
                    if (mines[i][j] == 0)
                        mines[i][j] = findAround(i, j);
    }
}

void Game::openField(int i, int j)
{
    if (i >= 0 && i < sizeField)
    {
        if (j >= 0 && j < sizeField)
        {
            paintIcons(i, j);

            if (!buttons[i*sizeField+j]->isChecked())
                buttons[i*sizeField+j]->setChecked(true);

            while (mines[i][j] == 0)
                if (mines[i][j] == 0)
                {
                    mines[i][j] = -1;
                    openField(i - 1, j - 1);
                    openField(i - 1, j    );
                    openField(i - 1, j + 1);
                    openField(i,     j - 1);
                    openField(i,     j + 1);
                    openField(i + 1, j - 1);
                    openField(i + 1, j    );
                    openField(i + 1, j + 1);
                }
                else
                {
                    if (isEmpty(i - 1, j - 1)) openField(i - 1, j - 1);
                    if (isEmpty(i - 1, j    )) openField(i - 1, j    );
                    if (isEmpty(i - 1, j + 1)) openField(i - 1, j + 1);
                    if (isEmpty(i,     j - 1)) openField(i,     j - 1);
                    if (isEmpty(i,     j + 1)) openField(i,     j + 1);
                    if (isEmpty(i + 1, j - 1)) openField(i + 1, j - 1);
                    if (isEmpty(i + 1, j    )) openField(i + 1, j    );
                    if (isEmpty(i + 1, j + 1)) openField(i + 1, j + 1);
                }
        }
    }
}

bool Game::isEmpty(int i, int j)
{
    // if cells is empty return true, else return false.
    if (i >= 0 && i < sizeField && j >= 0 && j < sizeField && mines[i][j] == 0)
        return true;
    return false;
}

void Game::start_window()
{
    // Show the first window and choose complexity.
    startWindow = new StartWindow;
    startWindow->exec();
    int complexity = startWindow->clicked_start();
    if (complexity == 1)
    {
        sizeField = 9;
        countMines = 10;
    }
    else if (complexity == 2)
    {
        sizeField = 16;
        countMines = 40;
    }
    else if (complexity == 3)
    {
        sizeField = 25;
        countMines = 120;
    }
    else
        std::exit(1);
}

void Game::minesOpen(bool isWin)
{
    // if you lost then open all mines.
    for (int i = 0; i < sizeField; i++)
        for (int j = 0; j < sizeField; j++)
            if (mines[i][j] == 9)
            {
                QString loseColor("QPushButton:checked {background-color: red;}");
                QString winColor("QPushButton:checked {background-color: green;}");
                buttons[i*sizeField+j]->setStyleSheet(isWin ? winColor : loseColor);
                buttons[i*sizeField+j]->setIcon(bomb);
                buttons[i*sizeField+j]->setChecked(true);
            }
}

void Game::newGame()
{
    for (int i = 0; i < sizeField; i++)
        for (int j = 0; j < sizeField; j++)
        {
            mines[i][j] = 1;
            flags[i][j] = false;
        }
    for (int i = 0; i < sizeField*sizeField; i++)
    {
        buttons[i]->setChecked(false);
        buttons[i]->setText("");
        buttons[i]->setStyleSheet(
                    " QPushButton {                    "
                    "    background-color: Black;      " // DarkOrchid
                    "    font-size: 25px;              "
                    "    border: 1px solid MistyRose;  "
                    " }                                "
                    "                                  "
                    " QPushButton:hover {              "
                    "    background-color: Fuchsia;    "
                    " }                                "
                    "                                  "
                    " QPushButton:checked {            "
                    "    background-color: White;      "
                    " }                                "
                                  );
        buttons[i]->setIcon(zero);
    }
    timerCount = 0;
    le_timer->setText("0");
    timer->stop();
    le_countOfMines->setText(QString::number(countMines));
    countMinesForLineEdit = countMines;
}

void Game::smartOpen(int i, int j)
{
    if (i-1 >= 0 && j-1 >= 0 && !flags[i-1][j-1])
        mines[i-1][j-1] == 0 ? openField(i-1, j-1) : paintIcons(i-1, j-1);

    if (i-1 >= 0 && !flags[i-1][j])
        mines[i-1][j] == 0 ? openField(i-1, j) : paintIcons(i-1, j);

    if (i-1 >= 0 && j+1 < sizeField && !flags[i-1][j+1])
        mines[i-1][j+1] == 0 ? openField(i-1, j+1) : paintIcons(i-1, j+1);

    if (j-1 >= 0 && !flags[i][j-1])
        mines[i][j-1] == 0 ? openField(i, j-1) : paintIcons(i, j-1);

    if (j+1 < sizeField && !flags[i][j+1])
        mines[i][j+1] == 0 ? openField(i, j+1) : paintIcons(i, j+1);

    if (i+1 < sizeField && j-1 >= 0 && !flags[i+1][j-1])
        mines[i+1][j-1] == 0 ? openField(i+1, j-1) : paintIcons(i+1, j-1);

    if (i+1 < sizeField && !flags[i+1][j])
        mines[i+1][j] == 0 ? openField(i+1, j) : paintIcons(i+1, j);

    if (i+1 < sizeField && j+1 < sizeField && !flags[i+1][j+1])
        mines[i+1][j+1] == 0 ? openField(i+1, j+1) : paintIcons(i+1, j+1);
}

void Game::paintIcons(int i, int j)
{
    if (mines[i][j] == 0 || mines[i][j] == -1)
    {
        buttons[i*sizeField+j]->setText("");
        buttons[i*sizeField+j]->setChecked(true);
    }
    else if (flags[i][j])
        buttons[i*sizeField+j]->setIcon(flag);
    else
    {
        if (mines[i][j] == 1)
        {
            buttons[i*sizeField+j]->setIcon(one);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 2)
        {
            buttons[i*sizeField+j]->setIcon(two);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 3)
        {
            buttons[i*sizeField+j]->setIcon(three);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 4)
        {
            buttons[i*sizeField+j]->setIcon(four);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 5)
        {
            buttons[i*sizeField+j]->setIcon(five);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 6)
        {
            buttons[i*sizeField+j]->setIcon(six);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 7)
        {
            buttons[i*sizeField+j]->setIcon(seven);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 8)
        {
            buttons[i*sizeField+j]->setIcon(eight);
            buttons[i*sizeField+j]->setChecked(true);
        }
        else if (mines[i][j] == 9)
        {
            buttons[i*sizeField+j]->setChecked(true);
            buttons[i*sizeField+j]->setIcon(bomb);
        }
    }
}

int Game::findFlags(int i, int j)
{
    int count = 0;

    if (i-1 >= 0        && j-1 >= 0        && flags[i-1][j-1]) count++;
    if (i-1 >= 0        &&                    flags[i-1][j]  ) count++;
    if (i-1 >= 0        && j+1 < sizeField && flags[i-1][j+1]) count++;
    if (j-1 >= 0        &&                    flags[i][j-1]  ) count++;
    if (j+1 < sizeField &&                    flags[i][j+1]  ) count++;
    if (i+1 < sizeField && j-1 >= 0        && flags[i+1][j-1]) count++;
    if (i+1 < sizeField &&                    flags[i+1][j]  ) count++;
    if (i+1 < sizeField && j+1 < sizeField && flags[i+1][j+1]) count++;

    return count;
}

void Game::newField()
{
    // Create and initialize arrays.
    buttons = new MyButton* [sizeField*sizeField];
    mines = new int* [sizeField];
    flags = new bool* [sizeField];
    for (int i = 0; i < sizeField; i++)
    {
        mines[i] = new int [sizeField];
        flags[i] = new bool [sizeField];
    }
    for (int i = 0; i < sizeField; i++)
        for (int j = 0; j < sizeField; j++)
        {
            mines[i][j] = 1;
            flags[i][j] = false;
        }

    // Set properties for buttons.
    for (int i = 0; i < sizeField*sizeField; i++)
    {
        buttons[i] = new MyButton;
        buttons[i]->setMinimumSize(25, 25);
        buttons[i]->setCheckable(true);
        buttons[i]->setSizePolicy(policy->verticalPolicy(), policy->horizontalPolicy());
        buttons[i]->setStyleSheet(
                    " QPushButton {                    "
                    "    background-color: Black;      " // DarkOrchid
                    "    font-size: 25px;              "
                    "    border: 1px solid MistyRose;  "
                    " }                                "
                    "                                  "
                    " QPushButton:hover {              "
                    "    background-color: Fuchsia;    "
                    " }                                "
                    "                                  "
                    " QPushButton:checked {            "
                    "    background-color: White;      "
                    " }                                "
                                 );
        buttons[i]->setIcon(zero);
    }
}

void Game::left_click()
{
    int count = 0;
    for (int i = 0; i < sizeField*sizeField; i++, count++)
        if (buttons[i] == sender())
            break;

    int ii = count / sizeField;
    int jj = count - ii*sizeField;

    if (!flags[ii][jj])
    {
        // Open sheet with mine.
        if (mines[ii][jj] == 9)
        {
            timer->stop();
            minesOpen(false);
            endWindow = new EndWindow;
            endWindow->lose_lbl();
            endWindow->show();
            endWindow->exec();
            newGame();
            firstCheck = false;
            return;
        }

        // First click (create field).
        if (!firstCheck)
        {
            timer = new QTimer;
            timer->start(1000);
            connect(timer, &QTimer::timeout, this, &Game::timeOut);
            createField(ii, jj);
            openField(ii, jj);
            firstCheck = true;
        }

        openField(ii, jj);

        bool isWin = true;
        for (int i = 0; i < sizeField; i++)
            for (int j = 0; j < sizeField; j++)
                if (!buttons[i*sizeField+j]->isChecked() && mines[i][j] != 9)
                    isWin = false;
        // If you win.
        if (isWin)
        {
            timer->stop();
            minesOpen(true);
            endWindow = new EndWindow;
            endWindow->win_lbl();
            endWindow->show();
            endWindow->exec();
            newGame();
            firstCheck = false;
            return;
        }
    }
}

void Game::right_click()
{
    int count = 0;
    for (int i = 0; i < sizeField*sizeField; i++, count++)
        if (buttons[i] == sender())
            break;

    int ii = count / sizeField;
    int jj = count - ii*sizeField;

    if (!buttons[count]->isChecked() && !flags[ii][jj])
    {
        buttons[count]->setIcon(flag);
        flags[ii][jj] = true;
        le_countOfMines->setText(QString::number(--countMinesForLineEdit));
        return;
    }
    if (!buttons[count]->isChecked() && flags[ii][jj])
    {
        buttons[count]->setIcon(zero);
        le_countOfMines->setText(QString::number(++countMinesForLineEdit));
        flags[ii][jj] = false;
    }
}

void Game::double_click()
{
    int count = 0;
    for (int i = 0; i < sizeField*sizeField; i++, count++)
        if (buttons[i] == sender())
            break;

    int ii = count / sizeField;
    int jj = count - ii*sizeField;

    if (mines[ii][jj] == findFlags(ii, jj))
        smartOpen(ii, jj);

    bool isWin = true;
    for (int i = 0; i < sizeField; i++)
        for (int j = 0; j < sizeField; j++)
        {
            if (mines[i][j] == 9 && buttons[i*sizeField+j]->isChecked())
            {
                minesOpen(false);
                endWindow = new EndWindow;
                endWindow->lose_lbl();
                endWindow->show();
                endWindow->exec();
                newGame();
                firstCheck = false;
            }
            if (!buttons[i*sizeField+j]->isChecked() && mines[i][j] != 9)
                isWin = false;
        }
    if (isWin)
    {
        timer->stop();
        minesOpen(true);
        endWindow = new EndWindow;
        endWindow->win_lbl();
        endWindow->show();
        endWindow->exec();
        newGame();
        firstCheck = false;
        return;
    }
}

void Game::menu_newGame()
{
    newGame();
    firstCheck = false;
}

void Game::menu_settings()
{
    settingsWindow = new SettingsWindow(sizeField, countMines);
    settingsWindow->show();
    settingsWindow->exec();
}

void Game::timeOut()
{
    le_timer->setText(QString::number(++timerCount));
}
