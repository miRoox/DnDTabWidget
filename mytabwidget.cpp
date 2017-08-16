#include "mytabwidget.h"
#include "mytabbar.h"
#include <QDebug>

MyTabWidget::MyTabWidget(QWidget * parent)
    : QTabWidget(parent)
{
    auto mTabBar = new MyTabBar(this);
    setTabBar(mTabBar);
    connect(mTabBar,&MyTabBar::tabCloseRequested,this,&MyTabWidget::removeTabActually);
    mTabBar->setTabsClosable(true);
    setTabShape(QTabWidget::Triangular);

    connect(mTabBar,&MyTabBar::openFileRequest,this,&MyTabWidget::openFileRequest);
    connect(mTabBar,&MyTabBar::dragTabRequest,this,&MyTabWidget::dragTabRequest);
}


MyTabWidget::~MyTabWidget()
{}

void MyTabWidget::removeTabActually(int index)
{
    widget(index)->deleteLater();
    removeTab(index);
}

