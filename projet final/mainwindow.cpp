#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dossiermedicale.h"
#include "consultation.h"
#include "payement.h"
#include <QDate>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableView>
#include <QPrinter>
#include <QPrintDialog>
#include <QMessageBox>
#include<QString>
#include<QMediaPlayer>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QComboBox>
#include<QObject>
#include"arduino.h"
#include"string.h"

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabdossier->setModel(d_temp.afficher());
    ui->tabconsu->setModel(c_temp.afficher());
    ui->tabpayement->setModel(p_temp.afficher());
 int ret=a.connect_arduino();
    switch(ret){
    case(0):qDebug()<<"arduino is available and  connected  to :"<<a.getarduino_port_name();
        timerId = startTimer(1000);
        break;
    case(1):qDebug()<<"arduino is available but not connected to"<<a.getarduino_port_name();
        break;
    case(-1):qDebug()<<"arduino is not available";
    }

    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{

    int num=ui->le_num->text().toInt();
QString datec=ui->le_date_ajout->date().toString();
   // QString id_p=ui->le_id->text();
QString id_p= ui->comboBox1->currentText();




    QString numbers = "123456789";
// bool verifHedhi = false;
  //bool verif_id_p=true;
  bool verif_num=true;
 /*for(int i = 0; i < id_p.length(); i++){
               for(int j = 0; j < numbers.length(); j++){

                   if(id_p[i] == numbers[j]){
                                         verifHedhi = true;      // test sur id_p numero
                                     }
               }
               if(verifHedhi == false ){
                                 verif_id_p = false;
                                 QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                             QObject::tr("id_p il faut que un numero .\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);

                                 break;
                             }
                         }*/
 if (num ==0){
                      verif_num = false;
                      QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("il faut que le numero de dossier different de 0 .\n"//test num
                                              "Click Cancel to exit."), QMessageBox::Cancel);
              }




//if((verif_num==true)&&(verif_id_p==true)){
    if(verif_num==true){

dossiermedicale d(num,datec,id_p);
    QMessageBox msg;
    bool testt=d.verifierId(id_p);
            if(testt)
             {
                 QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                             QObject::tr(" id patient déjà existant !.\n"
                                         "Click Ok to exit."), QMessageBox::Ok);

               }
            else

    {
                bool test=d.ajouter();
                if(test){


        ui->tabdossier->setModel(d_temp.afficher());
         msg.setText("Ajout avec succes");
    }

        else {
        msg.setText("Echec au niveau de lajout d un dossier medicale");
    }
    msg.exec();
    }
}
}



void MainWindow::on_pushButton_2_clicked()
{
    dossiermedicale d;
   // int num=ui->le_num_sup->text().toInt();
    int num= ui->com->currentText().toInt();
    /*bool verif_num=true;
    bool testt=d.verifiernum(num);
    if (num ==0) {
                          verif_num = false;
                         QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                     QObject::tr("il faut que le numero de dossier different de 0 .\n"//test num
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
                 }

            if(testt==true)
             {
                 QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                             QObject::tr(" num dossier n existant pas !.\n"
                                         "Click Ok to exit."), QMessageBox::Ok);

               }

   if((verif_num==true)&&(testt==false)){*/
     bool test=d_temp.supprimer(num);
     QMessageBox msg;
     if(test)
     {

         msg.setText("suppression avec succes");
 ui->tabdossier->setModel(d_temp.afficher());

     }

         else {
         msg.setText("Echec au niveau de la suppression d un dossier medicale");
     }
     msg.exec();

}

void MainWindow::on_pushButton_3_clicked()
{
    int num=ui->le_num_modif->text().toInt();
     QString datec=ui->le_date_modif->date().toString();
  //  QString id_p = ui->le_idpatient_modif->text();
     QString id_p= ui->comboBox3->currentText();



    dossiermedicale d(num,datec,id_p);
    QMessageBox msg;
    bool test=d.modifier(num,datec,id_p);
   // bool verif_id=true;
    bool verif_num=true;
    if (num ==0){
                          verif_num = false;
                         QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                     QObject::tr("il faut que le numero de dossier different de 0 .\n"//test num
                                                 "Click Cancel to exit."), QMessageBox::Cancel);}

                        /* if ((id_p ==0)&&(id_p=="")) {
                                               verif_id = false;
                                              QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                                          QObject::tr("il faut que le id de patient different de 0 .\n"//test num
                                                                      "Click Cancel to exit."), QMessageBox::Cancel);}*/
    if((test)&&(verif_num ))//&&(verif_id ))
    {
        ui->le_num_modif->clear();
        ui->le_date_modif->clear();
        //ui->le_idpatient_modif->clear();
 ui->tabdossier->setModel(d_temp.afficher());

        msg.setText("modifiction avec succes");


    }

        else {
        msg.setText("Echec au niveau de la modification d un dossier medicale");
    }
    msg.exec();

}
//}
//}

void MainWindow::on_rech_doc_clicked()
{
    QString id_p = ui->lineEdit->text();

    ui->tabdossier->setModel(d_temp.rechercher(id_p));



}

void MainWindow::on_annuler_modif_clicked()
{
    ui->le_num_modif->clear();
    ui->le_date_modif->clear();//annuler ajout
    //ui->le_idpatient_modif->clear();
}



void MainWindow::on_trie_doc_clicked()
{
    ui->tabdossier->setModel(d_temp.tridesc());
}



/*void MainWindow::on_consulter_clicked()
{
    QString id_p = ui->le_id->text();
    ui->tabdos1->setModel(tab.consulter(id_p));
}*/




void MainWindow::on_Impdos_clicked()
{
    //pour imprimer
                dossiermedicale ds;
                     QString text=ds.apercu_pdf();
                     ui->imprimer->setText(text);

                     QPrinter printer ;
                     printer.setPrinterName("imprim");
                     QPrintDialog dialog (&printer,this);
                     if(dialog.exec()==QDialog::Rejected) return ;
                     ui->imprimer->print(&printer);
}



void MainWindow::on_anuuler_ajout_clicked()
{



    ui->le_num->clear();
    ui->le_date_ajout->clear();//annuler modif
    //ui->le_id->clear();
}


void MainWindow::on_ajouterconsu_clicked()
{
     int num= ui->combondc->currentText().toInt();
    //int num=ui->numc->text().toInt();
    int num_interv=ui->nintervaj->text().toInt();
    QString date_inter=ui->dinteraj->date().toString();
    QString probl=ui->probaj->text();
    int tension=ui->tnaj->text().toInt();
    int glycemie=ui->glaj->text().toInt();
    int poids=ui->pdaj->text().toInt();
    int taille=ui->tlaj->text().toInt();
    QString ordonnance=ui->ordaj->text();

    QString num_tension= QString::number(tension);
     QString num_glycemie= QString::number(glycemie);//convertir les int en chaine
QString num_poids= QString::number(poids);
QString num_taille= QString::number(taille);

 QString numbers = "123456789";
 bool verif_tension=false;
  bool verif_glycemie=false;
  bool verif_poids=false;
   bool verif_taille=false;

 bool verif_num=true;

  for(int i = 0; i < num_tension.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_tension[i] == numbers[j]){
                                          verif_tension = true;      // test sur id_p numero
                                      }
                }
                if(verif_tension == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que le tension un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }

  for(int i = 0; i < num_glycemie.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_glycemie[i] == numbers[j]){
                                          verif_glycemie = true;      // test sur id_p numero
                                      }
                }
                if(verif_glycemie == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que le glycemie un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  for(int i = 0; i < num_poids.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_poids[i] == numbers[j]){
                                          verif_poids = true;      // test sur id_p numero
                                      }
                }
                if(verif_poids == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que le poids un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  for(int i = 0; i < num_taille.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_taille[i] == numbers[j]){
                                          verif_taille = true;      // test sur id_p numero
                                      }
                }
                if(verif_taille == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que la taille un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }



 if ((num ==0)||(num_interv==0)){
                      verif_num = false;
                      QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("il faut que le numero de dossier different et num inter <> 0 .\n"//test num
                                              "Click Cancel to exit."), QMessageBox::Cancel);
              }

           else

    {
     consultation c( num, num_interv, date_inter, probl, tension, glycemie, poids, taille,ordonnance);
         QMessageBox msg;
                bool test=c.ajouter();
                if((test)&&(verif_poids==true)&&(verif_num==true)&&(verif_taille==true)&&(verif_tension==true)&&(verif_glycemie==true))
                {


       ui->tabconsu->setModel(c_temp.afficher());
         msg.setText("Ajout avec succes");
    }

        else {
        msg.setText("Echec au niveau de lajout d un dossier medicale");
    }
    msg.exec();

}

}



void MainWindow::on_Quitterc_clicked()
{
    ui->le_num->clear();
    ui->le_date_ajout->clear();//annuler modif
    //ui->le_id->clear();
    //ui->numc->clear();
         ui->nintervaj->clear();
        ui->dinteraj->clear();
         ui->probaj->clear();
        ui->tnaj->clear();
      ui->glaj->clear();
       ui->pdaj->clear();
     ui->tlaj->clear();
       ui->ordaj->clear();
}

void MainWindow::on_supc_clicked()
{
    consultation c;
   // int num_interv=ui->numinsup->text().toInt();
   // QString num_inter= QString::number(num_interv);
    int num_interv= ui->combnic->currentText().toInt();
   // bool verif_num=true;
   /* QString numbers = "123456789";
    bool verif_inter=false;

    for(int i = 0; i < num_inter.length(); i++){
                  for(int j = 0; j < numbers.length(); j++){

                      if(num_inter[i] == numbers[j]){
                                            verif_inter = true;
                                        }
                  }
                  if(verif_inter == false ){

                                    QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                                QObject::tr("il faut que le num interv est un numero .\n"
                                                            "Click Cancel to exit."), QMessageBox::Cancel);

                                    break;
                                }
                            }*/

    /*if (num_interv ==0) {
                          verif_num = false;
                         QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                     QObject::tr("il faut que le numero dintervention different de 0 .\n"//test num
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
                 }*/


    bool test=c_temp.supprimer(num_interv);
    QMessageBox msg;

     if (test)//&&(verif_num))//&&(verif_inter = true))
     {
         ui->tabconsu->setModel(c_temp.afficher());
         msg.setText("suppression avec succes");

     }

         else {
         msg.setText("Echec au niveau de la suppression de consultation");
     }
     msg.exec();


}

void MainWindow::on_rechc_clicked()
{
int num_interv=ui->intervcherch->text().toInt();
ui->tabconsu->setModel(c_temp.rechercher(num_interv));
}

void MainWindow::on_triec_clicked()
{
    ui->tabconsu->setModel(c_temp.tridesc());


}


void MainWindow::on_modif_clicked()
{
    int num= ui->combondc->currentText().toInt();
    int num_interv=ui->nintervaj->text().toInt();
    QString date_inter=ui->dinteraj->date().toString();
    QString probl=ui->probaj->text();
    int tension=ui->tnaj->text().toInt();
    int glycemie=ui->glaj->text().toInt();
    int poids=ui->pdaj->text().toInt();
    int taille=ui->tlaj->text().toInt();
    QString ordonnance=ui->ordaj->text();



    QString num_tension= QString::number(tension);
     QString num_glycemie= QString::number(glycemie);//convertir les int en chaine
QString num_poids= QString::number(poids);
QString num_taille= QString::number(taille);

 QString numbers = "123456789";
 bool verif_tension=false;
  bool verif_glycemie=false;
  bool verif_poids=false;
   bool verif_taille=false;

 bool verif_num=true;

  for(int i = 0; i < num_tension.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_tension[i] == numbers[j]){
                                          verif_tension = true;      // test sur id_p numero
                                      }
                }
                if(verif_tension == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que le tension un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }

  for(int i = 0; i < num_glycemie.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_glycemie[i] == numbers[j]){
                                          verif_glycemie = true;      // test sur id_p numero
                                      }
                }
                if(verif_glycemie == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que le glycemie un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  for(int i = 0; i < num_poids.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_poids[i] == numbers[j]){
                                          verif_poids = true;      // test sur id_p numero
                                      }
                }
                if(verif_poids == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que le poids un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }
  for(int i = 0; i < num_taille.length(); i++){
                for(int j = 0; j < numbers.length(); j++){

                    if(num_taille[i] == numbers[j]){
                                          verif_taille = true;      // test sur id_p numero
                                      }
                }
                if(verif_taille == false ){

                                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                              QObject::tr("il faut que la taille un numero .\n"
                                                          "Click Cancel to exit."), QMessageBox::Cancel);

                                  break;
                              }
                          }




 if ((num ==0)||(num_interv==0)){
                      verif_num = false;
                      QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("il faut que le numero de dossier different et num inter <> 0 .\n"//test num
                                              "Click Cancel to exit."), QMessageBox::Cancel);
              }

           else

    {
     consultation c(num, num_interv, date_inter, probl, tension, glycemie, poids, taille,ordonnance);
         QMessageBox msg;
                bool test=c.modifier(num, num_interv, date_inter, probl, tension, glycemie, poids, taille,ordonnance);
                if((test)&&(verif_poids==true)&&(verif_num==true)&&(verif_taille==true)&&(verif_tension==true)&&(verif_glycemie==true))
                {


       ui->tabconsu->setModel(c_temp.afficher());
         msg.setText("modification avec succes");
    }

        else {
        msg.setText("Echec au niveau de modification consultation");
    }
    msg.exec();

}


}

void MainWindow::on_Impdos_2_clicked()
{
    consultation c;
         QString text=c.apercu_pdf();
         ui->impc->setText(text);

         QPrinter printer ;
         printer.setPrinterName("imprim");
         QPrintDialog dialog (&printer,this);
         if(dialog.exec()==QDialog::Rejected) return ;
         ui->impc->print(&printer);
}


void MainWindow::on_refrech_aj_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select ID_PATIENT from PATIENT");
    qry->exec();
    model->setQuery(*qry);
    ui->comboBox1->setModel(model);
}

void MainWindow::on_refrech_mod_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select ID_PATIENT from PATIENT");
    qry->exec();
    model->setQuery(*qry);
    ui->comboBox3->setModel(model);
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select NUM_DOSSIER from DOCMEDICALE");//
    qry->exec();
    model->setQuery(*qry);
    ui->com->setModel(model);
}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select NUM_DOSSIER from DOCMEDICALE");//
    qry->exec();
    model->setQuery(*qry);
    ui->combondc->setModel(model);
}

void MainWindow::on_pushButton_5_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select NUM_INTERV from CONSULTATION");//
    qry->exec();
    model->setQuery(*qry);
    ui->combnic->setModel(model);

}



void MainWindow::on_pushButton_7_clicked()
{
int num_interv= ui->com_2->currentText().toInt();
QString montant=ui->montant->text();
QString mode_p=ui->mode->text();
QString date_op=ui->dateop->date().toString();


QString caractere="azertyuiopmlkjhgfdsqwxcvbn";
QString numbers = "123456789";
bool verifHedhi = false;
bool verif_modep=true;
bool verif_montant=true;
bool verifHedhi1= false;



for(int i = 0; i < montant.length(); i++){
           for(int j = 0; j < numbers.length(); j++){

               if(montant[i] == numbers[j]){
                                     verifHedhi = true;      // test sur id_p numero
                                 }
           }
           if(verifHedhi == false ){

                             QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                         QObject::tr("id il faut que le montant de labo est un numero .\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);

                             break;
                         }
                     }
if ((mode_p =="0")||(mode_p =="")){
                  verif_modep = false;
                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                              QObject::tr("il faut que le mode de payement different de vide et dif de 0.\n"//test num
                                          "Click Cancel to exit."), QMessageBox::Cancel);
          }
if ((montant =="0")||(montant =="")){
                  verif_modep = false;
                  QMessageBox::information(nullptr, QObject::tr("Erreur"),
                              QObject::tr("il faut que le montant different de vide et dif de 0.\n"//test num
                                          "Click Cancel to exit."), QMessageBox::Cancel);
          }



for(int i = 0; i < mode_p.length(); i++){
         for(int j = 0; j < caractere.length(); j++){

             if(mode_p[i] == caractere[j]){
                                   verifHedhi1 = true;      // test sur id_p numero
                               }
         }
         if(verifHedhi1 == false ){

                           QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                       QObject::tr("id il faut que le mode de payement   est un caractere .\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);

                           break;
                       }
                   }







if((verif_montant==true)&&(verifHedhi==true)&&( verif_modep==true)&&(verifHedhi1==true)){

payement p(num_interv,montant,mode_p,date_op);
QMessageBox msg;
bool testt=p.verifiernum(num_interv);
        if(testt)
         {
             QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                         QObject::tr(" num intervention déjà existant !.\n"
                                     "Click Ok to exit."), QMessageBox::Ok);

           }
        else

{
            bool test=p.ajouter();
            if(test){


  ui->tabpayement->setModel(p_temp.afficher());
     msg.setText("Ajout avec succes");
}

    else {
    msg.setText("Echec au niveau de lajout d un payementt");
}
msg.exec();
}
}


}

void MainWindow::on_refrech_numinterpa_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select NUM_INTERV from CONSULTATION");//
    qry->exec();
    model->setQuery(*qry);
    ui->com_2->setModel(model);
}

void MainWindow::on_quitter_p_clicked()
{
    ui->com_2->clear();
    ui->montant->clear();
   ui->mode->clear();
    ui->dateop->clear();
}

void MainWindow::on_modifier_p_clicked()
{
    int num_interv= ui->com_2->currentText().toInt();
    QString montant=ui->montant->text();
    QString mode_p=ui->mode->text();
    QString date_op=ui->dateop->date().toString();


    QString caractere="azertyuiopmlkjhgfdsqwxcvbn";
    QString numbers = "123456789";
    bool verifHedhi = false;
    bool verif_modep=true;
    bool verif_montant=true;
    bool verifHedhi1= false;



    for(int i = 0; i < montant.length(); i++){
               for(int j = 0; j < numbers.length(); j++){

                   if(montant[i] == numbers[j]){
                                         verifHedhi = true;      // test sur id_p numero
                                     }
               }
               if(verifHedhi == false ){

                                 QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                             QObject::tr(" il faut que le montant de labo est un numero .\n"
                                                         "Click Cancel to exit."), QMessageBox::Cancel);

                                 break;
                             }
                         }
    if ((mode_p =="0")||(mode_p =="")){
                      verif_modep = false;
                      QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("il faut que le mode de payement different de vide et dif de 0.\n"//test num
                                              "Click Cancel to exit."), QMessageBox::Cancel);
              }
    if ((montant =="0")||(montant =="")){
                      verif_modep = false;
                      QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                  QObject::tr("il faut que le montant different de vide et dif de 0.\n"//test num
                                              "Click Cancel to exit."), QMessageBox::Cancel);
              }



    for(int i = 0; i < mode_p.length(); i++){
             for(int j = 0; j < caractere.length(); j++){

                 if(mode_p[i] == caractere[j]){
                                       verifHedhi1 = true;      // test sur id_p numero
                                   }
             }
             if(verifHedhi1 == false ){

                               QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                           QObject::tr("id il faut que le mode de payement est un caractere .\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);

                               break;
                           }
                       }







    if((verif_montant==true)&&(verifHedhi==true)&&( verif_modep==true)&&(verifHedhi1==true)){

    payement p(num_interv,montant,mode_p,date_op);
    QMessageBox msg;
    bool testt=p.verifiernum(num_interv);
            if(testt)
             {
                 QMessageBox::critical(nullptr, QObject::tr("Ajouter une Annonce"),
                             QObject::tr(" numero abo déjà existant !.\n"
                                         "Click Ok to exit."), QMessageBox::Ok);

               }
            else

    {
                bool test=p.modifier(num_interv,montant,mode_p,date_op);
                if(test){


      ui->tabpayement->setModel(p_temp.afficher());
         msg.setText("Ajout avec succes");
    }

        else {
        msg.setText("Echec au niveau de lajout d un abonnement");
    }
    msg.exec();
    }
}
}

void MainWindow::on_supprimer_payement_clicked()
{
    payement p;

    int num_interv= ui->combosuppp->currentText().toInt();


    bool test=p_temp.supprimer(num_interv);
    QMessageBox msg;

     if (test)
     {
         ui->tabpayement->setModel(p_temp.afficher());
         msg.setText("suppression avec succes");

     }

         else {
         msg.setText("Echec au niveau de la suppression de payement");
     }
     msg.exec();
}

void MainWindow::on_refreh_sup_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery* qry=new QSqlQuery();
    qry->prepare("select NUM_INTERV from CONSULTATION");//
    qry->exec();
    model->setQuery(*qry);
    ui->combosuppp->setModel(model);
}

void MainWindow::on_pushButton_6_clicked()
{
    int num_interv=ui->rech_n_p->text().toInt();
    ui->tabpayement->setModel(p_temp.rechercher(num_interv));
}

void MainWindow::on_pushButton_8_clicked()
{
 ui->tabpayement->setModel(p_temp.tridesc());
}

void MainWindow::on_pushButton_9_clicked()
{
    ui->tabpayement->setModel(p_temp.triasc());
}

void MainWindow::on_pushButton_10_clicked()
{
    payement p;
         QString text=p.apercu_pdf();
         ui->improumer->setText(text);

         QPrinter printer ;
         printer.setPrinterName("imprim");
         QPrintDialog dialog (&printer,this);
         if(dialog.exec()==QDialog::Rejected) return ;
         ui->improumer->print(&printer);
}
void MainWindow::timerEvent(QTimerEvent *event)
{

   QString ss=QString::fromUtf8(a.read_from_arduino()); // 9rina mel arduino

   int i=0;
   for(int j=0;j<4;j++)
   {
       if(ss[j].isNumber())
       {

           i=i*10+ss[j].digitValue();
       }

   }
   qDebug() << i;
   if(i<900)
       QMessageBox::information(nullptr, QObject::tr("database is open"),
                   QObject::tr("alarme de feu .\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);

}
