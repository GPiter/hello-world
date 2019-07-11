#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <String>
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


    /* --------------------- Вывод информации о доступных портах -----------------------------
     *
     *  Тестовый код, выводит описание всех доступных портов, vendor id и product id.
     *  Используется для определения параметров порта для настройки конткретной платы Arduino.
     */

    qDebug() << "Число портов: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
    qDebug() << "Описание: " << serialPortInfo.description() << "\n";
    qDebug() << "Наличие vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
    qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
    qDebug() << "Наличие product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
    qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }

    /*--------------------------------------------------------------------------------------*/


    // ------------------- Определение порта, к которому подключен Arduino ------------------

    bool arduino_is_available = false;
    QString arduino_port_name;

    //  Для каждого доступного serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        //  Проверка, имеет ли serialport данные product identifier и vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier())
        {
            //  Проверка, если product ID и vendor ID совпадают с данными Arduino
            if((serialPortInfo.productIdentifier() == arduino_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_vendor_id))
            {
                arduino_is_available = true;    // Флаг - Arduino доступно по данному порту
                arduino_port_name = serialPortInfo.portName();
            }
        }
    }

    // ----------------------------------------------------------------------------------------


    // ------------------------- Открытие и конфигурация Arduino порта ------------------------

    if(arduino_is_available)
    {
        qDebug() << "Определение Arduino порта...... OK\n";
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    } else
    {
        qDebug() << "Не найден корректный порт для Arduino. Проверьте подключение и настройки!\n";
        QMessageBox::information(this, "Ошибка Serial Port: ", "Couldn't open serial port to arduino.");
    }

    // ----------------------------------------------------------------------------------------

}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close(); //   Закрыть Serial port, если он открыт.
    }
    delete ui;
}

/* ----------------------- Чтение и обработка данных по Serial port ----------------------------
 *
 *  Алгоритм работы функции:
 *  1) Построчно читаем данные с Arduino.
 *  2) Преобразуем полученные данные в строку.
 *     Входящий пакет имеет структуру: [заголовок,значение].
 *  3) Парсим входящее сообщение по символу "," - с помощью метода split класса QString,
 *     таким образом, отделяем заголовок от значения датчика.
 *  4) В зависимости от полученного заголовка, присваиваем соответствующее значение дачтика.
 */

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

// ------------------------------------------------------------------------------------------

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
    // TODO
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
