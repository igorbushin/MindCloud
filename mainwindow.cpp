#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    model = new MainModel;
    ui->setupUi(this);
    ui->graphView->setModel(model);
    QMenu *menuData = new QMenu("Data");
    QMenu *menuEdit = new QMenu("Edit");
    menuBar()->addMenu(menuData);
    menuBar()->addMenu(menuEdit);
    menuData->addAction("Save data", model, &MainModel::saveData, Qt::CTRL | Qt::Key_S);
    menuData->addAction("Load data", model, &MainModel::loadData, Qt::CTRL | Qt::Key_O);
    menuEdit->addAction("Create new node", this, [=](){model->createNode(ui->graphView->getCenterOnScene());}, Qt::CTRL | Qt::Key_N);
    menuEdit->addAction("Link selected nodes", model, &MainModel::linkSelectedNodes, Qt::CTRL | Qt::Key_L);
    menuEdit->addAction("Delete selected nodes", model, &MainModel::deleteSelectedNodes, Qt::CTRL | Qt::Key_R);
    menuEdit->addAction("Delete selected links", model, &MainModel::deleteSelectedLinks, Qt::SHIFT | Qt::Key_R);
    menuEdit->addAction("Select all", ui->graphView, &GraphView::selectAll, Qt::CTRL | Qt::Key_A);
    QObject::connect(ui->lineEdit, &QLineEdit::returnPressed, this, [=](){model->changeSelectedNodeText(ui->lineEdit->text());});
    QObject::connect(model, &MainModel::nodeSelectedWithText, ui->lineEdit, &QLineEdit::setText);
}

MainWindow::~MainWindow()
{
    delete ui;
}
