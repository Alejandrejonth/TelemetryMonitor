#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QCustomplot.h"

#include<QSerialPortInfo>
#include<QSerialPort>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QtNetwork>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QSqlDatabase>
#include<QtNetwork>
#include<QStringList>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonValue>
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QDebug>

QSqlDatabase baseDeDatos = QSqlDatabase::addDatabase("QMYSQL");
float voltaje,Temp;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conectarArduino();
    //configurar base de datos.
        //Paso#1. cofigurar el servidor de la base de datos.
        baseDeDatos.setHostName("localhost");
        //baseDeDatos.setHostName("https://paginaweb.com");

        //Paso#2 configurar el puerto.
        baseDeDatos.setPort(3306);

        //Paso#3 configurar a que Bd nos conectaremos.
        baseDeDatos.setDatabaseName("2021B2");

        //Paso#4. Configurar el usuario al que se conectará.
        baseDeDatos.setUserName("admin51");

        //Paso #5 Configurar la contraseña del usuario anterior.
        baseDeDatos.setPassword("hola1234");
        if(baseDeDatos.open()){
                       qDebug() << "Abri la base de datos";
                   }
                   else{
                       qDebug() << "Error al abrir la base de datos";
                   }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recepcionSerialAsincrona(){
if(tarjeta_conectada && tarjeta->isReadable()){
      //QByteArray datosLeidos = arduino->readAll();
      QByteArray datosLeidos = tarjeta->readLine();
      int indice0 = datosLeidos.indexOf("}");
      int indice1 = datosLeidos.indexOf("{");
      QString infoExtraida = datosLeidos.mid(indice1,(indice0-indice1)+1);


      //Decodificacion JSON
      QJsonDocument mensajeJSON = QJsonDocument::fromJson(infoExtraida.toUtf8());
      QJsonValue varNivel1 = mensajeJSON["adc0"];
      QString varNivel1Texto = varNivel1.toString();
      if(!varNivel1Texto.isEmpty()){
          int valorADC = varNivel1Texto.toInt();
          voltaje = ((double)valorADC/1024)*5;
          ui->lcdNumber->display(voltaje);
          Temp= voltaje -0.5;
          Temp=Temp/.01;
          ui->lcdNumber_2->display(Temp);
          qDebug() << "Temperatura" << Temp;
          qDebug() << "Voltaje" << voltaje;
      }


     // ui->lcdNumber->display(datoEntero);
      if(indice0>=0 && indice1>=0) {
              qDebug() << "Datos extraidos: " << infoExtraida.toUtf8().constData();


      }


  }

}


void MainWindow::conectarArduino(){
  //Declaracion de las variables
  tarjeta = new QSerialPort(this);
  connect(tarjeta, &QSerialPort::readyRead, this, &MainWindow::recepcionSerialAsincrona);
  QString nombreDispositivoSerial = "";
  int productoID = 0;
  int fabricanteID = 0;

  //Imprimir en la terminal, la cantidad de dispositivos seriales virtuales, conectados a la computadora
  qDebug() << "Esto es un mensaje de terminal" << endl;
  qDebug() << "Puertos disponibles: " << QSerialPortInfo::availablePorts().length();

  foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
      if(serialPortInfo.hasVendorIdentifier()){
          fabricanteID = serialPortInfo.vendorIdentifier();
          productoID = serialPortInfo.productIdentifier();
          nombreDispositivoSerial = serialPortInfo.portName();

          qDebug() << "Fabricante: " << fabricanteID << endl;
          qDebug() << "Producto:   " << productoID << endl;

      }
  }


  //COnexion con Arduino
  if(productoID == ArduinoUNO || productoID == ArduinoMEGA){
      //Establece TTYACMX como nombre del dispositivo
      tarjeta->setPortName(nombreDispositivoSerial);
      tarjeta->open(QIODevice::ReadWrite);
      tarjeta->setDataBits(QSerialPort::Data8);
      tarjeta->setBaudRate(QSerialPort::Baud115200);
      tarjeta->setParity(QSerialPort::NoParity);
      tarjeta->setStopBits(QSerialPort::OneStop);
      tarjeta->setFlowControl(QSerialPort::NoFlowControl);
      tarjeta_conectada = true;
  }
}


void MainWindow::on_pushButton_clicked()
{
    if(baseDeDatos.open()){

        //obtener la fecha.
        //formato UNIX
        long int fechaUnix = QDateTime::currentSecsSinceEpoch();
        //Formato String
        QDateTime tiempo= QDateTime::currentDateTime();
        QString fechaString = tiempo.toString();

        ui->lineEdit->setText(fechaString);

               //Paso # 2.1 Preparar un comando de mysql para insertar los datos.
                    QString comando7 = "INSERT INTO RegTem(temperatura, fecha) VALUES(?,?)";
                    QSqlQuery comando8;
                    comando8.prepare(comando7);
                    comando8.addBindValue(Temp);
                    comando8.addBindValue(QString::number(fechaUnix));

               //Paso # 2.4 Ejecutar el comando de mysql.
               if(comando8.exec()){
                   qDebug()<<"La fila se inserto";
               }
               else{
                   qDebug()<<"Error_unu";
               }
           }
           else{
               qDebug() << "Error al abrir la base de datos";
               qDebug() << "Verifica la contraseña,";
               qDebug() << "Nombre de la base de datos,";
               qDebug() << "Nombre de la tabla de base de datos";
               //qDebug() << "La estructura y los datos enviados no coinciden";
           }

}


void MainWindow::on_pushButton_2_clicked()
{       QSqlDatabase baseDatos = QSqlDatabase::addDatabase("QMYSQL");
        baseDatos.setHostName("localhost");
        baseDatos.setPort(3306);
        baseDatos.setDatabaseName("2021B2");
        baseDatos.setUserName("admin51");
        baseDatos.setPassword("hola1234");

        if(!baseDatos.open()){
            qDebug() << "La base de datos no se pudo abrir";

        }
        else{
             qDebug() << "La base de datos SE pudo abrir";
             QString comandoMYSQL = "SELECT * FROM RegTem ORDER BY id ASC LIMIT 20";
             QSqlQuery comando = baseDatos.exec(comandoMYSQL);
             QVector<double> ejeX(20), ejeY(20);
             int contadorDatos = 0;
             while(comando.next()) {
                  int fechaUnix = comando.value(2).toLongLong();
                  double temperatura = comando.value(1).toDouble();
                  ejeX[contadorDatos] = contadorDatos;
                  ejeY[contadorDatos] = temperatura;
                  contadorDatos++;
                  QDateTime fecha = QDateTime::fromTime_t(fechaUnix);
                  QString filaLeida = "Temperatura: " + QString::number(temperatura) + " Fecha: " + fecha.toString() + "\n";
                //  ui->plainTextEdit->appendPlainText(filaLeida);

             }
             //Crear grafica
             QCustomPlot *grafica = ui->customPlot;
             grafica->addGraph();
             grafica->graph(0)->setData(ejeX,ejeY);
             grafica->xAxis->setLabel("Indice dato");
             grafica->yAxis->setLabel("Temperatura");
             grafica->yAxis->setRange(110,160);
             grafica->xAxis->setRange(0,20);
             //grafica->xAxis->setRange(0,100);
             ui->customPlot->replot();

    }
}

