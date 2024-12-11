#include "graphicsitemdebugdialog.h"
#include "ui_graphicsitemdebugdialog.h"
#include "graphmodelgraphicsitem.h"
#include "graphmodeltag.h"
#include <QtWidgets>

#include "mygraphicsitemgroup.h"

GraphicsItemDebugDialog::GraphicsItemDebugDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicsItemDebugDialog), m_item(NULL)
{
    ui->setupUi(this);
    m_timer.setInterval(500);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(loadProperties()));
}

GraphicsItemDebugDialog::~GraphicsItemDebugDialog()
{
    m_timer.stop();
    delete ui;
}

void GraphicsItemDebugDialog::setItem(GraphModelGraphicsItem *item)
{
    m_item = item;

    connect(ui->m_rect_x, SIGNAL(textChanged(QString)), this, SLOT(update_rect_x(QString)));
    connect(ui->m_rect_y, SIGNAL(textChanged(QString)), this, SLOT(update_rect_y(QString)));
    connect(ui->m_rect_w, SIGNAL(textChanged(QString)), this, SLOT(update_rect_w(QString)));
    connect(ui->m_rect_h, SIGNAL(textChanged(QString)), this, SLOT(update_rect_h(QString)));



    m_timer.start();
}

void GraphicsItemDebugDialog::loadProperties()
{
    ui->m_pos->setText(QString("%1,%2").arg(m_item->m_bondGroup->pos().x()).arg(m_item->m_bondGroup->pos().y()));
    ui->m_scenePos->setText(QString("%1,%2").arg(m_item->m_bondGroup->scenePos().x()).arg(m_item->m_bondGroup->scenePos().y()));

    QRectF br = m_item->m_bondGroup->boundingRect();
    ui->m_br_x->setText(QString("%1").arg(br.x()));
    ui->m_br_y->setText(QString("%1").arg(br.y()));
    ui->m_br_w->setText(QString("%1").arg(br.width()));
    ui->m_br_h->setText(QString("%1").arg(br.height()));

    QRectF sbr = m_item->m_bondGroup->mapRectToScene(m_item->m_bondGroup->boundingRect());
    ui->m_sbr_x->setText(QString("%1").arg(sbr.x()));
    ui->m_sbr_y->setText(QString("%1").arg(sbr.y()));
    ui->m_sbr_w->setText(QString("%1").arg(sbr.width()));
    ui->m_sbr_h->setText(QString("%1").arg(sbr.height()));

    QRectF tagbr = m_item->m_tagItem->boundingRect();
    ui->m_tagPos->setText(QString("%1,%2").arg(m_item->m_tagItem->pos().x()).arg(m_item->m_tagItem->pos().y()));
    ui->m_tag->setText(m_item->m_model->getFullTag());
    ui->m_tagVisible->setChecked(m_item->m_tagItem->isVisible());
    ui->m_tag_x ->setText(QString("%1").arg(tagbr.x()));
    ui->m_tag_y->setText(QString("%1").arg(tagbr.y()));
    ui->m_tag_w->setText(QString("%1").arg(tagbr.width()));
    ui->m_tag_h->setText(QString("%1").arg(tagbr.height()));

    QRectF factorbr = m_item->m_factor->boundingRect();
    ui->m_factor_pos->setText(QString("%1,%2").arg(m_item->m_factor->pos().x()).arg(m_item->m_factor->pos().y()));
    ui->m_factorVisible->setChecked(m_item->m_factor->isVisible());
    ui->m_factor_x ->setText(QString("%1").arg(factorbr.x()));
    ui->m_factor_y->setText(QString("%1").arg(factorbr.y()));
    ui->m_factor_w->setText(QString("%1").arg(factorbr.width()));
    ui->m_factor_h->setText(QString("%1").arg(factorbr.height()));

    QRectF rect = m_item->rect();
    ui->m_rect_x ->setText(QString("%1").arg(rect.x()));
    ui->m_rect_y->setText(QString("%1").arg(rect.y()));
    ui->m_rect_w->setText(QString("%1").arg(rect.width()));
    ui->m_rect_h->setText(QString("%1").arg(rect.height()));

    ui->m_width->setText(QString("%1").arg(m_item->getWidth()));
    ui->m_height->setText(QString("%1").arg(m_item->getHeight()));

    ui->m_item_pos->setText(QString("%1,%2").arg(m_item->pos().x()).arg(m_item->pos().y()));


}

void GraphicsItemDebugDialog::update_rect_x(QString value)
{
    QRectF rect = m_item->rect();
    rect.setLeft(value.toDouble());
    m_item->setRect(rect);
}

void GraphicsItemDebugDialog::update_rect_y(QString value)
{
    QRectF rect = m_item->rect();
    rect.setTop(value.toDouble());
    m_item->setRect(rect);
}

void GraphicsItemDebugDialog::update_rect_w(QString value)
{
    QRectF rect = m_item->rect();
    rect.setWidth(value.toDouble());
    m_item->setRect(rect);
}

void GraphicsItemDebugDialog::update_rect_h(QString value)
{
    QRectF rect = m_item->rect();
    rect.setHeight(value.toDouble());
    m_item->setRect(rect);
}
