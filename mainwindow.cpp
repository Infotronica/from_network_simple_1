#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::requestFromServer()
{
    QNetworkRequest networkRequest; // for make a request on the server using POST or GET method
    QByteArray postData; // contains data to send in the network request or store the data returned on the networkReply
    QString url_ws;

    url_ws=ui->lineEdit->text();
    networkRequest.setUrl(QUrl(url_ws));  // url for the network file, a text file in this case
    networkReply = networkManager.post(networkRequest,postData);  // make the request to server using the POST method

    // connect the networkReply to an SLOT, this SLOT is triggered when the network request finish
    connect(networkReply,SIGNAL(finished()),this,SLOT(receiveFromServer()));
}

void MainWindow::receiveFromServer()
{
    QString qString;
    QByteArray postData; // store the data returned on the networkReply

    // the networkReply contains returned data from the server when the network request is finished
    postData=networkReply->readAll(); // put received QByteArray data into postData object
    qString=QString::fromUtf8(postData); // the recieved data is plain text
    ui->plainTextEdit->setPlainText(qString); // copy to the plainTextEdit
    networkReply->deleteLater(); // delete networkReply object
}

void MainWindow::on_pushButton_clicked()
{
    requestFromServer();
}
