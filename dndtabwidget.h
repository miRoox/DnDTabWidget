#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>

class DnDTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    DnDTabWidget(QWidget * parent = Q_NULLPTR);
    ~DnDTabWidget();
    void removeTabActually(int index);

signals:
    void openFileRequest(QString/*fileName*/,int/*tabIndex*/);
    void dragTabRequest(int/*tabIndex*/);

};

#endif // MYTABWIDGET_H
