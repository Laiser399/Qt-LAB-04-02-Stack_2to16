#include "mainwindow.h"

#include <QDebug>
#include "stack.h"
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <cctype>
#include <QMessageBox>

//   functions   |
QString from2to16(const QString &num_str, bool *ok) {
    int number = 0, degree_2 = 1;
    for (auto it = num_str.rbegin(); it != num_str.rend(); ++it) {
        if (*it == '1') {
            number += degree_2;
        }
        else if (*it != '0') {
            *ok = false;
            return "";
        }
        degree_2 *= 2;
    }

    stack<char> s;
    while (number > 0) {
        short mod = number % 16;
        if (mod < 10) {
            s.push(mod + '0');
        }
        else {
            s.push(mod + 'A' - 10);
        }
        number /= 16;
    }

    QString res;
    while (s.count() > 0)
        res += s.pop();
    *ok = true;
    return res;
}

QString from16to2(const QString &num_str, bool *ok) {
    int number = 0, degree_16 = 1;
    for (auto it = num_str.rbegin(); it != num_str.rend(); ++it) {
        qDebug() << "HERE";
        QChar c = (*it).toUpper();
        if (c.isDigit()) {
            number += degree_16 * (c.unicode() - QChar('0').unicode());
        }
        else if ((c.unicode() >= QChar('A').unicode())
                 && (c.unicode() <= QChar('F').unicode()))
        {
            number += degree_16 * (c.unicode() - QChar('A').unicode() + 10);
        }
        else {
            *ok = false;
            return "";
        }
        degree_16 *= 16;
    }

    stack<char> s;
    while (number > 0) {
        s.push(number % 2 + '0');
        number /= 2;
    }

    QString res;
    while (s.count() > 0)
        res += s.pop();
    *ok = true;
    return res;
}

//-------------|
//   private   |
//-------------|
void MainWindow::setMenu() {
    QMenu *mFile = new QMenu("&Файл");
    mFile->addAction("&Выход", this, SLOT(close()));

    QMenu *mHelp = new QMenu("&?");
    mHelp->addAction("&Автор", this, SLOT(slot_About()));

    menuBar()->addMenu(mFile);
    menuBar()->addMenu(mHelp);
}

void MainWindow::setWidgets() {
    QWidget *w = new QWidget;
        QGridLayout *mainLay = new QGridLayout;
            edit2to16 = new QLineEdit;
            edit16to2 = new QLineEdit;
            edit2to16_res = new QLineEdit;
            edit16to2_res = new QLineEdit;
            QPushButton *buttonCalc2to16 = new QPushButton("Перевести");
            QPushButton *buttonCalc16to2 = new QPushButton("Перевести");


    setCentralWidget(w);
        w->setLayout(mainLay);
            mainLay->addWidget(new QLabel("Ввод"), 0, 1);
            mainLay->addWidget(new QLabel("Вывод"), 0, 2);
            mainLay->addWidget(new QLabel("Из 2 в 16:"), 1, 0);
            mainLay->addWidget(new QLabel("Из 16 в 2:"), 2, 0);
            mainLay->addWidget(edit2to16, 1, 1, 1, 1);
            mainLay->addWidget(edit16to2, 2, 1, 1, 1);
            mainLay->addWidget(edit2to16_res, 1, 2, 1, 1);
            mainLay->addWidget(edit16to2_res, 2, 2, 1, 1);
            mainLay->addWidget(buttonCalc2to16, 1, 3);
            mainLay->addWidget(buttonCalc16to2, 2, 3);

    connect(buttonCalc2to16, SIGNAL(clicked()), SLOT(slot_Calc2to16()));
    connect(buttonCalc16to2, SIGNAL(clicked()), SLOT(slot_Calc16to2()));

}

//-------------------|
//   private slots   |
//-------------------|
void MainWindow::slot_About() {
    QMessageBox::information(this, "Автор", "Студент МАИ\nГруппы М8О-213Б-17\nСеменов Сергей");
}

void MainWindow::slot_Calc2to16() {
    bool ok;
    QString res = from2to16(edit2to16->text().simplified(), &ok);
    edit2to16_res->setText(res);
    if (!ok) {
        QMessageBox::information(this, "Ошибка", "Ошибка перевода числа!");
        return;
    }
}

void MainWindow::slot_Calc16to2() {
    bool ok;
    QString res = from16to2(edit16to2->text().simplified(), &ok);
    edit16to2_res->setText(res);
    if (!ok) {
        QMessageBox::information(this, "Ошибка", "Ошибка перевода числа!");
        return;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMenu();
    setWidgets();

    setMinimumHeight(120);
    setMaximumHeight(120);

}

MainWindow::~MainWindow()
{

}
