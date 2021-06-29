#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <qnode.h>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();
    QString toQString(std::string const &s);
    std::string fromQString(QString const &s);

public slots:
    void updateSubBox();
    void updateGraphicsBox();


private slots:
    void on_publishButton_clicked();
    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;
    QNode qnode;
    QString mResourceDir;

};

#endif // MAINWINDOW_H
