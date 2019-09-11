/********************************************************************************
** Form generated from reading UI file 'QtOpenGLYUV.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTOPENGLYUV_H
#define UI_QTOPENGLYUV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include "XVideoWidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtOpenGLYUVClass
{
public:
    XVideoWidget *openGLWidget;

    void setupUi(QWidget *QtOpenGLYUVClass)
    {
        if (QtOpenGLYUVClass->objectName().isEmpty())
            QtOpenGLYUVClass->setObjectName(QString::fromUtf8("QtOpenGLYUVClass"));
        QtOpenGLYUVClass->resize(600, 400);
        openGLWidget = new XVideoWidget(QtOpenGLYUVClass);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(10, 10, 581, 381));

        retranslateUi(QtOpenGLYUVClass);

        QMetaObject::connectSlotsByName(QtOpenGLYUVClass);
    } // setupUi

    void retranslateUi(QWidget *QtOpenGLYUVClass)
    {
        QtOpenGLYUVClass->setWindowTitle(QApplication::translate("QtOpenGLYUVClass", "QtOpenGLYUV", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtOpenGLYUVClass: public Ui_QtOpenGLYUVClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTOPENGLYUV_H
