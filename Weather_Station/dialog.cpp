#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->temp_lcdNumber->display("-------");
    arduino = new QSerialPort(this);
    parsed_temperature = "";
    parsed_humidity = "";


    /* ------------------------------------------------------------------------------------
     *  Тестовый код, выводит описание всех портов, vendor id и product id.
     *  Используется для определения параметров порта для настройки конткретной платы Arduino.
     */

    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
    qDebug() << "Description: " << serialPortInfo.description() << "\n";
    qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
    qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
    qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
    qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }

    /*--------------------------------------------------------------------------------------*/

    /*
     *   Identify the port the arduino uno is on.
     */
    bool arduino_is_available = false;
    QString arduino_uno_port_name;
    //
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier())
        {
            //  check if the product ID and the vendor ID match those of the arduino uno
            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id))
            {
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available)
    {
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    } else
    {
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }

}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close(); //    Close the serial port if it's open.
    }
    delete ui;
}

void Dialog::readSerial()
{
    QByteArray serialData = arduino->readLine();
    QString data = QString::fromStdString(serialData.toStdString());

    QStringList data_split = data.split(",");

    if (data_split[0] == "temp")
    {
        parsed_temperature = data_split[1];
        serialData.clear();
    }

    if (data_split[0] == "humidity")
    {
        parsed_humidity = data_split[1];
        serialData.clear();
    }

// ------------------ Запись полученных данных в файл ------------------

    // Значения температуры
     QFile temp_base("D:/tempdata.txt");
     if (temp_base.open(QIODevice::ReadWrite| QIODevice::Append))
     {
         QTextStream out(&temp_base);
         out << parsed_temperature << "\n";
     }

     // Значения влажности
      QFile humidity_base("D:/humdata.txt");
      if (humidity_base.open(QIODevice::ReadWrite| QIODevice::Append))
      {
          QTextStream out(&humidity_base);
          out << parsed_humidity << "\n";
      }

// --------------------------------------------------------------------

// ------------------------ Работа с графиком -------------------------

    QVector<double> temp_array;
    QDataStream stream(serialData);
    stream >> temp_array;

    int numSamples = temp_array.size();

    for (int i=0; i<numSamples; ++i)
    {
      qDebug() << "Vector: " << temp_array[i] << "\r\n";
    }

// --------------------------------------------------------------------

// -------------------- Вывод показаний на дисплей ---------------------

    qDebug() << "Температура: " << parsed_temperature << "\n";
    Dialog::updateTemperature(parsed_temperature);

    qDebug() << "Влажность: " << parsed_humidity << "\n";
    Dialog::updateHumidity(parsed_humidity);
    serialData.clear();

// --------------------------------------------------------------------

}

void Dialog::updateTemperature(QString sensor_reading)
{
    ui->temp_lcdNumber->display(sensor_reading);
}

void Dialog::updateHumidity(QString sensor_reading)
{
   ui->humidity_lcdNumber->display(sensor_reading);
}
