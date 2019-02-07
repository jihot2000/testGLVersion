#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QTimer>

class OGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
public:
    explicit OGLWidget(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~OGLWidget();

    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

private:
    QOpenGLBuffer glCubeBuffer;
    QOpenGLBuffer glCubeIndexBuffer;
    QOpenGLShaderProgram * program;
    QTimer * timer;
};

#endif // OGLWIDGET_H
