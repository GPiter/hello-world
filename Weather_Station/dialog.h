#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QByteArray>
#include <QFile>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void readSerial();
    void updateTemperature(QString);
    void updateHumidity(QString);

private:
    Ui::Dialog *ui;

    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 6790;
    static const quint16 arduino_uno_product_id = 29987;
    QByteArray serialData;

    QString parsed_temperature;
    QString parsed_humidity;

    double temperature_value;
};

#endif // DIALOG_H
