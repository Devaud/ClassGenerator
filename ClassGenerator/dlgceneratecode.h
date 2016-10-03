#ifndef DLGCENERATECODE_H
#define DLGCENERATECODE_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>

class DlgCenerateCode : public QDialog
{
public:
    DlgCenerateCode(QString &code, QWidget *parent);

private:
    QTextEdit *m_generateCode;
    QPushButton *m_closeButton;
};

#endif // DLGCENERATECODE_H
