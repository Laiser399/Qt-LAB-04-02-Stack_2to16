#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLineEdit *edit2to16, *edit16to2, *edit2to16_res, *edit16to2_res;

    void setMenu();
    void setWidgets();
private slots:
    void slot_About();
    void slot_Calc2to16();
    void slot_Calc16to2();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
