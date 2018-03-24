#ifndef ADDEDITXDRANODE_H
#define ADDEDITXDRANODE_H

#include <QDialog>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

namespace Ui {
class AddEditxDraNode;
}


class AddEditxDraNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditxDraNode(QWidget *parent = 0);
    ~AddEditxDraNode();

protected:

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_AddEditAddressPasteButton_clicked();
    void on_AddEditPrivkeyPasteButton_clicked();
    void on_AddEditTxhashPasteButton_clicked();

signals:

private:
    Ui::AddEditxDraNode *ui;
};

#endif // ADDEDITXDRANODE_H
