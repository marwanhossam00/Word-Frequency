#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QMap>
#include <QPair>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString currentFilePath;
    QMap<QString, int> wordFreq;
    void countWordFrequency();
};
#endif // MAINWINDOW_H
