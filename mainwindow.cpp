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

    std::vector<std::pair<QString, int>> wordsSorted;
    for(auto it = wordFreq.begin(); it != wordFreq.end(); it++){
        wordsSorted.push_back({it.key(), it.value()});
    }
    std::sort(wordsSorted.begin(), wordsSorted.end(), [](const auto &a, const auto &b){
        return a.second > b.second;
    });

    QString display;

    for(auto & x: wordsSorted){
        QString key = x.first;
        int value = x.second;
        display += (key + ": " + QString::number(value));
        display += "\n";
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


void MainWindow::on_pushButton_2_clicked()
{
    QString key = ui->lineEdit->text();
    int freq = wordFreq[key];
    if(!freq)   ui->textEdit_2->setPlainText("The paragraph does not contain this word.");
    else    ui->textEdit_2->setPlainText(key + ": " + QString::number(freq));
}

