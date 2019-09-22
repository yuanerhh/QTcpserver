#include "client.h"
#include "ui_client.h"
#include <QDateTime>

client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    ui->lineEdit_Port->setText("8888");
    ui->lineEdit_IP->setText("127.0.0.1");

    tcpsocket = NULL;

    tcpsocket = new QTcpSocket(this);

    connect(tcpsocket, &QTcpSocket::readyRead,
            [=](){
        QByteArray array = tcpsocket->readAll();
        array.append('\n');
        array.push_front('\n');
        array.push_front(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toUtf8());
        ui->textEdit_read->append(array);

//        ui->textEdit_read->append("\n");
    });

    connect(tcpsocket, &QTcpSocket::disconnected,
            [=](){ui->textEdit_read->setText("连接断开");});
}

client::~client()
{
    delete ui;
}



void client::on_btn_connect_clicked()
{
    QString ipSer = ui->lineEdit_IP->text();
    qint16 portSer = ui->lineEdit_Port->text().toInt();

    tcpsocket->connectToHost(QHostAddress(ipSer), portSer);
}

void client::on_btn_send_clicked()
{
    QString str = ui->textEdit_send->toPlainText();
    tcpsocket->write(str.toUtf8().data());
}

void client::on_btn_disConnect_clicked()
{
    ui->textEdit_read->setText("连接断开");
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
}
