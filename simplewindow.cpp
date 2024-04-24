#include "simplewindow.h"

#include <QtWidgets>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

SimpleWindow::SimpleWindow(QWidget *parent) :
    QWidget(parent)
{
    auto noteLabel = new QLabel("Note:", this);
    auto noteEdit = new QTextEdit(this);
    auto clearButton = new QPushButton("Clear", this);
    auto saveButton = new QPushButton("Save", this);

    QString text = "Marwan\n";
    QObject::connect(saveButton, SIGNAL(clicked)
                     ,noteEdit,SLOT(insertPlainText(QString)));

    auto outer = new QVBoxLayout;
    outer->addWidget(noteLabel);
    outer->addWidget(noteEdit);
    {
        auto inner = new QHBoxLayout;
        inner->addWidget(clearButton);
        inner->addWidget(saveButton);
        outer->addLayout(inner);
    }
    this->setLayout(outer);
}
