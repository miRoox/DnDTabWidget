#ifndef MYTABBAR_H
#define MYTABBAR_H

#include <QTabBar>

class MyTabBar : public QTabBar
{
    Q_OBJECT

public:
    MyTabBar(QWidget * parent = Q_NULLPTR);
    ~MyTabBar();

signals:
    void openFileRequest(QString/*fileName*/,int/*tabIndex*/);
    void dragTabRequest(int/*tabIndex*/);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent (QMouseEvent *event) override;
    void mouseMoveEvent (QMouseEvent *event) override;
//    void mouseReleaseEvent (QMouseEvent *event) override;
};


#endif // MYTABBAR_H
