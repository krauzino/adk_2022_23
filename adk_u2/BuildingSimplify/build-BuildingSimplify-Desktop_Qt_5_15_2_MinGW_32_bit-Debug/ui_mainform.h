/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "draw.h"

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QVBoxLayout *verticalLayout;
    QPushButton *load_data;
    QLabel *label;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QPushButton *simplify;
    QSpacerItem *verticalSpacer_2;
    QPushButton *clear;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(1183, 772);
        horizontalLayout = new QHBoxLayout(MainForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Canvas = new Draw(MainForm);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Canvas->sizePolicy().hasHeightForWidth());
        Canvas->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Canvas);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        load_data = new QPushButton(MainForm);
        load_data->setObjectName(QString::fromUtf8("load_data"));

        verticalLayout->addWidget(load_data);

        label = new QLabel(MainForm);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        comboBox = new QComboBox(MainForm);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        simplify = new QPushButton(MainForm);
        simplify->setObjectName(QString::fromUtf8("simplify"));

        verticalLayout->addWidget(simplify);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        clear = new QPushButton(MainForm);
        clear->setObjectName(QString::fromUtf8("clear"));

        verticalLayout->addWidget(clear);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "Simplify Building", nullptr));
        load_data->setText(QCoreApplication::translate("MainForm", "Load data", nullptr));
        label->setText(QCoreApplication::translate("MainForm", "Select method", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainForm", "Minimum Area Rectangle", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainForm", "Wall Average", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainForm", "Longest Edge", nullptr));

        simplify->setText(QCoreApplication::translate("MainForm", "Simplify", nullptr));
        clear->setText(QCoreApplication::translate("MainForm", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
