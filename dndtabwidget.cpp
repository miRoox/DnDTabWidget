#include "dndtabwidget.h"
#include "dndtabbar.h"
#include <QDebug>

DnDTabWidget::DnDTabWidget(QWidget * parent)
    : QTabWidget(parent)
{
    auto mTabBar = new DnDTabBar(this);
    setTabBar(mTabBar);
    connect(mTabBar,&DnDTabBar::tabCloseRequested,this,&DnDTabWidget::removeTabActually);
    mTabBar->setTabsClosable(true);
    setTabShape(QTabWidget::Triangular);

    connect(mTabBar,&DnDTabBar::openFileRequest,this,&DnDTabWidget::openFileRequest);
    connect(mTabBar,&DnDTabBar::dragTabRequest,this,&DnDTabWidget::dragTabRequest);
}


DnDTabWidget::~DnDTabWidget()
{}

void DnDTabWidget::removeTabActually(int index)
{
    widget(index)->deleteLater();
    removeTab(index);
}

