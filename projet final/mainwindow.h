#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"dossiermedicale.h"
#include <QMainWindow>
#include <QPropertyAnimation>
#include "consultation.h"
#include "payement.h"
#include"arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pushButton_2_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_rech_doc_clicked();

    void on_annuler_modif_clicked();

    void on_anuuler_ajout_clicked();

    void on_trie_doc_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_consulter_clicked();

    void on_Impdos_clicked();

    void on_Impdoc_clicked();
    
    void on_ajouterconsu_clicked();

    void on_pushButton_6_clicked();

    void on_Quitterc_clicked();

    void on_supc_clicked();

    void on_rechc_clicked();

    void on_triec_clicked();

    void on_modif_clicked();

    void on_Impdos_2_clicked();

    void on_refrech_aj_clicked();

    void on_refrech_mod_clicked();

    void on_pushButton_5_clicked();

    void on_ajout_payement_clicked();

    void on_refrech_num_p_clicked();

    void on_pushButton_7_clicked();

    void on_refrech_numinterpa_clicked();

    void on_quitter_p_clicked();

    void on_modifier_p_clicked();

    void on_supprimer_payement_clicked();

    void on_refreh_sup_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::MainWindow *ui;
    dossiermedicale d_temp;
    dossiermedicale tab;
    consultation c_temp;
    payement p_temp;
    QPropertyAnimation *animation;
   arduino a;
    QByteArray data;
     int timerId;
protected:
    void timerEvent(QTimerEvent *event);

};

#endif // MAINWINDOW_H
