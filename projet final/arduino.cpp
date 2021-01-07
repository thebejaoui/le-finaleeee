#include "arduino.h"
#include<QDebug>


arduino::arduino()
{

data="";
arduino_port_name="";
arduino_is_available=false;
serial=new QSerialPort;


}

 int arduino:: connect_arduino()
 {
     foreach(const QSerialPortInfo  &serial_port_info , QSerialPortInfo::availablePorts()){
         if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
             if(serial_port_info.vendorIdentifier()== arduino_uno_vendor_id && serial_port_info.productIdentifier()== arduino_uno_producy_id){
                arduino_is_available = true;
                arduino_port_name=serial_port_info.portName();
                    }}  }
       qDebug()<<"arduino_port name is   :"<<arduino_port_name;

      arduino_is_available = true;

     if(arduino_is_available){

       serial->setPortName(arduino_port_name);

       if(serial->open(QSerialPort::ReadOnly)){
          serial->setBaudRate(QSerialPort::Baud9600);

          serial->setDataBits(QSerialPort::Data8);

          serial->setParity(QSerialPort::NoParity);

          serial->setStopBits(QSerialPort::OneStop);

          serial->setFlowControl(QSerialPort::NoFlowControl);


          return 0 ;


       }
       qDebug()<<"arduino_port name is   :"<<arduino_port_name;
        return 1 ;

     }
 }
 int arduino ::close_arduino()
 {

        if(serial->isOpen())
        {
           serial->close();
           return 0;

        }

       return 1 ;
 }
 QByteArray arduino:: read_from_arduino()
 {

     if(serial->isReadable()){
         data=serial->readAll();
         return data;
     }

 }
 int arduino::write_to_arduino(QByteArray d)
 {
     if(serial->isWritable()){

         serial->write(d);
     }else{
         qDebug() <<"couldnt write to serial !";
     }


 }
void time_slot(void)
 {


 }














