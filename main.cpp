#include <QtWidgets>
#include <QtWidgets>
#include "mainwindow.h"
#include "widget.h"
#include "testnode.h"
#include "layoutabletree.h"
#include <QQueue>
#include <QPainter>

void printTree(LayoutableTree* tree)
{
    QQueue<LayoutableTreeNode*> queue;
    TestNode *node = (TestNode*)tree->getRootNode();
    queue.enqueue(node);
    int counter = 1;
    int level = 1;
    int temp_counter = 0;
    while(!queue.isEmpty())
    {
        LayoutableTreeNode* node = queue.dequeue();
        --counter;
        QListIterator<LayoutableTreeNode*> it(tree->getAllChildren(node));
        while(it.hasNext())
        {
            queue.enqueue(it.next());
        }

        TestNode *real = (TestNode*) node;
        qDebug() << "level: " << level << "  " << real->pos();
        temp_counter = tree->getAllChildren(node).size();
        if (counter ==0 )
        {
            ++level;
            counter = temp_counter;
            temp_counter = 0;
        }

    }
}

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);


//    qDebug() << QFileInfo(argv[0]).absoluteFilePath();

    MainWindow *w = new MainWindow();
    double wid = QApplication::desktop()->screenGeometry(w).width()*0.8;
    double h = QApplication::desktop()->screenGeometry(w).height()*0.8;
    w->resize(wid,h);
    w->show();


//    TestNode* root = new TestNode(60,100);
//    LayoutableTree *tree = new LayoutableTree(root);
//    TestNode* node = new TestNode(800,100);
//    tree->appendChild(root, node);
//    tree->appendChild(root, new TestNode(60,100));
//    tree->appendChild(root, new TestNode(60,100));

//    tree->appendChild(node, new TestNode(60,100));
//    tree->appendChild(node, new TestNode(60,100));
//    tree->appendChild(node, new TestNode(60,100));

//    tree->reposition();

//    printTree(tree);

    return a.exec();
}
