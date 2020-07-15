#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dndtabwidget.h"
#include <QString>
#include <QAction>
#include <QTextBrowser>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QMimeData>
#include <QDrag>
#include <QWindow>
#include <QScreen>
#include <QProcess>
#include <QCursor>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto tabWidget = new DnDTabWidget(this);
    setCentralWidget(tabWidget);
    setAcceptDrops(true);
    connect(tabWidget,&DnDTabWidget::openFileRequest,this,&MainWindow::openFileAt);
    connect(tabWidget,&DnDTabWidget::dragTabRequest,this,&MainWindow::dragTab);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(QString fileName)
{
    return openFileAt(fileName,-1);
    //If index is out of range, the tab is simply appended.
    //see http://doc.qt.io/qt-5/qtabwidget.html#insertTab
}

void MainWindow::openFileAt(QString fileName, int tabIndex)
{
    QFile file(fileName);
    if(! file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,tr("Error"),
                             tr("Cannot open file %1:\n%2").arg(fileName).arg(file.errorString()));
        return ;
    }
    QTextStream in(&file);
    in.setAutoDetectUnicode(true);

    auto browser = new QTextBrowser(this);
    auto tabWidget = qobject_cast<DnDTabWidget*>(centralWidget());
    Q_ASSERT(tabWidget);
    auto index = tabWidget->insertTab(tabIndex,browser,QFileInfo(fileName).baseName());
    tabWidget->setCurrentIndex(index);

    browser->setAcceptDrops(false);
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    browser->setSource(QUrl::fromLocalFile(fileName));
    browser->setPlainText(in.readAll());
    QGuiApplication::restoreOverrideCursor();

    file.close();
}

void MainWindow::dragTab(int tabIndex)
{
    //if(!isTabMovable(tabIndex)) return;
    auto tabWidget = qobject_cast<DnDTabWidget*>(centralWidget());
    Q_ASSERT(tabWidget);
    auto browser = qobject_cast<QTextBrowser*>(tabWidget->widget(tabIndex));
    Q_ASSERT(browser);

    auto drag = new QDrag(this);
    auto mimeData = new QMimeData;
    QPixmap thumbnail = windowHandle()->screen()->grabWindow(browser->winId());
    mimeData->setUrls({browser->source()});
    drag->setMimeData(mimeData);
    drag->setPixmap(thumbnail.scaled(200,200));

    auto dragAction = drag->exec(Qt::LinkAction);
    int currentIndex = tabWidget->indexOf(browser);
    qDebug() << "removed tab source" << tabIndex;
    qDebug() << "removed tab current" << currentIndex;
    if (dragAction==Qt::LinkAction) {
        tabWidget->removeTabActually(currentIndex);
    } else if (dragAction==Qt::IgnoreAction) {
        if(QProcess::startDetached(qApp->applicationFilePath(),
                                   {"-x",QString::number(QCursor::pos().x()),
                                    "-y",QString::number(QCursor::pos().y()),
                                   browser->source().toLocalFile()})) {
            tabWidget->removeTabActually(currentIndex);
        }
    } else {
        return;
    }
    if(tabWidget->count()==0) {
        qApp->closeAllWindows();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData * mimeData = event->mimeData();
    if(mimeData->hasUrls()) {
        for (const QUrl& url : mimeData->urls()) {
            openFile(url.toLocalFile());
        }
        event->acceptProposedAction();
    }
    else {
        event->ignore();
    }
}

void MainWindow::on_action_Open_triggered()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this,tr("Open file"),".",
                                                        tr("text file(*.txt);;any file(*)"));
    for(const QString& fileName : fileNames) {
        openFile(fileName);
    }
}
