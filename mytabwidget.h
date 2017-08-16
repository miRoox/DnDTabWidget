#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QTabWidget>

class MyTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    MyTabWidget(QWidget * parent = Q_NULLPTR);
    ~MyTabWidget();
    void removeTabActually(int index);

signals:
    void openFileRequest(QString/*fileName*/,int/*tabIndex*/);
    void dragTabRequest(int/*tabIndex*/);

};

#endif // MYTABWIDGET_H
