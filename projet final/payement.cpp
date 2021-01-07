#include "payement.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QDebug>
#include <QSqlQueryModel>
#include<QLineEdit>
#include<QString>
#include "ui_mainwindow.h"
#include<QComboBox>

payement::payement()
{

    num_interv=0;
     montant="";
     mode_p="";
     date_op="";
}
payement::payement(int num_interv,QString montant,QString mode_p,QString date_op)
{

     this->num_interv=num_interv;
     this->montant=montant;
     this->mode_p=mode_p;
     this->date_op=date_op;

}
bool payement::verifiernum(int num_interv)
{

    QSqlQuery query;
    QString n;

            query.exec("SELECT NUM_DOSSIER from DOCMEDICALE ");
            if (query.value(num_interv)==0)
            {
                n=query.value("NUM_INTERV").toString();
                if (n==num_interv)
                {
                    return true;
                }
            }
    return false;

      }

bool payement::ajouter()
{

    QString num_string=QString::number(num_interv);

    QSqlQuery query;
          query.prepare("INSERT INTO payement (num_interv, montant, mode_p,date_op) "
                        "VALUES (:id, :forename, :surname, :date)");

          query.bindValue(":id",num_string);
          query.bindValue(":forename",montant);
          query.bindValue(":surname",mode_p);
          query.bindValue(":date",date_op);
           return query.exec();


}
QSqlQueryModel*  payement::afficher()
{


    QSqlQueryModel *model = new QSqlQueryModel;
          model->setQuery("SELECT * FROM payement");
    return model;

}
bool payement::modifier(int num_interv,QString montant,QString mode_p,QString date_op){
    QSqlQuery query;

    QString num_string= QString::number(num_interv);

    query.prepare("UPDATE payement SET  MONTANT = :m, MODE_P= :mode,DATE_OP= :da  WHERE NUM_INTERV = :num ");
    query.bindValue(":num",num_string);
    query.bindValue(":m",montant);
    query.bindValue(":mode",mode_p);
     query.bindValue(":da",date_op);

    return  query.exec();
}

bool payement:: supprimer(int num_interv)
{

    QSqlQuery query;
          query.prepare("delete from payement where NUM_INTERV= :num");
          query.bindValue(":num",num_interv);

           return query.exec();

}
QSqlQueryModel * payement::  rechercher(int num_interv )
{
    QString num_string=QString::number(num_interv);
    QSqlQueryModel * model= new QSqlQueryModel();
    model-> setQuery("SELECT * FROM payement  where NUM_INTERV = "+num_string);


    return model;

}

 QSqlQueryModel * payement::  tridesc()
 {

     QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from payement  order by NUM_INTERV  ");

     return model;

 }
 QSqlQueryModel * payement::  triasc()
 {

     QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from payement  order by NUM_INTERV ASC  ");

     return model;

 }
 QString payement:: apercu_pdf()
  {
      QString text="             ** Les payement  **       \n \n " ;
      QSqlQuery query ;
      QString i,x,z,n;


       query.exec("select * from payement ");
       while (query.next())
       {
          i=query.value(0).toString();
           x=query.value(1).toString();
           z=query.value(2).toString();
           n=query.value(3).toString();

         text += "\n num dossier medicale: "+i+"\n - date de creation : "+ x+"\n  - - id patient : "+ z+"\n_____________\n";
      }

              return text ;
  }



