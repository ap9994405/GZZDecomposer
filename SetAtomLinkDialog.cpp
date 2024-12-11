#include "SetAtomLinkDialog.h"

#include <QVBoxLayout>
#include "graphmodel.h"
#include "graphmodelgraphicsitem.h"
#include <QDialogButtonBox>
#include <QSplitter>
#include <QtWidgets>
#include <QTableWidgetItem>

SetAtomLinkDialog::SetAtomLinkDialog(GraphModel *model, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();

    scene = new QGraphicsScene(this);
    view = new ZoomableView(scene);
    view->setMouseTracking(true);




    m_model = model;

    m_model->prepare();

    graph_item = new GraphModelGraphicsItem(m_model);

    graph_item->setTagVisible(false);
    graph_item->setBondSelectable(false);
    graph_item->setAtomNumberVisible(true);
    scene->addItem(graph_item);
    view->centerOn(graph_item);

    scene->setSceneRect(scene->itemsBoundingRect());

    QSplitter* splitter = new QSplitter(Qt::Horizontal);

    splitter->addWidget(view);

    QVBoxLayout *vbox = new QVBoxLayout();
    QWidget *wid = new QWidget();
    wid->setLayout(vbox);
    wid->setMaximumWidth(300);

    m_addLink = new QPushButton(tr("Add link"));
    m_removeLink = new QPushButton(tr("Remove link"));
    m_table = new QTableWidget;
    m_preview = new QPushButton(tr("Preview"));

    m_table->setColumnCount(2);
    m_table->setHorizontalHeaderLabels(QStringList() << "Atom1" << "Atom2");
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->verticalHeader()->hide();
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(m_addLink, &QPushButton::pressed, [&]()
    {
        m_table->setRowCount(m_table->rowCount()+1);
    }
    );

    connect(m_removeLink, &QPushButton::pressed, [&]()
    {
        auto list = m_table->selectionModel()->selectedRows();
        for(int i=list.size();i>=0; --i)
        {
            m_table->removeRow(i);
        }
    }
    );

    connect(m_preview, SIGNAL(pressed()), this, SLOT(preview()));

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(m_addLink);
    hbox->addWidget(m_removeLink);
    hbox->addWidget(m_preview);
    vbox->setMargin(0);
    vbox->addLayout(hbox);
    vbox->addWidget(m_table);



    splitter->addWidget(wid);
    layout->addWidget(splitter);

    splitter->setCollapsible(1,false);


    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);

    layout->addWidget(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    this->setLayout(layout);
}

void SetAtomLinkDialog::preview()
{
    m_model->clearLink();
    graph_item->clearLink();
    QList<QPair<int, int> > links;

    for(int i=0; i<m_table->rowCount();++i)
    {
        bool ok1 = true;
        int index1 = m_table->item(i,0)->text().toInt(&ok1);
        bool ok2 = true;
        int index2 = m_table->item(i,1)->text().toInt(&ok2);

        if (!ok1 or !ok2 )
        {
            continue;
        }

        if (index1 == index2)
            continue;

        if (m_model->getNeighborList().isNeighbor(index1-1, index2-1))
            continue;
        links.append(qMakePair(index1-1, index2-1));
    }



    if (m_model->addLink(links))
    {
        graph_item->addLink(links);
    }
}
