/********************************************************************************
** Form generated from reading UI file 'emotion.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMOTION_H
#define UI_EMOTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmotionClass
{
public:
    QWidget *centralWidget;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QLabel *imm;
    QComboBox *comboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EmotionClass)
    {
        if (EmotionClass->objectName().isEmpty())
            EmotionClass->setObjectName(QString::fromUtf8("EmotionClass"));
        EmotionClass->resize(530, 378);
        centralWidget = new QWidget(EmotionClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        button1 = new QPushButton(centralWidget);
        button1->setObjectName(QString::fromUtf8("button1"));
        button1->setGeometry(QRect(20, 290, 151, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Gill Sans MT"));
        font.setPointSize(14);
        button1->setFont(font);
        button2 = new QPushButton(centralWidget);
        button2->setObjectName(QString::fromUtf8("button2"));
        button2->setGeometry(QRect(190, 290, 151, 31));
        button2->setFont(font);
        button3 = new QPushButton(centralWidget);
        button3->setObjectName(QString::fromUtf8("button3"));
        button3->setGeometry(QRect(360, 290, 151, 31));
        button3->setFont(font);
        imm = new QLabel(centralWidget);
        imm->setObjectName(QString::fromUtf8("imm"));
        imm->setGeometry(QRect(0, 0, 531, 291));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(0, 0, 111, 22));
        EmotionClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EmotionClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 530, 21));
        EmotionClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EmotionClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        EmotionClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EmotionClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        EmotionClass->setStatusBar(statusBar);

        retranslateUi(EmotionClass);

        QMetaObject::connectSlotsByName(EmotionClass);
    } // setupUi

    void retranslateUi(QMainWindow *EmotionClass)
    {
        EmotionClass->setWindowTitle(QApplication::translate("EmotionClass", "FEAtuREs", nullptr));
        button1->setText(QApplication::translate("EmotionClass", "Real Time", nullptr));
        button2->setText(QApplication::translate("EmotionClass", "Registra", nullptr));
        button3->setText(QApplication::translate("EmotionClass", "Carica e Analizza", nullptr));
        imm->setText(QString());
        comboBox->setItemText(0, QApplication::translate("EmotionClass", "Webcam Interna", nullptr));
        comboBox->setItemText(1, QApplication::translate("EmotionClass", "Webcam Esterna", nullptr));

    } // retranslateUi

};

namespace Ui {
    class EmotionClass: public Ui_EmotionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMOTION_H
