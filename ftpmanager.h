#ifndef FTPMANAGER_H
#define FTPMANAGER_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

class FtpManager : public QObject
{
    Q_OBJECT
public:
    explicit FtpManager(QObject *parent = nullptr);

    void put(QString fileName, QString urlFile);

    void get(QString urlFile, QString fileName);

    void setHostInfo(QString host, int port);

    void setUserInfo(QString name, QString password);

signals:
    void error(QNetworkReply::NetworkError);

    void downloadProcess(qint64 nReceive, qint64 nTotal);

    void uploadProcess(qint64 nSent, qint64 nTotal);

private slots:
    void downloadFinished();

private:
    QUrl m_url;
    QFile m_file;
    QNetworkAccessManager m_manager;
};

#endif // FTPMANAGER_H
