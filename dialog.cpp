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

    m_ftp.setHostInfo("127.0.0.1", 2121);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_Download_clicked()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Select an directory"), "", QFileDialog::ShowDirsOnly);
    QString fileName = folderPath + "/download.txt";

    m_ftp.get("download.txt", fileName);

    qDebug() << "Dialog::on_pushButton_Download_clicked";
}

void Dialog::on_pushButton_Upload_clicked()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this, tr("Select the files"), "", tr("Files (*)"));
    if (!fileList.isEmpty()) {
        for (int i=0; i<fileList.count(); i++) {
            QString filePath = fileList.at(i);

            m_ftp.put(filePath, "upload.txt");
        }
    }

    qDebug() << "Dialog::on_pushButton_Upload_clicked";
}

void Dialog::error(QNetworkReply::NetworkError err)
{
    switch (err) {
    case QNetworkReply::HostNotFoundError :
        qDebug() << QString::fromLocal8Bit("主机没有找到");
        break;
    default:
        break;
    }

    qDebug() << "Dialog::error";
}
