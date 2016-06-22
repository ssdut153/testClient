#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

QTcpSocket *client;

void MainWindow::readClient2()
{
    QString str = client->readAll();
    ui->textEdit_2->append(str);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("103.13.222.121"), 6665);//103.13.222.121
    connect(client, SIGNAL(readyRead()), this, SLOT(readClient2()));
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

    client->write(ch);

    //client->close();
    ui->textEdit->setPlainText("");
}
