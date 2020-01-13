#include "ftpmanager.h"

FtpManager::FtpManager(QObject *parent) : QObject(parent)
{
    m_url.setScheme("ftp");

    qDebug() << "FtpManager::FtpManager";
}

void FtpManager::put(QString fileName, QString urlFile)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QByteArray data = file.readAll();
    m_url.setPath(urlFile);

    QNetworkReply *pReply = m_manager.put(QNetworkRequest(m_url), data);

    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));

    qDebug() << "FtpManager::put";
}

void FtpManager::get(QString urlFile, QString fileName)
{
    m_file.setFileName(fileName);
    m_file.open(QIODevice::WriteOnly);

    m_url.setPath(urlFile);
    QNetworkReply *pReply = m_manager.get(QNetworkRequest(m_url));
    m_manager.setNetworkAccessible(QNetworkAccessManager::Accessible);

    connect(pReply, SIGNAL(finished()), this, SLOT(downloadFinished()));
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));

    qDebug() << "FtpManager::get";
}

void FtpManager::setHostInfo(QString host, int port)
{
    m_url.setHost(host);
    m_url.setPort(port);

    qDebug() << "FtpManager::setHostInfo";
}

void FtpManager::setUserInfo(QString name, QString password)
{
    m_url.setUserName(name);
    m_url.setPassword(password);

    qDebug() << "FtpManager::setUserInfo";
}

void FtpManager::downloadFinished()
{
    QNetworkReply *pReply = qobject_cast<QNetworkReply*>(sender());
    switch (pReply->error()) {
    case QNetworkReply::NoError:
        m_file.write(pReply->readAll());
        m_file.flush();
        qDebug() << "FtpManager::NoError";
        break;
    default:
        qDebug() << pReply->errorString();
        break;
    }

    m_file.close();
    pReply->deleteLater();

    qDebug() << "FtpManager::downloadFinished";
}
