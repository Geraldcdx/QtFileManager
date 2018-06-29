#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QUrl>
#include <QDesktopServices>
#include <QFileSystemModel>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Creates the FileSystemModel for the TreeView which is the right widget
    QString sPath="C:/Users";//Change this such that you can issue your own relative path
    dirmodel = new QFileSystemModel(this);
    dirmodel ->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs);//Change this such that you are able to set your own filters
    ui->treeView->setModel(this->dirmodel);
    dirmodel->setRootPath(sPath);
    ui->treeView->setRootIndex(dirmodel->index(sPath));
    //qDebug()<<QDir::currentPath();

    //Creates the FileSystemModel for the listview, the right file widget
    listmodel=new QFileSystemModel(this);
    listmodel->setRootPath(sPath);
    ui->listView->setModel(listmodel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//This allows whatever that is clicked on the right widget to be shown on the left widget
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

    QString sPath=dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(listmodel->setRootPath(sPath));
}

//This uses QDesktopServices in order to create open the file with local programs
void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString sPath=listmodel->fileInfo(index).absoluteFilePath();
    QDesktopServices::openUrl(QUrl::fromLocalFile(sPath));
}
