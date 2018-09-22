//#include "dommodel.h"
#include "materialdommodel.h"
#include "mainwindow.h"

#include <QDomDocument>
#include <QTreeView>
#include <QMenuBar>
#include <QFileDialog>

MainWindow::MainWindow() : QMainWindow(), model(0)
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), this, &MainWindow::openFile, QKeySequence::Open);
    fileMenu->addAction(tr("E&xit"), this, &QWidget::close, QKeySequence::Quit);

    //model = new DomModel(QDomDocument(), this);
    model = new MaterialDomModel(QDomDocument(), this);
    view = new QTreeView(this);
    view->setModel(model);

    setCentralWidget(view);
    setWindowTitle(tr("Simple DOM Model"));
}

void MainWindow::openFile()
{
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
