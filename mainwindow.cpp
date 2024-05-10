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

//Mariem Ali
void MainWindow::on_actionOpen_triggered()
{
    // Upload file
    currentFilePath = QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("Text Files (*.txt)"));

    QFile file(currentFilePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Could not open file."));
        return;
    }

    //Display on GUI TextEditor
    QString content = file.readAll();

    file.close();

    //GUI Display
    ui->textEdit->setPlainText(content);
}

//Process Button
//Khaled
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
    MainWindow::rankCount();
}

//Marwan & Moussab
void MainWindow::rankCount()
{
    int highestRank = wordsSorted[0].second;
    int rankNum = 1;

    for(auto& x: wordsSorted){
        if(x.second != highestRank){
            highestRank = x.second;
            rankNum++;
            rank[x.first] = rankNum;
        }
        else
            rank[x.first] = rankNum;
    }
}

//Marwan & Mariem
void MainWindow::countWordFrequency()
{
    wordFreq.clear();
    QString content = ui->textEdit->toPlainText();

    QRegularExpression rx("[^a-zA-z]+");

    wordsList = content.split(rx, Qt::SkipEmptyParts);

    std::vector<std::pair<QString, int>> tmp;

    for(const QString &word:wordsList)
        wordFreq[word.toLower()]++;

    for(auto it = wordFreq.begin(); it != wordFreq.end(); it++)
        tmp.push_back({it.key(), it.value()});

    std::sort(tmp.begin(), tmp.end(), [](const auto &a, const auto &b){
        return a.second > b.second;
    });

    wordsSorted = tmp;

    QString display = "";

    for(auto & x: tmp){
        QString key = x.first;
        int value = x.second;
        display += (key + ": " + QString::number(value));
        display += "\n";
    }

    ui->textEdit_2->setPlainText(display);
}

//Marwan
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    completer = new QCompleter(this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    completer->setModel(new QStringListModel(wordsList, this));
    ui->lineEdit->setCompleter(completer);
}


//Hazem
//Display Frequency
void MainWindow::on_pushButton_2_clicked()
{
    QString key = ui->lineEdit->text();
    int freq = wordFreq[key];
    if(!freq)   ui->textEdit_2->setPlainText("The paragraph does not contain this word.");
    else    ui->textEdit_2->setPlainText(key + ": " + QString::number(freq));
}

//Hazem
//Display Ranking
void MainWindow::on_pushButton_clicked()
{
    QString query = ui->lineEdit->text();
    if(rank[query])   ui->textEdit_2->setPlainText(query + ": " + QString::number(rank[query]));
    else    ui->textEdit_2->setPlainText("The paragraph does not contain this word.");
}

