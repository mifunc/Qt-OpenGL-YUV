#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>

class XVideoWidget : public QOpenGLWidget,protected QOpenGLFunctions
{
	Q_OBJECT

public:

	void initializeGL();
	void paintGL();
	void resizeGL(int width,int height);

	XVideoWidget(QWidget *parent);
	~XVideoWidget();

	GLuint texs[3] = {0};
	GLuint unis[3] = {0};
	unsigned char* datas[3] = {0};

	QGLShaderProgram program;

	int width = 240;
	int height = 128;

};
