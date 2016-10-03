#include "dlgceneratecode.h"

DlgCenerateCode::DlgCenerateCode(QString &code, QWidget *parent) : QDialog(parent)
{
    this->m_generateCode = new QTextEdit();
    this->m_generateCode->setPlainText(code);
    this->m_generateCode->setReadOnly(true);
    this->m_generateCode->setFont(QFont("Courier"));
    this->m_generateCode->setLineWrapMode(QTextEdit::NoWrap);

    this->m_closeButton = new QPushButton(tr("close"));
    this->connect(this->m_closeButton, SIGNAL(clicked()), this, SLOT(accept()));

    QVBoxLayout *princiaplLayout = new QVBoxLayout();
    princiaplLayout->addWidget(this->m_generateCode);
    princiaplLayout->addWidget(this->m_closeButton);

    this->resize(350, 450);
    this->setLayout(princiaplLayout);
}
