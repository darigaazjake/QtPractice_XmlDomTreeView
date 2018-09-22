/**
  QSortFilterProxyModelの使い方は、Exampleの"basicsortfiltermodel.pro"を参考にした
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtWidgets>

//class DomModel;
class MaterialDomModel;

QT_BEGIN_NAMESPACE
class QMenu;
class QSortFilterProxyModel;
class QTreeView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void openFile();
    void treeItemClicked(const QModelIndex&);

private:
    //読み込んだDOM
    //DomModel *model;
    MaterialDomModel *model;

    //フィルタリング用データ
    QSortFilterProxyModel *proxyModel;

    //ファイルパス 次のダイアログ起点として使うため保存
    QString xmlPath;

    //GUIパーツメニューバー
    QMenu *fileMenu;

    //GUIパーツ  表示用のツリービュー
    QTreeView *view;
};

#endif // MAINWINDOW_H
