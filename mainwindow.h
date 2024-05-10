#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QMap>
#include <QPair>
#include <QList>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QRegularExpression>
#include <QCompleter>
#include <QStringListModel>
#include <bits/stdc++.h>
#include <algorithm>

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

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QCompleter *completer;
    QString currentFilePath;
    QStringList wordsList;
    QMap<QString, int> rank;
    std::vector<std::pair<QString, int>> wordsSorted;
    QMap<QString, int> wordFreq;
    bool compareByValue(const QPair<QString, int> &a, const QPair<QString, int> &b);
    void countWordFrequency();
    void rankCount();
};
#endif // MAINWINDOW_H
