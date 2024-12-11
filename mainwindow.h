#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>


class GraphModel;
class BuilderWidget;
class Decomposer;
class IdentificationDecomposer;
class ZZPolynomialCalculatorPanel;
// class ZZAromaticityCalculatorPanel;
// class ZZSpinpopulaitonCalculatorPanel;
// class ZZSpinpopulaitonCalculatorPanel2;
// class ZZSpinpopulaitonCalculatorPanel3;
// class johanna;
class porsche;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
private slots:
    void tabPageChanged(int index);
    void clearAll();
    void saveClicked();
    void showZZInfo();
    void showAbout();
    void showAboutQt();
    void undo();
    void redo();
    void processZZPolynomialRequest(GraphModel* model);
    void builderProcessZZPolynomialRequest(GraphModel* model);
    void setGridRotate(bool rotate);
    void toggleSeparateFragments(bool isSeparated);
    void test();
    void screenshot();
private:
    void createActions();
    void createToolbars();
    void createMenus();
    void createDocks();
    QAction *m_newfile;
    QAction *m_savefile;
    QAction *m_openfile;
    QToolBar *m_toolbar;
    QTabWidget *m_tabWidget;
    BuilderWidget *m_builder;
    Decomposer *m_decomposer;
    IdentificationDecomposer *m_identDecomposer;
    ZZPolynomialCalculatorPanel *m_zzCalculatorPanel;
    // ZZAromaticityCalculatorPanel *m_zzAromaticityCalculatorPanel;
    // ZZSpinpopulaitonCalculatorPanel *m_zzSpinpopulaitonCalculatorPanel;
    // ZZSpinpopulaitonCalculatorPanel2 *m_zzSpinpopulaitonCalculatorPanel2;
    // ZZSpinpopulaitonCalculatorPanel3 *m_zzSpinpopulaitonCalculatorPanel3;
    // johanna *m_johanna;
    porsche *m_porsche;



    QAction *m_zzinfo;
    QAction *m_hidezeros;
    QMenu *m_viewMenu;
    QAction *m_undo;
    QAction *m_redo;
    QAction* m_toogleSeparateFragments;

private:
    GraphModel* m_workingGraphModel;
};

#endif // MAINWINDOW_H
