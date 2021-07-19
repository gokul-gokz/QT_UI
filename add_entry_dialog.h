#ifndef ADD_ENTRY_DIALOG_H
#define ADD_ENTRY_DIALOG_H

#include <QDialog>

namespace Ui {
class add_entry_dialog;
}

class add_entry_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_entry_dialog(QWidget *parent = 0);

    QString barcode();
    int testtube_slot_no();
    int teststrip_slot_no();
    int test_time();
    QString comments();

    ~add_entry_dialog();
private slots:

    void on_ok_rejected();

    void on_ok_accepted();

private:
    Ui::add_entry_dialog *ui;

};

#endif // ADD_ENTRY_DIALOG_H
