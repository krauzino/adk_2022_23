/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <draw.h>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QAction *actionOpen_element;
    QAction *actionDisplace;
    QAction *actionSettings;
    QAction *actionElement_Barrier;
    QAction *actionDisplace_2_elements;
    QAction *actionOpen_barrier;
    QAction *actionClear_all;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuDisplace;
    QMenu *menuInput;
    QMenu *menuClear_all;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(1217, 714);
        actionOpen_element = new QAction(MainForm);
        actionOpen_element->setObjectName(QString::fromUtf8("actionOpen_element"));
        actionDisplace = new QAction(MainForm);
        actionDisplace->setObjectName(QString::fromUtf8("actionDisplace"));
        actionSettings = new QAction(MainForm);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionElement_Barrier = new QAction(MainForm);
        actionElement_Barrier->setObjectName(QString::fromUtf8("actionElement_Barrier"));
        actionElement_Barrier->setCheckable(true);
        actionDisplace_2_elements = new QAction(MainForm);
        actionDisplace_2_elements->setObjectName(QString::fromUtf8("actionDisplace_2_elements"));
        actionOpen_barrier = new QAction(MainForm);
        actionOpen_barrier->setObjectName(QString::fromUtf8("actionOpen_barrier"));
        actionClear_all = new QAction(MainForm);
        actionClear_all->setObjectName(QString::fromUtf8("actionClear_all"));
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Canvas = new Draw(centralwidget);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));

        horizontalLayout->addWidget(Canvas);

        MainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1217, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuDisplace = new QMenu(menubar);
        menuDisplace->setObjectName(QString::fromUtf8("menuDisplace"));
        menuInput = new QMenu(menubar);
        menuInput->setObjectName(QString::fromUtf8("menuInput"));
        menuClear_all = new QMenu(menubar);
        menuClear_all->setObjectName(QString::fromUtf8("menuClear_all"));
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainForm->setStatusBar(statusbar);
        toolBar = new QToolBar(MainForm);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainForm->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuInput->menuAction());
        menubar->addAction(menuDisplace->menuAction());
        menubar->addAction(menuClear_all->menuAction());
        menuFile->addAction(actionOpen_element);
        menuFile->addAction(actionOpen_barrier);
        menuFile->addSeparator();
        menuDisplace->addSeparator();
        menuDisplace->addAction(actionDisplace);
        menuDisplace->addAction(actionDisplace_2_elements);
        menuDisplace->addSeparator();
        menuDisplace->addAction(actionSettings);
        menuInput->addAction(actionElement_Barrier);
        menuClear_all->addAction(actionClear_all);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "Energy minimizing splines", nullptr));
        actionOpen_element->setText(QCoreApplication::translate("MainForm", "Open file with element", nullptr));
        actionDisplace->setText(QCoreApplication::translate("MainForm", "Displace 1 element", nullptr));
        actionSettings->setText(QCoreApplication::translate("MainForm", "Settings", nullptr));
        actionElement_Barrier->setText(QCoreApplication::translate("MainForm", "Element/Barrier", nullptr));
        actionDisplace_2_elements->setText(QCoreApplication::translate("MainForm", "Displace 2 elements", nullptr));
        actionOpen_barrier->setText(QCoreApplication::translate("MainForm", "Open file with barrier", nullptr));
        actionClear_all->setText(QCoreApplication::translate("MainForm", "Clear all", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainForm", "File", nullptr));
        menuDisplace->setTitle(QCoreApplication::translate("MainForm", "Displace", nullptr));
        menuInput->setTitle(QCoreApplication::translate("MainForm", "Input", nullptr));
        menuClear_all->setTitle(QCoreApplication::translate("MainForm", "Clear", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainForm", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
