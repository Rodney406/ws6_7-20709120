#ifndef EDITITEMDIALOG_H
#define EDITITEMDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class EditItemDialog;
}
QT_END_NAMESPACE

class EditItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditItemDialog(QWidget *parent = nullptr);
    ~EditItemDialog();

    void setName(const QString &name);
    QString getName() const;

    void setVisibleValue(bool visible);
    bool getVisibleValue() const;

    void setColour(int r, int g, int b);
    int getR() const;
    int getG() const;
    int getB() const;

private:
    Ui::EditItemDialog *ui;
};

#endif // EDITITEMDIALOG_H
