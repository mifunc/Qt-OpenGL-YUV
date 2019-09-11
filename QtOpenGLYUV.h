#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtOpenGLYUV.h"

class QtOpenGLYUV : public QWidget
{
	Q_OBJECT

public:
	QtOpenGLYUV(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtOpenGLYUVClass ui;
};
