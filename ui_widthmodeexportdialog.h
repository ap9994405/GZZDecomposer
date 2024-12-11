/********************************************************************************
** Form generated from reading UI file 'widthmodeexportdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDTHMODEEXPORTDIALOG_H
#define UI_WIDTHMODEEXPORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <zoomableview.h>

QT_BEGIN_NAMESPACE

class Ui_WidthModeExportDialog
{
public:
    QHBoxLayout *horizontalLayout_2;
    ZoomableView *graphicsView;
    QVBoxLayout *verticalLayout;
    QPushButton *button_OK;
    QPushButton *button_cancel;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_ncols;
    QSlider *slider_ncols;
    QCheckBox *checkBox;
    QCheckBox *checkBox_gridlines;
    QLabel *label;
    QSlider *horizontalSlider_2;
    QLabel *label_2;
    QSlider *horizontalSlider_3;
    QLabel *label_4;
    QSlider *horizontalSlider_4;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *WidthModeExportDialog)
    {
        if (WidthModeExportDialog->objectName().isEmpty())
            WidthModeExportDialog->setObjectName(QStringLiteral("WidthModeExportDialog"));
        WidthModeExportDialog->resize(994, 808);
        horizontalLayout_2 = new QHBoxLayout(WidthModeExportDialog);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        graphicsView = new ZoomableView(WidthModeExportDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(400, 0));
        graphicsView->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_2->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        button_OK = new QPushButton(WidthModeExportDialog);
        button_OK->setObjectName(QStringLiteral("button_OK"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(button_OK->sizePolicy().hasHeightForWidth());
        button_OK->setSizePolicy(sizePolicy1);
        button_OK->setMaximumSize(QSize(150, 16777215));
        button_OK->setCheckable(false);

        verticalLayout->addWidget(button_OK);

        button_cancel = new QPushButton(WidthModeExportDialog);
        button_cancel->setObjectName(QStringLiteral("button_cancel"));
        sizePolicy1.setHeightForWidth(button_cancel->sizePolicy().hasHeightForWidth());
        button_cancel->setSizePolicy(sizePolicy1);
        button_cancel->setMaximumSize(QSize(150, 16777215));

        verticalLayout->addWidget(button_cancel);

        groupBox = new QGroupBox(WidthModeExportDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMaximumSize(QSize(150, 16777215));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        label_ncols = new QLabel(groupBox);
        label_ncols->setObjectName(QStringLiteral("label_ncols"));
        label_ncols->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_ncols);


        verticalLayout_2->addLayout(horizontalLayout_3);

        slider_ncols = new QSlider(groupBox);
        slider_ncols->setObjectName(QStringLiteral("slider_ncols"));
        slider_ncols->setMinimum(1);
        slider_ncols->setMaximum(5);
        slider_ncols->setValue(3);
        slider_ncols->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(slider_ncols);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        verticalLayout_2->addWidget(checkBox);

        checkBox_gridlines = new QCheckBox(groupBox);
        checkBox_gridlines->setObjectName(QStringLiteral("checkBox_gridlines"));
        checkBox_gridlines->setChecked(true);

        verticalLayout_2->addWidget(checkBox_gridlines);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        horizontalSlider_2 = new QSlider(groupBox);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setMinimum(10);
        horizontalSlider_2->setMaximum(500);
        horizontalSlider_2->setSingleStep(10);
        horizontalSlider_2->setPageStep(50);
        horizontalSlider_2->setValue(50);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        horizontalSlider_3 = new QSlider(groupBox);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setMinimum(10);
        horizontalSlider_3->setMaximum(500);
        horizontalSlider_3->setSingleStep(10);
        horizontalSlider_3->setPageStep(50);
        horizontalSlider_3->setValue(50);
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_3);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        horizontalSlider_4 = new QSlider(groupBox);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setMaximum(100);
        horizontalSlider_4->setPageStep(20);
        horizontalSlider_4->setValue(10);
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(horizontalSlider_4);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addWidget(groupBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(WidthModeExportDialog);

        button_OK->setDefault(false);


        QMetaObject::connectSlotsByName(WidthModeExportDialog);
    } // setupUi

    void retranslateUi(QDialog *WidthModeExportDialog)
    {
        WidthModeExportDialog->setWindowTitle(QApplication::translate("WidthModeExportDialog", "Dialog", 0));
        button_OK->setText(QApplication::translate("WidthModeExportDialog", "Save", 0));
        button_cancel->setText(QApplication::translate("WidthModeExportDialog", "Cancel", 0));
        groupBox->setTitle(QApplication::translate("WidthModeExportDialog", "Options", 0));
        label_3->setText(QApplication::translate("WidthModeExportDialog", "Columns", 0));
        label_ncols->setText(QApplication::translate("WidthModeExportDialog", "3", 0));
        checkBox->setText(QApplication::translate("WidthModeExportDialog", "Frame", 0));
        checkBox_gridlines->setText(QApplication::translate("WidthModeExportDialog", "Grid Lines", 0));
        label->setText(QApplication::translate("WidthModeExportDialog", "V. Spacing:", 0));
        label_2->setText(QApplication::translate("WidthModeExportDialog", "H. Spacing:", 0));
        label_4->setText(QApplication::translate("WidthModeExportDialog", "Margin:", 0));
    } // retranslateUi

};

namespace Ui {
    class WidthModeExportDialog: public Ui_WidthModeExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDTHMODEEXPORTDIALOG_H
