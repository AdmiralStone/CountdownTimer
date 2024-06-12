#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startCountdown();
    void stopCountdown();
    void updateDisplay();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTime countdownTime;
};
#endif // MAINWINDOW_H
