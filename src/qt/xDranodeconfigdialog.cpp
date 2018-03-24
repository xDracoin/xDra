#include "xDranodeconfigdialog.h"
#include "ui_xDranodeconfigdialog.h"

#include <QModelIndex>

xDraNodeConfigDialog::xDraNodeConfigDialog(QWidget *parent, QString nodeAddress, QString privkey) :
    QDialog(parent),
    ui(new Ui::xDraNodeConfigDialog)
{
    ui->setupUi(this);
    QString desc = "rpcallowip=127.0.0.1<br>rpcuser=REPLACEME<br>rpcpassword=REPLACEME<br>server=1<br>listen=1<br>port=REPLACEMEWITHYOURPORT<br>masternode=1<br>masternodeaddr=" + nodeAddress + "<br>masternodeprivkey=" + privkey + "<br>";
    ui->detailText->setHtml(desc);
}

xDraNodeConfigDialog::~xDraNodeConfigDialog()
{
    delete ui;
}
