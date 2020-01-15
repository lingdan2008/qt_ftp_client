#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
//#include <QtNetwork/QNetworkAccessManager>
//#include <QtNetwork/QNetworkReply>
//#include <QUrl>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QDebug>

#include "ftpmanager.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:

private slots:
    void on_pushButton_Download_clicked();

    void on_pushButton_Upload_clicked();

    void error(QNetworkReply::NetworkError err);

private:
    QString getFileName(QString sFilePath);

private:
    Ui::Dialog *ui;

    FtpManager m_ftp;

};

#endif // DIALOG_H
