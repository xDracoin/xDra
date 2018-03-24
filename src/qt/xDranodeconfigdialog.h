#ifndef XDRANODECONFIGDIALOG_H
#define XDRANODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class xDraNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class xDraNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit xDraNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "123.456.789.123:19700", QString privkey="MASTERNODEPRIVKEY");
    ~xDraNodeConfigDialog();

private:
    Ui::xDraNodeConfigDialog *ui;
};

#endif // XDRANODECONFIGDIALOG_H
