#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QString;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openFile(QString fileName);
    void openFileAt(QString fileName, int tabIndex);
    void dragTab(int tabIndex);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void on_action_Open_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
