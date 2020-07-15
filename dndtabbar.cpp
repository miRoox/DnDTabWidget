#include "dndtabbar.h"
#include <QUrl>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDebug>

DnDTabBar::DnDTabBar(QWidget *parent)
    : QTabBar(parent)
{
    setMovable(true);
    setAcceptDrops(true);
}

DnDTabBar::~DnDTabBar()
{}

void DnDTabBar::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else event->ignore();
}

void DnDTabBar::dropEvent(QDropEvent *event)
{
    const QMimeData * mimeData = event->mimeData();
    if(mimeData->hasUrls()) {
        qDebug() << "dropped tab" << tabAt(event->pos());
        for (const QUrl& url : mimeData->urls()) {
            emit openFileRequest(url.toLocalFile(),tabAt(event->pos()));
        }
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

void DnDTabBar::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MiddleButton) {
        emit tabCloseRequested(tabAt(event->pos()));
    }
    QTabBar::mousePressEvent(event);
}

void DnDTabBar::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton) {
        if(!geometry().contains(event->pos())) {
            emit dragTabRequest(currentIndex());
        }
    }
    QTabBar::mouseMoveEvent(event);
}
