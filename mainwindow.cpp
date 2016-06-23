#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QMessageBox>
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
    char* localhost="127.0.0.1";
    char* serverhost="103.13.222.121";
    char host[20];
    ui->setupUi(this);
    client = new QTcpSocket(this);
    QMessageBox msg(QMessageBox::Warning, "警告", "您想要远程调试吗?", 0, 0);
    msg.setWindowFlags(Qt::WindowStaysOnTopHint| (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    msg.addButton("是", QMessageBox::AcceptRole);
    msg.addButton("否", QMessageBox::RejectRole);
    if (msg.exec() == QMessageBox::RejectRole)
        strcpy(host,localhost);
    else
        strcpy(host,serverhost);
    client->connectToHost(QHostAddress(host), 6665);//103.13.222.121
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
