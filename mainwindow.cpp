#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(ui->comboBox_com, SIGNAL(cliked()),this,SLOT(serial_refresh()));
    serial_refresh();
    btn_status(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serial_refresh(){

     QList<QSerialPortInfo> serial_list;

     serial_list = QSerialPortInfo::availablePorts();
     ui->comboBox_com->clear();

     for(int i=0;i<serial_list.size();i++){
          ui->comboBox_com->addItem(serial_list.at(i).portName());// + " " + serial_list.at(i).description());
          qDebug() << serial_list.at(i).portName() + serial_list.at(i).description();
     }

}

void MainWindow::serial_init(){

    serial = new QSerialPort();
    serial_timer = new QTimer();


    ui->comboBox_com->setEnabled(false);

    connect(serial, SIGNAL(readyRead()), this, SLOT(serial_read_timeout()));
    connect(serial_timer, SIGNAL(timeout()), this, SLOT(serial_read()));


    serial->setPortName(ui->comboBox_com->currentText());
    serial->setBaudRate(9600);

    if(serial->open(QIODevice::ReadWrite)){

        serial->waitForReadyRead(10);

    }
}

//QByteArray转16进制字符串
QString MainWindow::ba_to_hex_str(QByteArray ba){

    QString str,tmp;

    tmp.append(ba.toHex().toUpper());

    for(int i=0;i<ba.count();i++) {
        str.append(tmp.mid(i*2,2)+" ");
    }

    str.chop(1);

    return str;
}

//16进制字符串转QByteArray
QByteArray MainWindow::hex_str_to_ba(QString str){

    bool ok;
    QByteArray ba;
    QStringList str_list;
    str_list = str.split(" ");

    for(int i=0;i<str_list.size();i++){
        ba.append(str_list.at(i).toUInt(&ok,16));
    }

    //ba.append()
    return ba;
}

//串口超时
void MainWindow::serial_read_timeout(){

    serial_timer->start(30);

}


//串口发送数据
void MainWindow::serial_write(QByteArray ba){

    serial->write(ba);
    //qDebug()<<"串口发送数据："<<ba_to_hex_str(ba);
   // debug_msg("发送："+ba_to_hex_str(ba));

    serial->waitForBytesWritten(200);

}

//串口接收数据
void MainWindow::serial_read(){

    QByteArray ba;

    ba = serial->readAll();

    ui->textEdit_msg->append(ba);
   // qDebug()<<"串口收到数据："<<ba_to_hex_str(ba)<<"转换成字符串："<<ba;
    //debug_msg("收到："+ba_to_hex_str(ba));

    serial_timer->stop();
}


void MainWindow::btn_status(bool status){

    if(status){

        ui->pushButton_rsn->setEnabled(true);
        ui->pushButton_wsn->setEnabled(true);
        ui->pushButton_clr->setEnabled(true);
        ui->pushButton_fac->setEnabled(true);
        ui->pushButton_wpa->setEnabled(true);
        ui->pushButton_rpa->setEnabled(true);

    }else{
        ui->pushButton_rsn->setEnabled(false);
        ui->pushButton_wsn->setEnabled(false);
        ui->pushButton_clr->setEnabled(false);
        ui->pushButton_fac->setEnabled(false);
        ui->pushButton_wpa->setEnabled(false);
        ui->pushButton_rpa->setEnabled(false);
    }
}


void MainWindow::on_pushButton_com_clicked()
{
    if(ui->pushButton_com->text() == "打开串口"){

        serial_init();

        btn_status(true);
        ui->pushButton_com->setText("关闭串口");
        ui->pushButton_rsn->setEnabled(true);

    }else{
        serial->close();

        btn_status(false);
        ui->pushButton_com->setText("打开串口");
        ui->comboBox_com->setEnabled(true);

    }
}


void MainWindow::on_pushButton_rsn_clicked()
{
    serial->write("ff aa bb 00 ff");
    //serial->write("abcdefg");

}


void MainWindow::on_pushButton_wsn_clicked()
{
    serial->write("ff bb aa 01 ff");
    //serial->write("abcdefg");
}


void MainWindow::on_pushButton_fac_clicked()
{

}


void MainWindow::on_pushButton_rpa_clicked()
{

}


void MainWindow::on_pushButton_wpa_clicked()
{

}


void MainWindow::on_pushButton_clr_clicked()
{
    ui->textEdit_msg->clear();
}

