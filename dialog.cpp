#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("FTP client"));
    ui->progressBar->setVisible(false);
    ui->lineEdit->setText("ftp://127.0.0.1:2121");
    ui->lineEdit->setReadOnly(true);
    ui->pushButton_Download->setFocus();
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::initFTP()
{
    QString sUrl = ui->lineEdit->text();
    QUrl url = QUrl(sUrl);
    if(!url.isValid() || ("ftp" != url.scheme())) {
        return false;
    }

    return true;

    qDebug() << "initFTP";
}

void Dialog::replyFinished(QNetworkReply *pReply)
{
    if(QNetworkReply::NoError == m_pReply->error()) {
        m_pReply->deleteLater();

        m_pFile->flush();
        m_pFile->close();
    }
    else {
        QMessageBox::critical(NULL, tr("replyFinished"), "Error!!!");
    }

    qDebug() << "replyFinished";
}

void Dialog::readContent()
{
    m_pFile->write(m_pReply->readAll());

    qDebug() << "readContent";
}

void Dialog::replyError(QNetworkReply::NetworkError error)
{
    QString errStr = m_pReply->errorString();

    //auto metaEnum = QMetaEnum::fromType<QNetworkReply::NetworkError>();
    //auto errStr = metaEnum.valueToKey(error);
    QMessageBox::critical(NULL, tr("replyError"), QString(errStr));

    //m_pFile->deleteLater();
    //m_pFile = Q_NULLPTR;

    m_pReply->deleteLater();

    qDebug() << "replyError";
}

void Dialog::on_pushButton_Download_clicked()
{
    if(initFTP()) {
        QString folderPath = QFileDialog::getExistingDirectory(this, tr("Select an directory"), "", QFileDialog::ShowDirsOnly);
        QString fileName = folderPath + "/download.txt";
        m_pFile = new QFile(fileName);
        m_pFile->open(QIODevice::WriteOnly);

        QUrl url("ftp://127.0.0.1/download.txt");
        url.setPort(2121);

        QNetworkRequest request(url);
        QNetworkAccessManager *pManage = new QNetworkAccessManager(this);
        pManage->setNetworkAccessible(QNetworkAccessManager::Accessible);
        m_pReply = pManage->get(request);

        connect(pManage, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
        connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(replyError(QNetworkReply::NetworkError)));
        connect((QObject *)m_pReply, SIGNAL(readyRead()), SLOT(readContent()));
    }

    qDebug() << "on_pushButton_Download_clicked";
}

void Dialog::on_pushButton_Upload_clicked()
{
    if(initFTP()) {
        QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Select the files"), "", tr("Files (*)"));
        if (!fileList.isEmpty()) {
            for (int i=0; i<fileList.count(); i++) {
                QString filePath = fileList.at(i);
                m_pFile = new QFile(filePath);
                m_pFile->open(QIODevice::ReadOnly);
                QByteArray baData = m_pFile->readAll();
                m_pFile->close();

                //QUrl url;
                //url.setScheme("ftp");
                //url.setHost("127.0.0.1");
                //url.setPort(2121);
                //url.setPath("upload.txt");
                QUrl url("ftp://127.0.0.1/upload.txt");
                url.setPort(2121);

                QNetworkRequest request(url);
                QNetworkAccessManager *pManage = new QNetworkAccessManager(this);
                pManage->setNetworkAccessible(QNetworkAccessManager::Accessible);
                m_pReply = pManage->put(request, baData);

                connect(pManage, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
                connect(m_pReply, SIGNAL(error(QNetworkReply::NetworkError)),SLOT(replyError(QNetworkReply::NetworkError)));
            }
        }
    }

    qDebug() << "on_pushButton_Upload_clicked";
}
