#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

#include "Triangulation.h"
#include "Transformation.h"
#include "OpenGlWidget.h"
#include "GraphicsSynchronizer.h"

using namespace Geometry;

class Visualizer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizer(QWidget* parent = nullptr);
    ~Visualizer();

private slots:
    void onLoadFirstFileClick();
    void onLoadSecondFileClick();
    void onJoinClick();
    void onExportClick();

private:
    void setupUi();
    OpenGlWidget::Data convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation);

private:
    Triangulation triangulation;
    Triangulation TranslationTriangulation;
    Triangulation RotationTriangulation;
    Triangulation ReverseRotationTriangulation;
    Triangulation ReverseTranslationTriangulation;

    Triangulation triangulation2;
    Triangulation TranslationTriangulation2;
    Triangulation RotationTriangulation2;
    Triangulation ReverseRotationTriangulation2;
    Triangulation ReverseTranslationTriangulation2;

    Triangulation outputTriangulation;

    QPushButton* loadFirstFile;
    QPushButton* loadSecondFile;
    QPushButton* join;
    QPushButton* exportFile;

    OpenGlWidget* openglWidgetFirstInput;
    OpenGlWidget* openglWidgetSecondInput;
   
    OpenGlWidget* openglWidgetOutput;

    GraphicsSynchronizer* graphicsSynchronizer;

    QVector<GLfloat> vertices;



    // translation data
    QString inputFilePath;

};

