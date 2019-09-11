#include "XVideoWidget.h"
#include <QTimer>
#include <iostream>
#define STR(x)  #x
#define V_VER 3
#define T_VER 4


using namespace std;
FILE* fp = NULL;
//顶点shader
const char* vString = STR(
attribute vec4 vertexIn;
attribute vec2 textureIn;
varying vec2 textureOut;
void main(void)
{
	gl_Position = vertexIn;
	textureOut = textureIn;
}
);


//片元shader
const char* tString = STR(
varying vec2 textureOut;
uniform sampler2D tex_y;
uniform sampler2D tex_u;
uniform sampler2D tex_v;
void main(void)
{
	vec3 yuv;
	vec3 rgb;
	yuv.x = texture2D(tex_y, textureOut).r;
	yuv.y = texture2D(tex_u, textureOut).r - 0.5;
	yuv.z = texture2D(tex_v, textureOut).r - 0.5;
	rgb = mat3(1.0, 1.0, 1.0,
		0.0, -0.39465, 2.03211,
		1.13983, -0.58060, 0.0) * yuv;
	gl_FragColor = vec4(rgb, 1.0);
}

);




void XVideoWidget::initializeGL() {
	initializeOpenGLFunctions();
	program.addShaderFromSourceCode(QGLShader::Vertex,vString);
	program.addShaderFromSourceCode(QGLShader::Fragment,tString);
	program.bindAttributeLocation("vertexIn",V_VER);
	program.bindAttributeLocation("textureIn",T_VER);
	program.link();
	program.bind();

	unis[0] = program.uniformLocation("tex_y");
	unis[1] = program.uniformLocation("tex_u");
	unis[2] = program.uniformLocation("tex_v");


	//传递顶点和材质坐标
	//顶点
	static const GLfloat ver[] = {
		-1.0f,-1.0f,
		1.0f,-1.0f,
		-1.0f, 1.0f,
		1.0f,1.0f
	};

	//材质
	static const GLfloat tex[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};
	
	glVertexAttribPointer(V_VER,2,GL_FLOAT,0,0,ver);
	glEnableVertexAttribArray(V_VER);

	glVertexAttribPointer(T_VER,2,GL_FLOAT,0,0,tex);
	glEnableVertexAttribArray(T_VER);


	//创建材质 YUV420P
	//在数组texs中返回n个当期未使用的值，表示纹理对象的名称
	glGenTextures(3,texs);
	//Y
	glBindTexture(GL_TEXTURE_2D,texs[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RED,width,height,0,GL_RED,GL_UNSIGNED_BYTE,0);

	//U
	glBindTexture(GL_TEXTURE_2D, texs[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width/2, height/2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	
	//V
	glBindTexture(GL_TEXTURE_2D, texs[2]); //绑定材质
	//设置材质参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//创建显卡空间
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width/2, height/2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
	

	//创建数据空间
	datas[0] = new unsigned char[width*height];
	datas[1] = new unsigned char[width * height/4];
	datas[2] = new unsigned char[width * height/4];

	fp = fopen("out240x128.yuv","rb");

	QTimer* t1 = new QTimer(this);
	connect(t1,SIGNAL(timeout()),this,SLOT(update()));
	t1->start(40);



}
void XVideoWidget::paintGL() {
	if (feof(fp)) {
		fseek(fp,0,SEEK_SET);
	}
	fread(datas[0],1,width*height,fp);
	fread(datas[1], 1, width * height/4, fp);
	fread(datas[2], 1, width * height/4, fp);
	//绑定纹理对象和纹理单元
	glActiveTexture(GL_TEXTURE0);//0号纹理单元
	glBindTexture(GL_TEXTURE_2D,texs[0]); //纹理单元绑定纹理对象
	//修改显卡空间数据
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,GL_RED,GL_UNSIGNED_BYTE,datas[0]);
	//纹理单元和着色器绑定
	glUniform1i(unis[0],0);

	glActiveTexture(GL_TEXTURE0+1);
	glBindTexture(GL_TEXTURE_2D, texs[1]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width/2, height/2, GL_RED, GL_UNSIGNED_BYTE, datas[1]);
	glUniform1i(unis[1], 1);

	glActiveTexture(GL_TEXTURE0+2);
	glBindTexture(GL_TEXTURE_2D, texs[2]);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width/2, height/2, GL_RED, GL_UNSIGNED_BYTE, datas[2]);
	glUniform1i(unis[2], 2);

	glDrawArrays(GL_TRIANGLE_STRIP,0,4);
}
void XVideoWidget::resizeGL(int width, int height) {
	cout << "width:"<<width <<"height:"<< height << endl;
}

XVideoWidget::XVideoWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
}

XVideoWidget::~XVideoWidget()
{
}
