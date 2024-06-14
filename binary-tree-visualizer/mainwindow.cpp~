#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        this->setWindowTitle("Binary tree visualizer");

    scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);

    ui->treeGraphicsView->setRenderHint(QPainter::Antialiasing);
    ui->treeGraphicsView->setScene(scene);

    //icons for button
    ui->createButton->setIcon(QIcon(":/icons/add.ico"));
    ui->clearButton->setIcon(QIcon(":icons/remove.ico"));
    ui->insertButton->setIcon(QIcon(":/icons/add.ico"));
    ui->deleteButton->setIcon(QIcon(":/icons/remove.ico"));
    ui->findMinKeypushButton->setIcon(QIcon(":/icons/min_search.ico"));
    ui->findMaxKeypushButton->setIcon(QIcon(":/icons/max_search.ico"));
    ui->findNodePushButton->setIcon(QIcon(":/icons/search.ico"));
    ui->refreshButton->setIcon(QIcon(":/icons/refresh.ico"));

    //icons for tabwidget

    tree = new bintree<nodeData>();

    // default tree
    printTree(tree);
    drawTree(tree);

    //clear tree
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::on_clearButton_clicked);
}

void MainWindow::printTree(bintree<nodeData>* tree) {
    if (tree->root != nullptr) {
        QTreeWidgetItem* rootItem = new QTreeWidgetItem;
        rootItem->setText(0, "");
        ui->treeWidget->addTopLevelItem(rootItem);

        _printTree(tree->root, rootItem);
    }
}

void MainWindow::_printTree(node<nodeData>* leaf, QTreeWidgetItem* parentItem) {
    if (leaf != nullptr) {

        QTreeWidgetItem* childItem = new QTreeWidgetItem;
        childItem->setText(0, "- " + QString::number(leaf->key) + " " + leaf->data->str);
        parentItem->addChild(childItem);

        _printTree(leaf->left, childItem);
        _printTree(leaf->right, childItem);
    }
}

void MainWindow::drawTree(bintree<nodeData>* tree) {
    if (tree->root != nullptr) {
        // Инициализация корневого узла
        QGraphicsRectItem* rootRectItem = new QGraphicsRectItem(0, 0, sX, sY);
        QGraphicsTextItem* labelItem = new QGraphicsTextItem(QString::number(tree->root->key) + " " + tree->root->data->str, rootRectItem);

        labelItem->setDefaultTextColor(Qt::white);
        rootRectItem->setBrush(QBrush(Qt::red));

        labelItem->setPos(rootRectItem->boundingRect().center() - labelItem->boundingRect().center());

        scene->addItem(rootRectItem);
        scene->addItem(labelItem);

        _drawTree(tree->root->left, tree->root->right, rootRectItem, -1, false); // Для корня не рисуем линию
        _drawTree(tree->root->right, tree->root->left, rootRectItem, 1, false); // Для корня не рисуем линию
    }
}

#define dY 70
#define dX 60
#define sX 100
#define sY 40

//print tree
void MainWindow::_drawTree(node<nodeData>* leaf, node<nodeData>* neighbor, QGraphicsRectItem* parentRectItem, int side, bool drawLine) {
    if (leaf != nullptr) {
        QGraphicsRectItem* childRectItem = new QGraphicsRectItem;
        QGraphicsTextItem* labelItem = new QGraphicsTextItem(QString::number(leaf->key) + " " + leaf->data->str);
        QPen border;

        // Логика построения дерева
        int rightDepthNeighbor = (neighbor != nullptr) ? bintree<nodeData>::rightDepth(neighbor) : 0;
        int leftDepthNeighbor = (neighbor != nullptr) ? bintree<nodeData>::leftDepth(neighbor) : 0;

        if (side == -1) {
            int offsetX = (bintree<nodeData>::rightDepth(leaf) + leftDepthNeighbor + 2) * dX;
            childRectItem->setRect(parentRectItem->boundingRect().x() - offsetX,
                                   parentRectItem->boundingRect().y() + dY, sX, sY);
        } else if (side == 1) {
            int offsetX = (rightDepthNeighbor + bintree<nodeData>::leftDepth(leaf) + 2) * dX;
            childRectItem->setRect(parentRectItem->boundingRect().x() + offsetX,
                                   parentRectItem->boundingRect().y() + dY, sX, sY);
        } else if (side == 0) {
            childRectItem->setRect(parentRectItem->boundingRect().x(),
                                   parentRectItem->boundingRect().y() + dY, sX, sY);
        }

        labelItem->setPos(childRectItem->boundingRect().center() - labelItem->boundingRect().center());
        labelItem->setDefaultTextColor(Qt::white);

        childRectItem->setBrush(QBrush(Qt::red));

        // подсветка максимального и минимального изла
        if (leaf == lastFoundMax) {
            childRectItem->setBrush(QBrush(Qt::green));
            labelItem->setDefaultTextColor(Qt::black);
        } else if (leaf == lastFoundMin) {
            childRectItem->setBrush(QBrush(Qt::cyan));
            labelItem->setDefaultTextColor(Qt::black);
        } else {
            childRectItem->setBrush(QBrush(Qt::red));
            labelItem->setDefaultTextColor(Qt::white);
        }
        labelItem->setDefaultTextColor(Qt::white);

        // Проверка на нахождение в списке найденных узлов
        if (foundNodes.contains(leaf)) {
            childRectItem->setBrush(QBrush(Qt::yellow));  // Цвет для выделения найденных узлов
            labelItem->setDefaultTextColor(Qt::black);
        }

        childRectItem->setPen(border);

        QGraphicsLineItem* lineItem = new QGraphicsLineItem(parentRectItem->boundingRect().center().x(),
                                                            parentRectItem->boundingRect().center().y(),
                                                            childRectItem->boundingRect().center().x(),
                                                            childRectItem->boundingRect().center().y());
        lineItem->setPen(QPen(Qt::white));

        lineItem->setPen(QPen(Qt::white));
        lineItem->setZValue(-2);
        scene->addItem(lineItem);

        //lineItem->setZValue(0);
        childRectItem->setZValue(1);
        labelItem->setZValue(2);

        scene->addItem(childRectItem);
        scene->addItem(labelItem);

        _drawTree(leaf->left, leaf->right, childRectItem, -1);
        _drawTree(leaf->right, leaf->left, childRectItem, 1);
    }
}



bintree<nodeData>* MainWindow::makeTree(void) {
    delete tree;

    tree = new bintree<nodeData>;

    int count = ui->nodeQuantitySpinBox->value();
    int max = ui->maxKeySpinBox->value();

    node<nodeData>* node;
    for (int i = 0; i < count; i++) {
        node = tree->insert(QRandomGenerator::global()->bounded(max+1));
    }

    onTreeOperation();

    return tree;
}

void MainWindow::updateTree() {
    ui->treeWidget->clear();
    scene->clear();

    if (tree == nullptr)
        QMessageBox::critical(this, "Ошибка", "Список не создан");
    else {
        printTree(tree);
        drawTree(tree);
        scene->setSceneRect(scene->itemsBoundingRect());
    }

    ui->treeWidget->expandAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTreeOperation(bool changing) {
    if (changing) {
        lastFoundMax = nullptr;
        lastFoundMin = nullptr;
        lastFound = nullptr;

        ui->maxLabel->setText("Максимальный ключ");
        ui->minLabel->setText("Минимальный ключ");
        ui->findLabel->setText("Найденый ключ");
    }

    if (ui->findAutomaticallyCheckBox->isChecked()) {
        findMaxNode(false);
        findMinNode(false);
    }

    if (ui->refreshAutomaticallyCheckBox->isChecked()) {
        updateTree();
    }
}

void MainWindow::on_expandAllPushButton_clicked()
{
    ui->treeWidget->expandAll();
}


void MainWindow::on_collapseAllPushButton_clicked()
{
    ui->treeWidget->collapseAll();
}

void MainWindow::on_createButton_clicked()
{
    makeTree();
}


void MainWindow::on_refreshButton_clicked()
{
    updateTree();
}

void MainWindow::on_expandToLevelPushButton_clicked()
{
    ui->treeWidget->expandToDepth(ui->expandToLevelSpinBox->value());
}

void MainWindow::on_insertButton_clicked()
{

    node<nodeData>* node = tree->insert(ui->insertKeySpinBox->value());
    onTreeOperation();
}

void MainWindow::on_deleteButton_clicked()
{


    if (tree->search(ui->insertKeySpinBox->value()) == nullptr) {
        QMessageBox::critical(this, "Не удалось удалить узел", "Не удалось удалить узел с помощью ключа" + QString::number(ui->insertKeySpinBox->value()) + ".");
        return;
    } else
        tree->destroy(ui->insertKeySpinBox->value());


    onTreeOperation();
}

void MainWindow::on_findMaxKeypushButton_clicked()
{
    findMaxNode();
}

void MainWindow::on_insertKeySpinBox_valueChanged(int arg1)
{
    ui->deleteButton->setText("Удалить ключ по значению " + QString::number(arg1));
}


void MainWindow::on_findMinKeypushButton_clicked()
{
    findMinNode();
}

void MainWindow::findMaxNode(bool update) {

    node<nodeData>* leaf = tree->searchMax();

    if (leaf != nullptr) {

        lastFoundMax = leaf;

        ui->maxLabel->setText(QString::number(leaf->key));
        ui->findLabel->setText("Найденый узел");
        if (update)
            onTreeOperation(false);
    } else {

        QMessageBox::critical(this, "Не удалось найти узел", "Не удалось найти узел с максимальным значением.");

        ui->maxLabel->setText("Нет такого узла");
    }
}

void MainWindow::findMinNode(bool update) {

    node<nodeData>* leaf = tree->searchMin();

    if (leaf != nullptr) {

        lastFoundMin = leaf;

        ui->minLabel->setText(QString::number(leaf->key));
        ui->findLabel->setText("Найденый узел");
        if (update)
            onTreeOperation(false);
    } else {

        QMessageBox::critical(this, "Не удалось найти узел", "Не удалось найти узел с минимальным значением.");

        ui->maxLabel->setText("Нет такого узла");
    }
}

//поиск всех узлов с заданным значением
void MainWindow::findAllNodesWithKey(node<nodeData>* leaf, int key, QList<node<nodeData>*>& nodes) {
    if (leaf != nullptr) {
        if (leaf->key == key) {
            nodes.append(leaf);
        }
        findAllNodesWithKey(leaf->left, key, nodes);
        findAllNodesWithKey(leaf->right, key, nodes);
    }
}

void MainWindow::on_findNodePushButton_clicked() {
    int key = ui->findKeySpinBox->value();
    foundNodes.clear();
    findAllNodesWithKey(tree->root, key, foundNodes);

    if (!foundNodes.isEmpty()) {
        ui->findLabel->setText("Найдено узлов: " + QString::number(foundNodes.size()));
        onTreeOperation(false);
    } else {
        QMessageBox::critical(this, "Не удалось найти узел", "Нет узлов с ключом " + QString::number(key) + ".");
        ui->findLabel->setText("Нет такого узла");
    }
}

void MainWindow::clearTree() {
    // Удаляем текущее дерево
    delete tree;

    // Создаем новое пустое дерево
    tree = new bintree<nodeData>;

    // Очищаем виджеты
    ui->treeWidget->clear();
    scene->clear();

    // Обновляем интерфейс
    updateTree();
}

void MainWindow::on_clearButton_clicked() {
    clearTree();
}

void MainWindow::on_findAutomaticallyCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->findMaxKeypushButton->setEnabled(false);
        ui->findMaxKeypushButton->setCursor(Qt::CursorShape::ForbiddenCursor);
        ui->findMinKeypushButton->setEnabled(false);
        ui->findMinKeypushButton->setCursor(Qt::CursorShape::ForbiddenCursor);
        findMaxNode(false);
        findMinNode();
    } else {
        onTreeOperation();
        ui->findMaxKeypushButton->setEnabled(true);
        ui->findMaxKeypushButton->setCursor(Qt::CursorShape::PointingHandCursor);
        ui->findMinKeypushButton->setEnabled(true);
        ui->findMinKeypushButton->setCursor(Qt::CursorShape::PointingHandCursor);
    }
}

void MainWindow::on_refreshAutomaticallyCheckBox_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->refreshButton->setEnabled(false);
        ui->refreshButton->setCursor(Qt::CursorShape::ForbiddenCursor);
        onTreeOperation(false);
    } else {
        ui->refreshButton->setEnabled(true);
        ui->refreshButton->setCursor(Qt::CursorShape::PointingHandCursor);
    }

}

void MainWindow::on_findKeySpinBox_valueChanged(int arg1)
{
    ui->findNodePushButton->setText("Найти ключ по значению " + QString::number(arg1));
}

void MainWindow::on_zoomHorizontalSlider_valueChanged(int value)
{
    qreal factor = value / 100.0;
    ui->treeGraphicsView->setTransform(QTransform::fromScale(factor, factor));

    ui->zoomLabel->setText("Увеличение: " + QString::number(value) + "%");
}
/////////////////////////////////////////////////////////////////////////////////
///add icons in button

void MainWindow::on_createButton_toggled(bool checked)
{
   if(checked)
   {
      ui->createButton->setIcon(QIcon(":/icons/add.ico"));
   }
}

void MainWindow::on_clearButton_toggled(bool checked)
{
   if(checked)
   {
       ui->clearButton->setIcon(QIcon(":/icons/remove.ico"));
   }
}

void MainWindow::on_insertButton_toggled(bool checked)
{
   if(checked)
   {
       ui->insertButton->setIcon(QIcon(":/icons/add.ico"));
   }
}

void MainWindow::on_deleteButton_toggled(bool checked)
{
   if(checked)
   {
       ui->deleteButton->setIcon(QIcon(":/icons/remove.ico"));
   }
}

void MainWindow::on_findMinKeypushButton_toggled(bool checked)
{
   if(checked)
   {
       ui->findMinKeypushButton->setIcon(QIcon(":/icons/min_search.ico"));
   }
}

void MainWindow::on_findMaxKeypushButton_toggled(bool checked)
{
   if(checked)
   {
       ui->findMaxKeypushButton->setIcon(QIcon(":/icons/max_search.ico"));
   }
}

void MainWindow::on_findNodePushButton_toggled(bool checked)
{
   if(checked)
   {
       ui->findNodePushButton->setIcon(QIcon(":/icons/search.ico"));
   }
}

void MainWindow::on_refreshButton_toggled(bool checked)
{
   if(checked)
   {
       ui->refreshButton->setIcon(QIcon(":/icons/refresh.ico"));
   }
}
