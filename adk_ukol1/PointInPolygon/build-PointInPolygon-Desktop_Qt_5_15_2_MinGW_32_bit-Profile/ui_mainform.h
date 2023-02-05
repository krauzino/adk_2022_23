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
#include <draw.h>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QPushButton *pushButton_File;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_Position;
    QLabel *label;
    QLabel *label_3;
    QPushButton *pushButton_Clear;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(1210, 760);
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
        label_4 = new QLabel(MainForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        pushButton_File = new QPushButton(MainForm);
        pushButton_File->setObjectName(QString::fromUtf8("pushButton_File"));

        verticalLayout->addWidget(pushButton_File);

        label_2 = new QLabel(MainForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        comboBox = new QComboBox(MainForm);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);

        verticalSpacer_2 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton_Position = new QPushButton(MainForm);
        pushButton_Position->setObjectName(QString::fromUtf8("pushButton_Position"));

        verticalLayout->addWidget(pushButton_Position);

        label = new QLabel(MainForm);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        label_3 = new QLabel(MainForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        pushButton_Clear = new QPushButton(MainForm);
        pushButton_Clear->setObjectName(QString::fromUtf8("pushButton_Clear"));

        verticalLayout->addWidget(pushButton_Clear);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "Point in polygon", nullptr));
        label_4->setText(QCoreApplication::translate("MainForm", "Choose file", nullptr));
        pushButton_File->setText(QCoreApplication::translate("MainForm", "Load file", nullptr));
        label_2->setText(QCoreApplication::translate("MainForm", "Choose method", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainForm", "Ray Crossing", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainForm", "Winding Number", nullptr));

        pushButton_Position->setText(QCoreApplication::translate("MainForm", "Analyze position", nullptr));
        label->setText(QString());
        label_3->setText(QString());
        pushButton_Clear->setText(QCoreApplication::translate("MainForm", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
