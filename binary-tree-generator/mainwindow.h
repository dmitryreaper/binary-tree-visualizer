#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "bintree.h"

#include <QDebug>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QRandomGenerator>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>


#define LOG(EXPR) ui->logTextEdit->append(EXPR)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct nodeData {
    QString str = nullptr;
    node<nodeData>* parent = nullptr;

    int rightSpacing = 0;
    int leftSpacing = 0;

    int cumulativeRightSpacing = 0;
    int cumulativeLeftSpacing = 0;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_expandAllPushButton_clicked();

    void on_collapseAllPushButton_clicked();

    void on_createButton_clicked();

    void on_refreshButton_clicked();

    void on_expandToLevelPushButton_clicked();

    void on_insertButton_clicked();

    void on_deleteButton_clicked();

    void on_findMaxKeypushButton_clicked();

    void on_insertKeySpinBox_valueChanged(int arg1);

    void on_findMinKeypushButton_clicked();

    void on_findNodePushButton_clicked();

    void on_findAutomaticallyCheckBox_stateChanged(int arg1);

    void on_refreshAutomaticallyCheckBox_stateChanged(int arg1);

    void on_findKeySpinBox_valueChanged(int arg1);

    void on_zoomHorizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    bintree<nodeData>* tree;
    node<nodeData>* lastFoundMax = nullptr;
    node<nodeData>* lastFoundMin = nullptr;
    node<nodeData>* lastFound = nullptr;

    QGraphicsScene* scene;

    void printTree(bintree<nodeData>* tree);
    void _printTree(node<nodeData>* leaf, QTreeWidgetItem* parentItem);
    void drawTree(bintree<nodeData>* tree);
    void _drawTree(node<nodeData>* leaf, node<nodeData>* neighbor, QGraphicsRectItem* parentRectItem, int side);

    void findMaxNode(bool update = true);
    void findMinNode(bool update = true);


    void updateTree(void);

    void onTreeOperation(bool changing = true);
    bintree<nodeData>* makeTree(void);
};
#endif // MAINWINDOW_H
