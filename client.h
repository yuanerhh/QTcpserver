#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();

private slots:
    void on_btn_connect_clicked();

    void on_btn_send_clicked();

    void on_btn_disConnect_clicked();

private:
    Ui::client *ui;
    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
};

#endif // CLIENT_H
