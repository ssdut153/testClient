#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

QTcpSocket *client;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //char data[20]="hello,i am a client";
    //支持汉语
    std::string str = ui->textEdit->toPlainText().toStdString();
    const char* ch = str.c_str();

    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);
    client->write(ch);
    ui->textEdit->setPlainText("");
}
