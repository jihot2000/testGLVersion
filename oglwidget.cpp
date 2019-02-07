#include "oglwidget.h"
#include <QVector>
#include <QDebug>
#include <assert.h>

OGLWidget::OGLWidget(QWidget* parent, Qt::WindowFlags f)
    :QOpenGLWidget(parent, f)
    ,glCubeBuffer(QOpenGLBuffer::VertexBuffer)
    ,glCubeIndexBuffer(QOpenGLBuffer::IndexBuffer)
{
    timer = new QTimer(this);
    timer->setInterval(0);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    QSurfaceFormat tmpFormat;
    tmpFormat.setRenderableType(QSurfaceFormat::OpenGLES);
    tmpFormat.setProfile(QSurfaceFormat::NoProfile);
    tmpFormat.setVersion(3, 0);
    setFormat(tmpFormat);

    timer->start();
}

OGLWidget::~OGLWidget()
{

}

void OGLWidget::initializeGL()
{
    if(context()->isOpenGLES())
    {
        qDebug() << QString("OpenGL ES %1.%2").arg(format().majorVersion()).arg(format().minorVersion()).toStdString().data();
    }
    else
    {
        qDebug() << QString("OpenGL %1.%2").arg(format().majorVersion()).arg(format().minorVersion()).toStdString().data();
    }
    initializeOpenGLFunctions();

//    GLfloat tmpCubeVertex[24] = {
//        -0.5f, -0.5f, -0.5f,
//        0.5f, -0.5f, -0.5f,
//        0.5f, 0.5f, -0.5f,
//        -0.5f, 0.5f, -0.5f,
//        -0.5f, -0.5f, 0.5f,
//        0.5f, -0.5f, 0.5f,
//        0.5f, 0.5f, 0.5f,
//        -0.5f, 0.5f, 0.5f
//    };
//    GLushort tmpCubeIndex[] = {
//        0, 3, 1, 2, 5, 6, 4, 7, 255,
//        1, 5, 0, 4, 3, 7, 2, 6
//    };

    GLfloat tmpCubeVertex[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    GLushort tmpCubeIndex[] = {
        0, 2, 1
    };

    assert(glCubeBuffer.create());
    assert(glCubeBuffer.bind());
    glCubeBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    glCubeBuffer.allocate(tmpCubeVertex, sizeof(tmpCubeVertex));
    qDebug() << "sizeof(tmpCubeVertex)=" << sizeof(tmpCubeVertex);
    assert(glGetError() == GL_NO_ERROR);

    assert(glCubeIndexBuffer.create());
    assert(glCubeIndexBuffer.bind());
    glCubeIndexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    glCubeIndexBuffer.allocate(tmpCubeIndex, sizeof(tmpCubeIndex));
    qDebug() << "sizeof(tmpCubeIndex)=" << sizeof(tmpCubeIndex);
    assert(glGetError() == GL_NO_ERROR);

    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    assert(vertexShader.compileSourceFile(":/vertex_shader/simplevertex.vsh"));

    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    assert(fragShader.compileSourceFile(":/fragment_shader/simplefrag.fsh"));

    program = new QOpenGLShaderProgram(this);
    assert(program->addShader(&vertexShader));
    assert(program->addShader(&fragShader));
    assert(program->link());
    assert(program->bind());

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OGLWidget::resizeGL(int w, int h)
{
//    glViewport(0, 0, w, h);
}

void OGLWidget::paintGL()
{

    program->enableAttributeArray(0);
    program->setAttributeBuffer(0, GL_FLOAT, 0, 3);
    glEnable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    glEnable(GL_CULL_FACE);
    glDrawElements(GL_TRIANGLE_STRIP, 3, GL_UNSIGNED_SHORT, 0);
    glDisable(GL_CULL_FACE);
//    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
    glDisable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
    program->disableAttributeArray(0);


}
