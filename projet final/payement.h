#ifndef PAYEMENT_H
#define PAYEMENT_H
#include<QSqlQueryModel>
#include<QString>

class payement
{
public:
    payement();
    payement(int,QString,QString,QString);
    bool verifiernum(int );
     bool ajouter();
     QSqlQueryModel* afficher();
     bool modifier(int,QString ,QString,QString);
     bool supprimer(int);
     QSqlQueryModel * rechercher(int );
      QSqlQueryModel * tridesc();
      QSqlQueryModel * triasc();
       QString  apercu_pdf();

private:
int num_interv;
QString montant;
QString mode_p;
QString date_op;



};

#endif // PAYEMENT_H
