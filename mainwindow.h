#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

//class DomModel;
class MaterialDomModel;
QT_BEGIN_NAMESPACE
class QMenu;
class QTreeView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

public slots:
    void openFile();

private:
    //読み込んだDOM
    //DomModel *model;
    MaterialDomModel *model;

    //ファイルパス 次のダイアログ起点として使うため保存
    QString xmlPath;

    //GUIパーツメニューバー
    QMenu *fileMenu;

    //GUIパーツ  表示用のツリービュー
    QTreeView *view;
};

#endif // MAINWINDOW_H
