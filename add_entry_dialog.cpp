#include "add_entry_dialog.h"
#include "ui_add_entry_dialog.h"

add_entry_dialog::add_entry_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_entry_dialog)
{
    ui->setupUi(this);
}

add_entry_dialog::~add_entry_dialog()
{
    delete ui;
}


void add_entry_dialog::on_ok_rejected()
{
    reject();
}

QString add_entry_dialog::barcode()
{
    return ui->BarcodeNo->text();
}

int add_entry_dialog::testtube_slot_no()
{
    return ui->TTSlotNo->value();
}

int add_entry_dialog::teststrip_slot_no()
{
    return ui->TSSlotNo->value();
}

int add_entry_dialog::test_time()
{
    return ui->TestTime->value();
}

QString add_entry_dialog::comments()
{
    return ui->Comments->toPlainText();
}

void add_entry_dialog::on_ok_accepted()
{
    accept();
}
