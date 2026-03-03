#include "edititemdialog.h"
#include "ui_edititemdialog.h"

EditItemDialog::EditItemDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditItemDialog)
{
    ui->setupUi(this);
}

EditItemDialog::~EditItemDialog()
{
    delete ui;
}
