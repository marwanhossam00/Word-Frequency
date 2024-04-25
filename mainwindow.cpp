#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    currentFilePath = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Text Files (*.txt)"));
    if(currentFilePath.isEmpty())
        return;

    QFile file(currentFilePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Could not open file."));
        return;
    }

    QString content = file.readAll();

    file.close();

    ui->textEdit->setPlainText(content);
}


void MainWindow::on_pushButton_3_clicked()
{
    if(currentFilePath.isEmpty())   return;

    QFile file(currentFilePath);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Could not save file"));
        return;
    }
    QString content = ui->textEdit->toPlainText();

    QTextStream out(&file);
    out << content;

    file.close();

    MainWindow::countWordFrequency();
}

void MainWindow::countWordFrequency()
{
    wordFreq.clear();
    QString content = ui->textEdit->toPlainText();

    QRegularExpression rx("[^a-zA-z]+");

    QStringList words = content.split(rx, Qt::SkipEmptyParts);

    for(const QString &word:words)
        wordFreq[word.toLower()]++;

    auto it = wordFreq.begin();

    QString display;

    while(it != wordFreq.end()){
        QString key = it.key();
        int value = it.value();
        wordsList.append(key);
        display += (key + ": " + QString::number(value));
        display += "\n";
        ++it;
    }
    ui->textEdit_2->setPlainText(display);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setModel(new QStringListModel(wordsList, this));
    ui->lineEdit->setCompleter(completer);
}

