#ifndef DECOMPOSER_H
#define DECOMPOSER_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHash>


class UndoRedoManager;
class LayoutableTree;
class GraphModelTreeNode;
class GraphModel;
class UniqueTagGenerator;   //in uniquetaggenerator
class Decomposer : public QWidget
{
    Q_OBJECT
    friend class GraphDecomposeCommand;
public:
    explicit Decomposer(UniqueTagGenerator *tagGen = 0, QWidget *parent = 0);
    ~Decomposer();
    QString getZZPolynomial();
signals:
    void ZZPolynomialRequest(GraphModel* model);
private slots:
    void childZZPolynomialRequest(GraphModel* model);
public slots:
    void setRootGraph(GraphModel* graph);
    QList<GraphModel *> getLeafs();
    void clear();
    void setAllowFragments(bool enable);
    bool allowFragments();

    void exportSVG(QString filename, bool compressed);
//    void setHideZeros(bool on);

    void setGridRotate(bool rotate);
    void reposition();



private slots:
    void graphSelectionChanged(GraphModel* model);
    void addChild(GraphModel* parent, GraphModel* child);
    void tagChanged();
private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    GraphModel* m_root_graph;
    LayoutableTree *m_graphtree;
    QHash<GraphModel*, GraphModelTreeNode*> m_nodeMapping;
    bool m_allowFragments;
    UniqueTagGenerator* m_tagGenerator;
    UndoRedoManager* m_undoRedoManager;
    bool m_rotateGrid;
    class BondItem;

private:
    QString getZZPolynomial(GraphModelTreeNode* node);
};

#endif // DECOMPOSER_H
