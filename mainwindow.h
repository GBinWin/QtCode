#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QComboBox>
#include <QList>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString    ba_to_hex_str(QByteArray ba);
    QByteArray hex_str_to_ba(QString str);

public slots:

    void serial_refresh();
    void serial_init();
    void btn_status(bool status);
    void serial_write(QByteArray ba);
    void serial_read();
    void serial_read_timeout();


private slots:
    void on_pushButton_com_clicked();

    void on_pushButton_rsn_clicked();

    void on_pushButton_wsn_clicked();

    void on_pushButton_fac_clicked();

    void on_pushButton_rpa_clicked();

    void on_pushButton_wpa_clicked();

    void on_pushButton_clr_clicked();

private:
    Ui::MainWindow *ui;

    QSerialPort *serial;
    QTimer *serial_timer, *refresh_timer;

};
#endif // MAINWINDOW_H
