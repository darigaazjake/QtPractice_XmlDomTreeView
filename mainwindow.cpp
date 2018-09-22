//#include "dommodel.h"
#include "materialdommodel.h"
#include "mainwindow.h"

#include <QDomDocument>
#include <QTreeView>
#include <QMenuBar>
#include <QFileDialog>
#include <QtWidgets>//QSortFilterProxyModelに必要

#include <QDebug>

MainWindow::MainWindow() : QMainWindow(), model(0)
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile, QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), this, &QWidget::close, QKeySequence::Quit);

    proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel(model);
    QRegExp regExp("#comment", Qt::CaseSensitive);
    proxyModel->setFilterRegExp(regExp);

    //model = new DomModel(QDomDocument(), this);
    model = new MaterialDomModel(QDomDocument(), this);
    view = new QTreeView(this);

    //view->setModel(model);
    view->setModel(proxyModel);

    setCentralWidget(view);
    setWindowTitle(tr("Simple DOM Model"));

    connect(view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(treeItemClicked(const QModelIndex&)));
}

void MainWindow::treeItemClicked(const QModelIndex&)
{
    /*
    int rowNum = view->selectionModel()->currentIndex().row();
    int columnNum = view->selectionModel()->currentIndex().column();
    qDebug("%d, %d", rowNum, columnNum);
    */


}

void MainWindow::openFile()
{
    //for Debug
    xmlPath = "/home/jake/VTD/Data/Projects/Current/Config/ImageGenerator";

    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
        xmlPath, tr("XML files (*.xml);;HTML files (*.html);;"
                    "SVG files (*.svg);;User Interface files (*.ui)"));

    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly))
        {
            //documentに全部読み出す
            QDomDocument document;
            if (document.setContent(&file))
            {
                //documentからDomModelを生成
                //DomModel *newModel = new DomModel(document, this);
                MaterialDomModel *newModel = new MaterialDomModel(document, this);

                //ツリービューにデータ登録
                view->setModel(newModel);

                //すでに読み込み済のデータを破棄
                delete model;

                //読み込んだデータを保持
                model = newModel;

                //読んだパスを記録
                xmlPath = filePath;
            }
            file.close();
        }
    }
}
