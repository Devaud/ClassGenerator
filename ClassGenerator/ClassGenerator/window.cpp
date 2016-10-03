#include "window.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    this->initialize();

    this->createAction();
    this->createMenu();

    // Create central zone
    this->m_centralZone = new QWidget;

    // Create principal layout
    this->m_principalLayout = new QVBoxLayout();

    this->createDefinitionClass();
    this->createOptions();
    this->createComments();

    this->m_generateButton = new QPushButton(tr("Generate"), this);
    this->m_generateButton->setEnabled(false);
    this->connect(this->m_generateButton, SIGNAL(clicked()), this, SLOT(generateCode()));

    // Add widget in the principal layout
    this->m_principalLayout->addWidget(this->m_definitionGroup);
    this->m_principalLayout->addWidget(this->m_optionsGroup);
    this->m_principalLayout->addWidget(this->m_commentsGroup);
    this->m_principalLayout->addWidget(this->m_generateButton);

    // Set the principal layout in the central zone
    this->m_centralZone->setLayout(m_principalLayout);


    // Set the central zone
    this->setCentralWidget(this->m_centralZone);
}

void Window::createComments()
{
    // User object interaction
    this->m_authorEdit = new QLineEdit();
    this->m_dateEdit = new QDateEdit(QDate::currentDate());
    this->m_descEdit = new QTextEdit();

    // Layout
    this->m_commentsLayout = new QFormLayout();
    this->m_commentsLayout->addRow(tr("Author :"), this->m_authorEdit);
    this->m_commentsLayout->addRow(tr("Creation date :"), this->m_dateEdit);
    this->m_commentsLayout->addRow(tr("Description :"), this->m_descEdit);

    // Group
    this->m_commentsGroup = new QGroupBox(tr("Add comments"), this);
    this->m_commentsGroup->setCheckable(true);
    this->m_commentsGroup->setChecked(false);
    this->m_commentsGroup->setLayout(this->m_commentsLayout);
}

void Window::createOptions()
{
    // User object interaction
    this->m_headerProtect = new QCheckBox(tr("Protect header to multiple includes"), this);
    this->m_headerProtect->setChecked(true);
    this->m_generateConstructor = new QCheckBox(tr("Generate default constructor"), this);
    this->m_generateDesctructor = new QCheckBox(tr("Generate desctructor"), this);

    // Layout
    this->m_optionsLayout = new QVBoxLayout();
    this->m_optionsLayout->addWidget(this->m_headerProtect);
    this->m_optionsLayout->addWidget(this->m_generateConstructor);
    this->m_optionsLayout->addWidget(this->m_generateDesctructor);

    // Group
    this->m_optionsGroup = new QGroupBox(tr("Options"), this);
    this->m_optionsGroup->setLayout(this->m_optionsLayout);
}

void Window::createDefinitionClass()
{
    // User object interaction
    this->m_nameEdit = new QLineEdit();
    this->connect(this->m_nameEdit, SIGNAL(textChanged(QString)), this, SLOT(editChanged(QString)));
    this->m_heritageEdit = new QLineEdit();

    // Layout
    this->m_definitionLayout = new QFormLayout();
    this->m_definitionLayout->addRow(tr("Name :"), this->m_nameEdit);
    this->m_definitionLayout->addRow(tr("Heritage :"), this->m_heritageEdit);

    // Group
    this->m_definitionGroup = new QGroupBox(tr("Class definition"), this);
    this->m_definitionGroup->setLayout(this->m_definitionLayout);
}

void Window::createAction()
{
    // Quit action
    this->m_quitAction = new QAction(tr("Quit"), this);
    this->m_quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    this->connect(this->m_quitAction, SIGNAL(triggered()), this, SLOT(close()));

    // Generate action
    this->m_generateAction = new QAction(tr("Generate"), this);
    this->m_generateAction->setShortcut(QKeySequence("Ctrl+G"));
    this->m_generateAction->setEnabled(false);
    this->connect(this->m_generateAction, SIGNAL(triggered()), this, SLOT(generateCode()));
}

void Window::createMenu()
{
    // File menu
    this->m_fileMenu = this->menuBar()->addMenu(tr("&File"));
    this->m_fileMenu->addAction(this->m_generateAction);
    this->m_fileMenu->addSeparator();
    this->m_fileMenu->addAction(this->m_quitAction);

    // Help menu
    this->m_helpMenu = this->menuBar()->addMenu(tr("&?"));
}

void Window::initialize()
{
    this->setFixedSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    this->setWindowTitle(tr("Class generator"));

    // Put the window in the middle screen
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

void Window::editChanged(QString changedText)
{
    bool enaState = (changedText.size() > NULL_VALUE) ? true : false;
    this->m_generateAction->setEnabled(enaState);
    this->m_generateButton->setEnabled(enaState);
}

void Window::generateCode()
{
    if (this->m_nameEdit->text().isEmpty())
    {
        QMessageBox::critical(this, "Error", "Class name is required !");
        return;
    }

    QString code = this->generateHeader();

    DlgCenerateCode *dlgGenerateCode = new DlgCenerateCode(code, this);
    dlgGenerateCode->exec();
}

QString Window::generateHeader()
{
    QString code = "";

    QString name = (this->m_nameEdit->text().size() > 0) ? this->m_nameEdit->text() : "";
    QString heritage = (this->m_heritageEdit->text().size() > 0) ? this->m_heritageEdit->text() : "";

    // Create header protection
    if (this->m_headerProtect->isChecked())
    {
        code += "#ifndef " + name.toUpper() + "_H\n";
        code += "#define " + name.toUpper() + "_H\n";
        code += "\n";
    }

    // Add description comments
    if (this->m_commentsGroup->isChecked())
    {
        code += "/*\n";
        code += "Author      : " + this->m_authorEdit->text() + "\n";
        code += "Date        : " + this->m_dateEdit->text() + "\n";
        code += "Description : \n" + this->m_descEdit->toPlainText() + "\n";
        code += "*/\n";
        code += "\n";
    }

    // Create class
    code += "Class " + name;
    code += (!heritage.isEmpty()) ? " : " + heritage + "\n" : "\n";
    code += "{\n";
    code += "public:\n";
    code += (this->m_generateConstructor->isChecked()) ? name + "();\n" : "\n";
    code += (this->m_generateDesctructor->isChecked()) ? "~" + name + "();\n" : "";
    code += "private:\n";
    code += "};\n";
    code += (this->m_headerProtect->isChecked()) ? "\n#endif" : "";

    return code;
}
