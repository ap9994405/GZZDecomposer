/********************************************************************************
** Form generated from reading UI file 'graphicsitemdebugdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICSITEMDEBUGDIALOG_H
#define UI_GRAPHICSITEMDEBUGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_GraphicsItemDebugDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *m_pos;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *m_sbr_x;
    QLabel *label_4;
    QLineEdit *m_sbr_y;
    QLabel *label_5;
    QLineEdit *m_sbr_w;
    QLabel *label_6;
    QLineEdit *m_sbr_h;
    QLabel *label_7;
    QLineEdit *m_scenePos;
    QLineEdit *m_br_h;
    QLineEdit *m_br_y;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *m_br_w;
    QLineEdit *m_br_x;
    QLabel *label_11;
    QLabel *label_12;
    QGroupBox *groupBox;
    QLabel *label_13;
    QLineEdit *m_tag;
    QLabel *label_14;
    QLineEdit *m_tagPos;
    QLineEdit *m_tag_h;
    QLabel *label_15;
    QLineEdit *m_tag_y;
    QLineEdit *m_tag_w;
    QLabel *label_17;
    QLineEdit *m_tag_x;
    QLabel *label_18;
    QLabel *label_16;
    QLabel *label_19;
    QCheckBox *m_tagVisible;
    QGroupBox *groupBox_2;
    QLabel *label_24;
    QLabel *label_20;
    QLineEdit *m_factor_pos;
    QLabel *label_22;
    QLabel *label_21;
    QLabel *label_23;
    QLineEdit *m_factor_y;
    QLineEdit *m_factor_w;
    QLineEdit *m_factor_x;
    QLineEdit *m_factor_h;
    QCheckBox *m_factorVisible;
    QLabel *label_25;
    QGroupBox *groupBox_3;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *m_rect_y;
    QLineEdit *m_rect_w;
    QLineEdit *m_rect_x;
    QLineEdit *m_rect_h;
    QLabel *label_31;
    QLabel *label_26;
    QLineEdit *m_width;
    QLabel *label_30;
    QLineEdit *m_height;
    QLabel *label_32;
    QLineEdit *m_item_pos;

    void setupUi(QDialog *GraphicsItemDebugDialog)
    {
        if (GraphicsItemDebugDialog->objectName().isEmpty())
            GraphicsItemDebugDialog->setObjectName(QStringLiteral("GraphicsItemDebugDialog"));
        GraphicsItemDebugDialog->resize(643, 400);
        buttonBox = new QDialogButtonBox(GraphicsItemDebugDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(390, 330, 241, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(GraphicsItemDebugDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 47, 12));
        m_pos = new QLineEdit(GraphicsItemDebugDialog);
        m_pos->setObjectName(QStringLiteral("m_pos"));
        m_pos->setGeometry(QRect(40, 10, 113, 20));
        label_2 = new QLabel(GraphicsItemDebugDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 140, 81, 16));
        label_3 = new QLabel(GraphicsItemDebugDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 160, 47, 12));
        m_sbr_x = new QLineEdit(GraphicsItemDebugDialog);
        m_sbr_x->setObjectName(QStringLiteral("m_sbr_x"));
        m_sbr_x->setGeometry(QRect(40, 160, 113, 20));
        m_sbr_x->setReadOnly(true);
        label_4 = new QLabel(GraphicsItemDebugDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(170, 160, 47, 12));
        m_sbr_y = new QLineEdit(GraphicsItemDebugDialog);
        m_sbr_y->setObjectName(QStringLiteral("m_sbr_y"));
        m_sbr_y->setGeometry(QRect(190, 160, 113, 20));
        m_sbr_y->setReadOnly(true);
        label_5 = new QLabel(GraphicsItemDebugDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 190, 47, 12));
        m_sbr_w = new QLineEdit(GraphicsItemDebugDialog);
        m_sbr_w->setObjectName(QStringLiteral("m_sbr_w"));
        m_sbr_w->setGeometry(QRect(40, 190, 113, 20));
        m_sbr_w->setReadOnly(true);
        label_6 = new QLabel(GraphicsItemDebugDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(160, 190, 47, 12));
        m_sbr_h = new QLineEdit(GraphicsItemDebugDialog);
        m_sbr_h->setObjectName(QStringLiteral("m_sbr_h"));
        m_sbr_h->setGeometry(QRect(190, 190, 113, 20));
        m_sbr_h->setReadOnly(true);
        label_7 = new QLabel(GraphicsItemDebugDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 120, 47, 12));
        m_scenePos = new QLineEdit(GraphicsItemDebugDialog);
        m_scenePos->setObjectName(QStringLiteral("m_scenePos"));
        m_scenePos->setGeometry(QRect(60, 120, 113, 20));
        m_br_h = new QLineEdit(GraphicsItemDebugDialog);
        m_br_h->setObjectName(QStringLiteral("m_br_h"));
        m_br_h->setGeometry(QRect(190, 90, 113, 20));
        m_br_h->setReadOnly(true);
        m_br_y = new QLineEdit(GraphicsItemDebugDialog);
        m_br_y->setObjectName(QStringLiteral("m_br_y"));
        m_br_y->setGeometry(QRect(190, 60, 113, 20));
        m_br_y->setReadOnly(true);
        label_8 = new QLabel(GraphicsItemDebugDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 90, 47, 12));
        label_9 = new QLabel(GraphicsItemDebugDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 60, 47, 12));
        label_10 = new QLabel(GraphicsItemDebugDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 40, 81, 16));
        m_br_w = new QLineEdit(GraphicsItemDebugDialog);
        m_br_w->setObjectName(QStringLiteral("m_br_w"));
        m_br_w->setGeometry(QRect(40, 90, 113, 20));
        m_br_w->setReadOnly(true);
        m_br_x = new QLineEdit(GraphicsItemDebugDialog);
        m_br_x->setObjectName(QStringLiteral("m_br_x"));
        m_br_x->setGeometry(QRect(40, 60, 113, 20));
        m_br_x->setReadOnly(true);
        label_11 = new QLabel(GraphicsItemDebugDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(160, 90, 47, 12));
        label_12 = new QLabel(GraphicsItemDebugDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(170, 60, 47, 12));
        groupBox = new QGroupBox(GraphicsItemDebugDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(320, 10, 311, 151));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(10, 20, 47, 12));
        m_tag = new QLineEdit(groupBox);
        m_tag->setObjectName(QStringLiteral("m_tag"));
        m_tag->setGeometry(QRect(40, 20, 113, 20));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 50, 47, 12));
        m_tagPos = new QLineEdit(groupBox);
        m_tagPos->setObjectName(QStringLiteral("m_tagPos"));
        m_tagPos->setGeometry(QRect(40, 50, 113, 20));
        m_tag_h = new QLineEdit(groupBox);
        m_tag_h->setObjectName(QStringLiteral("m_tag_h"));
        m_tag_h->setGeometry(QRect(190, 120, 113, 20));
        m_tag_h->setReadOnly(true);
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(10, 120, 47, 12));
        m_tag_y = new QLineEdit(groupBox);
        m_tag_y->setObjectName(QStringLiteral("m_tag_y"));
        m_tag_y->setGeometry(QRect(190, 90, 113, 20));
        m_tag_y->setReadOnly(true);
        m_tag_w = new QLineEdit(groupBox);
        m_tag_w->setObjectName(QStringLiteral("m_tag_w"));
        m_tag_w->setGeometry(QRect(40, 120, 113, 20));
        m_tag_w->setReadOnly(true);
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(170, 90, 47, 12));
        m_tag_x = new QLineEdit(groupBox);
        m_tag_x->setObjectName(QStringLiteral("m_tag_x"));
        m_tag_x->setGeometry(QRect(40, 90, 113, 20));
        m_tag_x->setReadOnly(true);
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(20, 90, 47, 12));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(160, 120, 47, 12));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(10, 70, 81, 16));
        m_tagVisible = new QCheckBox(groupBox);
        m_tagVisible->setObjectName(QStringLiteral("m_tagVisible"));
        m_tagVisible->setEnabled(false);
        m_tagVisible->setGeometry(QRect(170, 20, 73, 16));
        m_tagVisible->setCheckable(true);
        groupBox_2 = new QGroupBox(GraphicsItemDebugDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(320, 180, 311, 141));
        label_24 = new QLabel(groupBox_2);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(10, 50, 81, 16));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(170, 70, 47, 12));
        m_factor_pos = new QLineEdit(groupBox_2);
        m_factor_pos->setObjectName(QStringLiteral("m_factor_pos"));
        m_factor_pos->setGeometry(QRect(40, 30, 113, 20));
        label_22 = new QLabel(groupBox_2);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(160, 100, 47, 12));
        label_21 = new QLabel(groupBox_2);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(20, 70, 47, 12));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 30, 47, 12));
        m_factor_y = new QLineEdit(groupBox_2);
        m_factor_y->setObjectName(QStringLiteral("m_factor_y"));
        m_factor_y->setGeometry(QRect(190, 70, 113, 20));
        m_factor_y->setReadOnly(true);
        m_factor_w = new QLineEdit(groupBox_2);
        m_factor_w->setObjectName(QStringLiteral("m_factor_w"));
        m_factor_w->setGeometry(QRect(40, 100, 113, 20));
        m_factor_w->setReadOnly(true);
        m_factor_x = new QLineEdit(groupBox_2);
        m_factor_x->setObjectName(QStringLiteral("m_factor_x"));
        m_factor_x->setGeometry(QRect(40, 70, 113, 20));
        m_factor_x->setReadOnly(true);
        m_factor_h = new QLineEdit(groupBox_2);
        m_factor_h->setObjectName(QStringLiteral("m_factor_h"));
        m_factor_h->setGeometry(QRect(190, 100, 113, 20));
        m_factor_h->setReadOnly(true);
        m_factorVisible = new QCheckBox(groupBox_2);
        m_factorVisible->setObjectName(QStringLiteral("m_factorVisible"));
        m_factorVisible->setEnabled(false);
        m_factorVisible->setGeometry(QRect(170, 30, 73, 16));
        m_factorVisible->setCheckable(true);
        label_25 = new QLabel(groupBox_2);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 110, 47, 12));
        groupBox_3 = new QGroupBox(GraphicsItemDebugDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 230, 311, 81));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(170, 20, 47, 12));
        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(160, 50, 47, 12));
        label_29 = new QLabel(groupBox_3);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(20, 20, 47, 12));
        m_rect_y = new QLineEdit(groupBox_3);
        m_rect_y->setObjectName(QStringLiteral("m_rect_y"));
        m_rect_y->setGeometry(QRect(190, 20, 113, 20));
        m_rect_y->setReadOnly(false);
        m_rect_w = new QLineEdit(groupBox_3);
        m_rect_w->setObjectName(QStringLiteral("m_rect_w"));
        m_rect_w->setGeometry(QRect(40, 50, 113, 20));
        m_rect_w->setReadOnly(false);
        m_rect_x = new QLineEdit(groupBox_3);
        m_rect_x->setObjectName(QStringLiteral("m_rect_x"));
        m_rect_x->setGeometry(QRect(40, 20, 113, 20));
        m_rect_x->setReadOnly(false);
        m_rect_h = new QLineEdit(groupBox_3);
        m_rect_h->setObjectName(QStringLiteral("m_rect_h"));
        m_rect_h->setGeometry(QRect(190, 50, 113, 20));
        m_rect_h->setReadOnly(false);
        label_31 = new QLabel(groupBox_3);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(10, 50, 47, 12));
        label_26 = new QLabel(GraphicsItemDebugDialog);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(10, 350, 47, 12));
        m_width = new QLineEdit(GraphicsItemDebugDialog);
        m_width->setObjectName(QStringLiteral("m_width"));
        m_width->setGeometry(QRect(40, 350, 113, 20));
        label_30 = new QLabel(GraphicsItemDebugDialog);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(160, 350, 47, 12));
        m_height = new QLineEdit(GraphicsItemDebugDialog);
        m_height->setObjectName(QStringLiteral("m_height"));
        m_height->setGeometry(QRect(190, 350, 113, 20));
        label_32 = new QLabel(GraphicsItemDebugDialog);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(10, 320, 47, 12));
        m_item_pos = new QLineEdit(GraphicsItemDebugDialog);
        m_item_pos->setObjectName(QStringLiteral("m_item_pos"));
        m_item_pos->setGeometry(QRect(40, 320, 113, 20));

        retranslateUi(GraphicsItemDebugDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GraphicsItemDebugDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GraphicsItemDebugDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GraphicsItemDebugDialog);
    } // setupUi

    void retranslateUi(QDialog *GraphicsItemDebugDialog)
    {
        GraphicsItemDebugDialog->setWindowTitle(QApplication::translate("GraphicsItemDebugDialog", "Dialog", 0));
        label->setText(QApplication::translate("GraphicsItemDebugDialog", "pos:", 0));
        label_2->setText(QApplication::translate("GraphicsItemDebugDialog", "boundingRect", 0));
        label_3->setText(QApplication::translate("GraphicsItemDebugDialog", "x", 0));
        label_4->setText(QApplication::translate("GraphicsItemDebugDialog", "y", 0));
        label_5->setText(QApplication::translate("GraphicsItemDebugDialog", "width", 0));
        label_6->setText(QApplication::translate("GraphicsItemDebugDialog", "height", 0));
        label_7->setText(QApplication::translate("GraphicsItemDebugDialog", "scenePos", 0));
        label_8->setText(QApplication::translate("GraphicsItemDebugDialog", "width", 0));
        label_9->setText(QApplication::translate("GraphicsItemDebugDialog", "x", 0));
        label_10->setText(QApplication::translate("GraphicsItemDebugDialog", "boundingRect", 0));
        label_11->setText(QApplication::translate("GraphicsItemDebugDialog", "height", 0));
        label_12->setText(QApplication::translate("GraphicsItemDebugDialog", "y", 0));
        groupBox->setTitle(QApplication::translate("GraphicsItemDebugDialog", "Tag", 0));
        label_13->setText(QApplication::translate("GraphicsItemDebugDialog", "Tag", 0));
        label_14->setText(QApplication::translate("GraphicsItemDebugDialog", "pos", 0));
        label_15->setText(QApplication::translate("GraphicsItemDebugDialog", "width", 0));
        label_17->setText(QApplication::translate("GraphicsItemDebugDialog", "y", 0));
        label_18->setText(QApplication::translate("GraphicsItemDebugDialog", "x", 0));
        label_16->setText(QApplication::translate("GraphicsItemDebugDialog", "height", 0));
        label_19->setText(QApplication::translate("GraphicsItemDebugDialog", "boundingRect", 0));
        m_tagVisible->setText(QApplication::translate("GraphicsItemDebugDialog", "visible", 0));
        groupBox_2->setTitle(QApplication::translate("GraphicsItemDebugDialog", "Factor", 0));
        label_24->setText(QApplication::translate("GraphicsItemDebugDialog", "boundingRect", 0));
        label_20->setText(QApplication::translate("GraphicsItemDebugDialog", "y", 0));
        label_22->setText(QApplication::translate("GraphicsItemDebugDialog", "height", 0));
        label_21->setText(QApplication::translate("GraphicsItemDebugDialog", "x", 0));
        label_23->setText(QApplication::translate("GraphicsItemDebugDialog", "pos", 0));
        m_factorVisible->setText(QApplication::translate("GraphicsItemDebugDialog", "visible", 0));
        label_25->setText(QApplication::translate("GraphicsItemDebugDialog", "width", 0));
        groupBox_3->setTitle(QApplication::translate("GraphicsItemDebugDialog", "Rect", 0));
        label_27->setText(QApplication::translate("GraphicsItemDebugDialog", "y", 0));
        label_28->setText(QApplication::translate("GraphicsItemDebugDialog", "height", 0));
        label_29->setText(QApplication::translate("GraphicsItemDebugDialog", "x", 0));
        label_31->setText(QApplication::translate("GraphicsItemDebugDialog", "width", 0));
        label_26->setText(QApplication::translate("GraphicsItemDebugDialog", "width", 0));
        label_30->setText(QApplication::translate("GraphicsItemDebugDialog", "height", 0));
        label_32->setText(QApplication::translate("GraphicsItemDebugDialog", "pos", 0));
    } // retranslateUi

};

namespace Ui {
    class GraphicsItemDebugDialog: public Ui_GraphicsItemDebugDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICSITEMDEBUGDIALOG_H
