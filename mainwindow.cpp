#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    // Connect signals to slots
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startCountdown);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopCountdown);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateDisplay);

    ui->stopButton->setEnabled(false);  // Initially disable the stop button

    ui->lcdDisplay->setDigitCount(8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startCountdown()
{
    QString input = ui->timeInput->text();
    QTime time = QTime::fromString(input, "hh:mm:ss");

    if (!time.isValid()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid time in HH:MM:SS format.");
        return;
    }

    countdownTime = time;
    ui->lcdDisplay->display(countdownTime.toString("hh:mm:ss"));

    timer->start(1000);  // Start the timer to tick every second

    ui->timeInput->setEnabled(false);  // Clear the input field
    ui->startButton->setEnabled(false);  // Disable the start button
    ui->stopButton->setEnabled(true);  // Enable the stop button
}

void MainWindow::stopCountdown()
{
    timer->stop();

    ui->timeInput->setEnabled(true);
    ui->startButton->setEnabled(true);  // Enable the start button
    ui->stopButton->setEnabled(false);  // Disable the stop button
}

void MainWindow::updateDisplay()
{
    if (countdownTime == QTime(0, 0, 0)) {
        timer->stop();
        ui->timeInput->setEnabled(true);
        ui->timeInput->clear();
        QMessageBox::information(this, "Time's Up", "The countdown has finished.");

        ui->startButton->setEnabled(true);  // Enable the start button
        ui->stopButton->setEnabled(false);  // Disable the stop button
        return;
    }

    countdownTime = countdownTime.addSecs(-1);
    ui->lcdDisplay->display(countdownTime.toString("hh:mm:ss"));
}
