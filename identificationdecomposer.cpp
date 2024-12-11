#include "identificationdecomposer.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QListView>
#include <QtSvg>

#include "graphmodel.h"
#include "graphdelegate.h"

#include "identificationmodelmanager.h"
#include "decomposerdialog.h"
#include "tagmodificationdialog.h"
#include "undoredomanager.h"

#include "widthmodeexportdialog.h"


// commands
#include "widthidentifycommand.h"
#include "widthcombinecommand.h"
#include "widthdecomposecommand.h"

#include "uniquetaggenerator.h"
#include "graphmodelgraphicsitem.h"


#include "formats.h"

IdentificationDecomposer::IdentificationDecomposer(QWidget *parent) :
    QWidget(parent)
{
    m_undoRedoManager = new UndoRedoManager();
    m_freeterm_text = new QTextDocument(this);

    QFont font;
    font.setFamily("Times New Roman");
    font.setPixelSize(26);


    m_freeterm_text->setDefaultFont(font);
    m_freeterm_text->setDocumentMargin(0);
    m_freeterm_text->setHtml("0");


    createUI();
    m_manager = new IdentificationModelManager(this);
    m_unidentified->setItemDelegate(new GraphDelegate<GraphModelGraphicsItem>(m_unidentified, true, this) );
    m_identified->setItemDelegate(new GraphDelegate<GraphModelGraphicsItem>(m_identified, true, this) );

    m_identified->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_unidentified->setSelectionMode(QAbstractItemView::ExtendedSelection);


    m_identified->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_identified,SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(identRightClick(QPoint)));

    m_unidentified->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_unidentified,SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(unidentRightClick(QPoint)));

    connect(m_unidentified,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(unidentItemSelected(QModelIndex)));
    connect(m_identified,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(identItemDoubleClicked(QModelIndex)));

    m_unidentified->setSelectionRectVisible(true);
    m_identified->setSelectionRectVisible(true);

    m_unidentified->setModel(m_manager->getUnidentifiedModel());
    m_identified->setModel(m_manager->getIdentifiedModel());


    m_unidentified->setViewMode(QListView::IconMode);
    m_unidentified->setWrapping(true);
    m_unidentified->setResizeMode(QListView::Adjust);
    m_unidentified->setMovement(QListView::Static);


    m_identified->setViewMode(QListView::IconMode);
    m_identified->setWrapping(true);
    m_identified->setResizeMode(QListView::Adjust);
    m_identified->setMovement(QListView::Static);

}

IdentificationDecomposer::~IdentificationDecomposer()
{
}

void IdentificationDecomposer::setRootGraph(GraphModel *graphmodel)
{
    m_manager->appendGraphModelToUnidentified(graphmodel);
}

void IdentificationDecomposer::clear()
{
    m_manager->clear();
    m_undoRedoManager->clear();
}

QString IdentificationDecomposer::getZZPolynomial()
{
    return m_manager->getZZPolynomial();
}

void IdentificationDecomposer::unidentItemSelected(QModelIndex index)
{

    if (m_unidentified->selectionModel()->selectedIndexes().size() == 1)
    {
        if (index.row() < 0)
        {
            return;
        }

        GraphModel* model = m_manager->getModel(index);

        if (model->isDead())
            return;


        UniqueTagGenerator *tagGenerator = new UniqueTagGenerator(*(m_manager->getUniqueTagGenerator()));
        DecomposerDialog *w = new DecomposerDialog(m_manager->getUniqueTagGenerator());


        connect(w, SIGNAL(ZZPolynomialRequest(GraphModel*)), this, SLOT(childZZPolynomialRequest(GraphModel*)));

        double wid = QApplication::desktop()->screenGeometry(w).width()*0.8;
        double h = QApplication::desktop()->screenGeometry(w).height()*0.8;

        w->resize(wid,h);
        w->setRootGraphModel(model);
        w->setModal(true);
        w->exec();

        if (w->result() == 1 && model->isBondSelected())
        {
            QList<GraphModel*> leafs = w->getLeafs();
            ICommand* command = new WidthDecomposeCommand(this, m_manager, tagGenerator, index, leafs);
            command->Execute();
            m_undoRedoManager->addCommand(command);
            m_unidentified->update(index);
        }
        delete w;

        //qDebug() << model->getFullTag() ;


    }
}

void IdentificationDecomposer::identItemDoubleClicked(QModelIndex index)
{
    if (m_identified->selectionModel()->selectedIndexes().size() == 1)
    {
        TagModificationDialog *w = new TagModificationDialog(m_manager->getModel(index));
        w->exec();
        if (w->result() == 1)
        {
            m_identified->update(index);
        }
        delete w;
    }
}

void IdentificationDecomposer::IdentifyButtonClicked()
{
    QModelIndexList list = m_unidentified->selectionModel()->selectedIndexes();
    ICommand *command = new WidthIdentifyCommand(m_manager->getUnidentifiedModel(),m_manager->getIdentifiedModel(),list);
    command->Execute();
    m_undoRedoManager->addCommand(command);

}

void IdentificationDecomposer::UnidentifyButtonClicked()
{
    QModelIndexList list = m_identified->selectionModel()->selectedIndexes();
    ICommand *command = new WidthIdentifyCommand(m_manager->getIdentifiedModel(),m_manager->getUnidentifiedModel(),list);
    command->Execute();
    m_undoRedoManager->addCommand(command);
}

void IdentificationDecomposer::createUI()
{
    QSplitter* splitter = new QSplitter(this);
    m_unidentified = new QListView(this);
    m_identified = new QListView(this);


    QVBoxLayout *un_layout = new QVBoxLayout();
    un_layout->setMargin(5);

    QLabel* label = new QLabel(tr("Unidentified Graphs"));
    label->setAlignment(Qt::AlignCenter);

    un_layout->addWidget(label);
    un_layout->addWidget(m_unidentified);

    QWidget* tmp = new QWidget(this);
    tmp->setLayout(un_layout);
    splitter->addWidget(tmp);

    QWidget *w = new QWidget(this);
    QVBoxLayout *vbox = new QVBoxLayout();
    w->setLayout(vbox);
    QPushButton *button1 = new QPushButton(tr("=>"));
    vbox->addWidget(button1);
    connect(button1, SIGNAL(clicked()), this, SLOT(IdentifyButtonClicked()));

    button1 = new QPushButton(tr("<="));
    connect(button1, SIGNAL(clicked()), this, SLOT(UnidentifyButtonClicked()));
    vbox->addWidget(button1);
    w->setMaximumWidth(60);
    splitter->addWidget(w);





    QVBoxLayout *id_layout = new QVBoxLayout();
    id_layout->setMargin(5);
    label = new QLabel(tr("Identified Graphs"));
    label->setAlignment(Qt::AlignCenter);
    id_layout->addWidget(label);
    id_layout->addWidget(m_identified);

    id_layout->addWidget(new QLabel(tr("Free Term Coefficients:")));
    QTextEdit *edit = new QTextEdit(this);
    edit->setReadOnly(true);
    edit->setMaximumHeight(40);
    edit->setDocument(m_freeterm_text);
    edit->setContentsMargins(0,0,0,0);
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    id_layout->addWidget(edit);

    tmp = new QWidget(this);
    tmp->setLayout(id_layout);
    splitter->addWidget(tmp);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->addWidget(splitter);
    this->setLayout(layout);
}

void IdentificationDecomposer::identRightClick(QPoint point)
{   
    confirmCombination(m_identified, point);
}
void IdentificationDecomposer::unidentRightClick(QPoint point)
{
    confirmCombination(m_unidentified, point);
}


bool IdentificationDecomposer::isomorphismCheck(QModelIndexList list)
{
    int nBonds = 0;
    for(int i=0; i< list.size(); ++i)
    {
        GraphModel *model = m_manager->getModel(list.at(i));
        if (i==0)
        {
            nBonds = model->getEdges().size();
        }
        else
        {
            int lBonds = model->getEdges().size();
            if (lBonds != nBonds)
            {
                return false;
            }
        }
    }
    return true;
}

void IdentificationDecomposer::confirmCombination(QListView *target, QPoint point)
{
    QPoint globalPos = target->mapToGlobal(point);
    QMenu myMenu;

    if (target->selectionModel()->selectedIndexes().size() == 1)
    {
        QAction* ZZPolyAction = myMenu.addAction("Compute ZZ polynomial...");
        QAction* export_as = myMenu.addAction("Export structure as...");

        QAction* selectedItem = myMenu.exec(globalPos);
        if (selectedItem == ZZPolyAction )
        {
            QModelIndexList list = target->selectionModel()->selectedIndexes();
            GraphModel *model = m_manager->getModel(list.first());
            emit ZZPolynomialRequest(model);
        }
        else if (selectedItem == export_as)
        {
            QModelIndexList list = target->selectionModel()->selectedIndexes();
            GraphModel *model = m_manager->getModel(list.first());
            export_structure(model);
        }
    }
    else if (target->selectionModel()->selectedIndexes().size()>1)
    {

        QAction* combineAction = myMenu.addAction("Combine...");
        QAction* ZZPolyAction = myMenu.addAction("Compute ZZ polynomial...");

        QAction* selectedItem = myMenu.exec(globalPos);


        if (selectedItem == combineAction)
        {
            QMessageBox qbox(this);
            qbox.setWindowTitle(tr("GZZDecomposer"));
            qbox.setText(tr("Are you sure that they are isomorphic?"));
            qbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
            qbox.setIcon(QMessageBox::Question);
            int ret = qbox.exec();
            if (ret == QMessageBox::Yes)
            {
                QModelIndexList list = target->selectionModel()->selectedIndexes();

                bool pass = isomorphismCheck(list);
                if (pass)
                {
                    ICommand* command = new WidthCombineCommand(m_manager, list);
                    m_undoRedoManager->addCommand(command);
                    command->Execute();
                }
                else
                {
                    QMessageBox errorBox(this);
                    errorBox.setWindowTitle(tr("GZZDecomposer"));
                    qbox.setText(tr("The structures are not all isomorphic, abort!"));
                    qbox.setStandardButtons(QMessageBox::Ok);
                    qbox.setIcon(QMessageBox::Critical);
                    qbox.exec();
                }
            }
            else
            {
                return;
            }
        }
        else if (selectedItem == ZZPolyAction )
        {
            QModelIndexList list = target->selectionModel()->selectedIndexes();
            QMessageBox qbox(this);
            qbox.setWindowTitle(tr("ZZ Decomposer"));
            qbox.setText(tr("Do you want to compute the ZZ polynomials for %1 structures?").arg(list.size()));
            qbox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
            qbox.setIcon(QMessageBox::Question);
            int ret = qbox.exec();
            if (ret == QMessageBox::Yes)
            {
                QListIterator<QModelIndex> it(list);
                while(it.hasNext())
                {
                    GraphModel *model = m_manager->getModel(it.next());
                    emit ZZPolynomialRequest(model);
                }
            }
        }
    }
}

void IdentificationDecomposer::undo()
{
    m_undoRedoManager->undo();
}

void IdentificationDecomposer::redo()
{
    m_undoRedoManager->redo();
}

void IdentificationDecomposer::exportSVG()
{
    if (m_manager->getUnidentifiedModel()->rowCount() > 0)
    {
        QMessageBox qbox(this);
        qbox.setWindowTitle(tr("ZZ Decomposer"));
        qbox.setText(tr("Before exporting, please identify all the graphs."));
        qbox.setStandardButtons(QMessageBox::Ok);
        qbox.setIcon(QMessageBox::Critical);
        qbox.exec();
        return;
    }


    WidthModeExportDialog *w = new WidthModeExportDialog(this->m_manager->getIdentifiedModel(),
                                                         this->m_manager->getFreeTermPolynomialInHTML(),
                                                         this);


    double wid = QApplication::desktop()->screenGeometry(w).width()*0.8;
    double h = QApplication::desktop()->screenGeometry(w).height()*0.8;

    w->resize(wid,h);
    w->setModal(true);
    w->exec();
    delete w;

}

void IdentificationDecomposer::childZZPolynomialRequest(GraphModel *model)
{
    emit ZZPolynomialRequest(model);
}
