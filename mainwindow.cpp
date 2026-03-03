#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edititemdialog.h"

#include <QStandardItemModel>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Tree model
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

    // Buttons + status bar
    connect(ui->addButton, &QPushButton::clicked, this, [this]() {
        statusBar()->showMessage("Add clicked", 2000);
    });

    connect(ui->removeButton, &QPushButton::clicked, this, [this]() {
        statusBar()->showMessage("Remove clicked", 2000);
    });

    // Context menu
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
                    EditItemDialog dlg(this);
                    dlg.exec();
                }
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}
