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

void EditItemDialog::setName(const QString &name)
{
    ui->nameLineEdit->setText(name);
}

QString EditItemDialog::getName() const
{
    return ui->nameLineEdit->text();
}

void EditItemDialog::setVisibleValue(bool visible)
{
    ui->visibleCheckBox->setChecked(visible);
}

bool EditItemDialog::getVisibleValue() const
{
    return ui->visibleCheckBox->isChecked();
}

void EditItemDialog::setColour(int r, int g, int b)
{
    ui->rSpinBox->setValue(r);
    ui->gSpinBox->setValue(g);
    ui->bSpinBox->setValue(b);
}

int EditItemDialog::getR() const
{
    return ui->rSpinBox->value();
}

int EditItemDialog::getG() const
{
    return ui->gSpinBox->value();
}

int EditItemDialog::getB() const
{
    return ui->bSpinBox->value();
}
