#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chinaMapWidget = new ChinaMapWidget(this);
    setCentralWidget(chinaMapWidget);
    chinaMapWidget->loadJson(QApplication::applicationDirPath() + "/datas.json");
}

MainWindow::~MainWindow()
{
    delete ui;
}
