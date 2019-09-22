#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>

#define PORT_SERVER 8888

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    tcpserver = NULL;
    tcpsocket = NULL;

    //监听套接字
    setWindowTitle("Server:8888");
    tcpserver = new QTcpServer(this);
    //指定绑定的IP(Any指当前网卡的所有IP)和port
    tcpserver->listen(QHostAddress::Any, PORT_SERVER);

    //获取连接
    connect(tcpserver, &QTcpServer::newConnection,
            [=](){
        tcpsocket = tcpserver->nextPendingConnection();
        QString ipCli = tcpsocket->peerAddress().toString();
        qint16 portCli = tcpsocket->peerPort();
        QString temp = QString("[%1:%2]:连接成功").arg(ipCli).arg(portCli);
        ui->textread->setText(temp);

        connect(tcpsocket, &QTcpSocket::readyRead,
                [=](){
            QByteArray array = tcpsocket->readAll();
            array.push_front('\n');
            array.push_front(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").toUtf8());
            array.append('\n');
            ui->textread->append(array);
        });

        connect(tcpsocket, &QTcpSocket::disconnected,
                [=](){
            ui->textread->setText("连接断开");
        });
    });
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnclose_clicked()
{
    if (tcpsocket != NULL)
    {
        ui->textread->setText("连接断开");
        tcpsocket->disconnectFromHost();
        tcpsocket->close();
        tcpsocket = NULL;
    }
}

void Widget::on_sendBtn_clicked()
{
    if (tcpsocket != NULL)
    {
        QString str = ui->textwrite->toPlainText();
        tcpsocket->write(str.toUtf8().data());
    }
}
