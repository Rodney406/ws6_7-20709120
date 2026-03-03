#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edititemdialog.h"

#include <QStandardItemModel>
#include <QMenu>
#include <QBrush>
#include <QColor>
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(QStringList() << "Parts");

    auto *root = model->invisibleRootItem();

    auto *top1 = new QStandardItem("TopLevel 0");
    top1->appendRow(new QStandardItem("Child 0,0"));
    top1->appendRow(new QStandardItem("Child 0,1"));
    root->appendRow(top1);

    auto *top2 = new QStandardItem("TopLevel 1");
    top2->appendRow(new QStandardItem("Child 1,0"));
    root->appendRow(top2);

    ui->treeView->setModel(model);
    ui->treeView->expandAll();

    connect(ui->addButton, &QPushButton::clicked, this, [this]() {
        statusBar()->showMessage("Add clicked", 2000);
    });

    connect(ui->removeButton, &QPushButton::clicked, this, [this]() {
        statusBar()->showMessage("Remove clicked", 2000);
    });

    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->treeView, &QWidget::customContextMenuRequested,
            this, [this](const QPoint &pos)
            {
                QModelIndex index = ui->treeView->indexAt(pos);
                if (!index.isValid())
                    return;

                QMenu menu(this);
                QAction *editAction = menu.addAction("Edit...");

                QAction *selected = menu.exec(
                    ui->treeView->viewport()->mapToGlobal(pos)
                    );

                if (selected == editAction)
                {
                    QStandardItem *item = model->itemFromIndex(index);
                    if (!item)
                        return;

                    EditItemDialog dlg(this);

                    dlg.setName(item->text());

                    bool visible = item->data(Qt::UserRole + 1).toBool();
                    dlg.setVisibleValue(visible);

                    QColor colour = item->data(Qt::UserRole + 2).value<QColor>();
                    if (!colour.isValid())
                        colour = Qt::black;

                    dlg.setColour(colour.red(), colour.green(), colour.blue());

                    if (dlg.exec() == QDialog::Accepted)
                    {
                        item->setText(dlg.getName());
                        item->setData(dlg.getVisibleValue(), Qt::UserRole + 1);

                        QColor newColour(dlg.getR(), dlg.getG(), dlg.getB());
                        item->setData(newColour, Qt::UserRole + 2);
                        item->setForeground(QBrush(newColour));

                        statusBar()->showMessage("Item updated", 2000);
                    }
                }
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QModelIndex index = ui->treeView->currentIndex();
    if (!index.isValid())
    {
        statusBar()->showMessage("Please select an item first", 3000);
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open File"),
        "C:\\",
        tr("All Files (*.*)")
        );

    if (filePath.isEmpty())
        return;

    QStandardItem *item = model->itemFromIndex(index);
    if (!item)
        return;

    QFileInfo fileInfo(filePath);
    item->setText(fileInfo.fileName());

    statusBar()->showMessage(filePath, 3000);
}
