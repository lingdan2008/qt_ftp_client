#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QMetaEnum>
#include <QMessageBox>
#include <QDebug>

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
    bool initFTP();

    void replyFinished(QNetworkReply *);

    void readContent();

    void replyError(QNetworkReply::NetworkError);

private slots:
    void on_pushButton_Download_clicked();

    void on_pushButton_Upload_clicked();

private:
    Ui::Dialog *ui;

    QFile *m_pFile;
    QNetworkReply *m_pReply;
};

#endif // DIALOG_H
