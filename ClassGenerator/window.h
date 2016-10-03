#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QMessageBox>

#include "dlgceneratecode.h"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

signals:

private slots:
    ///
    /// \brief Check if the edit is empty or not
    /// \param changedText Text which changed
    ///
    void editChanged(QString changedText);
    void generateCode();

    ///
    /// \brief Clear all fields (reset)
    ///
    void clearFields();

private:
    ///
    /// \brief initialize the window application
    ///
    void initialize();
    void createMenu();
    void createAction();
    void createDefinitionClass();
    void createOptions();
    void createComments();
    void createButtons();
    QString generateHeader();

    // Const
    static int const DEFAULT_WIDTH = 350;
    static int const DEFAULT_HEIGHT = 550;
    static int const NULL_VALUE = 0;
    static QString const DEFAULT_TEXT = "";
    static bool const DEFAULT_CHECKBOX = false;

    // Fields
    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QAction *m_quitAction;
    QAction *m_generateAction;
    QAction *m_clearFieldsAction;
    QLineEdit *m_nameEdit;
    QLineEdit *m_heritageEdit;
    QFormLayout *m_definitionLayout;
    QGroupBox *m_definitionGroup;
    QCheckBox *m_headerProtect;
    QCheckBox *m_generateConstructor;
    QCheckBox *m_generateDesctructor;
    QGroupBox *m_optionsGroup;
    QVBoxLayout *m_optionsLayout;
    QVBoxLayout *m_principalLayout;
    QWidget *m_centralZone;
    QGroupBox *m_commentsGroup;
    QFormLayout *m_commentsLayout;
    QLineEdit *m_authorEdit;
    QDateEdit *m_dateEdit;
    QTextEdit *m_descEdit;
    QPushButton *m_generateButton;
    QPushButton *m_clearFields;
    QHBoxLayout *m_buttonLayout;
};

#endif // WINDOW_H
