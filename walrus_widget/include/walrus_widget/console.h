#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QScrollBar>

#include "qnode.h"

class Console : public QFrame{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = 0,  qnode::QNode* qnode = 0 );
    ~Console();

Q_SIGNALS:

public Q_SLOTS:

protected:
    QLineEdit* input_;
    QTextEdit* message_box_;
    QScrollBar* scroll_;

};

#endif // CONSOLE_H
