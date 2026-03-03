#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>

namespace Ui {
class EditItemDialog;
}

class EditItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditItemDialog(QWidget *parent = nullptr);
    ~EditItemDialog();

private:
    Ui::EditItemDialog *ui;
};

#endif // EDITITEMDIALOG_H
