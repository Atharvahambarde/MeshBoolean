#include <QFileDialog>
#include <QGridLayout>
#include <QMessageBox>
#include "Visualizer.h"
#include "STLReader.h"
#include "OBJReader.h"
#include "OBJWriter.h"
#include "STLWriter.h"
#include "MeshJoiner.h"



Visualizer::Visualizer(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();

    connect(loadFirstFile, &QPushButton::clicked, this, &Visualizer::onLoadFirstFileClick);
    connect(loadSecondFile, &QPushButton::clicked, this, &Visualizer::onLoadSecondFileClick);
    connect(join, &QPushButton::clicked, this, &Visualizer::onJoinClick);
    connect(exportFile, &QPushButton::clicked, this, &Visualizer::onExportClick);
}

Visualizer::~Visualizer()
{

}

void Visualizer::setupUi()
{
    loadFirstFile = new QPushButton("Load File1", this);
    loadSecondFile = new QPushButton("Load File2", this);
    join = new QPushButton("Join", this);
    exportFile = new QPushButton("Export", this);
    openglWidgetFirstInput = new OpenGlWidget(this);
    openglWidgetSecondInput = new OpenGlWidget(this);
    openglWidgetOutput = new OpenGlWidget(this);
    //graphicsSynchronizer = new GraphicsSynchronizer(openglWidgetFisrtInput, openglWidgetSecondInput , openglWidgetOutput);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFirstFile, 0, 0);
    layout->addWidget(loadSecondFile, 0, 1);
    layout->addWidget(join, 0, 2);
    layout->addWidget(exportFile, 0, 3);
    layout->addWidget(openglWidgetFirstInput, 1, 0, 1, 2);
    layout->addWidget(openglWidgetSecondInput, 1, 2, 1, 2);
    layout->addWidget(openglWidgetOutput, 2, 0, 1, 4);
    


    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
}

void  Visualizer::onLoadFirstFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
        {
            STLReader reader;
            reader.read(inputFilePath.toStdString(), triangulation);
        }
        else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
        {
            OBJReader reader;
            reader.read(inputFilePath.toStdString(), triangulation);
        }
        OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(triangulation);
        openglWidgetFirstInput->addObject(data);
        
    }
}

void Visualizer::onLoadSecondFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("files (*.stl *.obj)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
        {
            STLReader reader;
            reader.read(inputFilePath.toStdString(), triangulation2);
        }
        else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
        {
            OBJReader reader;
            reader.read(inputFilePath.toStdString(), triangulation2);
        }
        OpenGlWidget::Data data = convertTrianglulationToGraphicsObject(triangulation2);
        //QVector< OpenGlWidget::Data> dataList = QVector< OpenGlWidget::Data>{ data };
        openglWidgetSecondInput->addObject(data);

    }
}




void Visualizer::onJoinClick()
{
    QFileDialog dialog(this);

    if (triangulation.isEmpty() || triangulation2.isEmpty())
    {
        QMessageBox::warning(this, tr("Data Error"), tr("Triangulation data is empty. Please ensure valid input before proceeding."));
        return;
    }

    dialog.setFileMode(QFileDialog::Directory);

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
        "/home",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);


    if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        QString exportFileName = dir + "/output.obj";
        Geometry::Matrix4x4 mat;
        Transformations::Transformation t;

        ObjWriter writer;
        writer.Write(exportFileName.toStdString(), outputTriangulation);

        OBJReader reader;
        reader.read(exportFileName.toStdString(), outputTriangulation);

    
        MeshJoiner meshJoinerInstance;
        std::vector<Triangulation> tri;
        tri.push_back(triangulation);
        tri.push_back(triangulation2);
        std::vector<Triangulation> result = meshJoinerInstance.performTransformations(tri);
       
       
        OpenGlWidget::Data data3 = convertTrianglulationToGraphicsObject(result[0]);
        OpenGlWidget::Data data4 = convertTrianglulationToGraphicsObject(result[1]);
      
        openglWidgetOutput->addObject(data3);
        openglWidgetOutput->addObject(data4);
    }
    else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        QString exportFileName = dir + "/output.stl";
        Geometry::Matrix4x4 mat;
        Transformations::Transformation t;

        STLWriter writer;
        writer.Write(exportFileName.toStdString(), outputTriangulation);

        STLReader reader;
        reader.read(exportFileName.toStdString(), outputTriangulation);

        MeshJoiner meshJoinerInstance;
        std::vector<Triangulation> tri1;
        tri1.push_back(triangulation);
        tri1.push_back(triangulation2);
        std::vector<Triangulation> result1 = meshJoinerInstance.performTransformations(tri1);
     
        OpenGlWidget::Data data3 = convertTrianglulationToGraphicsObject(result1[0]);
        OpenGlWidget::Data data4 = convertTrianglulationToGraphicsObject(result1[1]);

        openglWidgetOutput->addObject(data3);
        openglWidgetOutput->addObject(data4);

    }
}


void Visualizer::onExportClick()
{
    QFileDialog dialog(this);

    if (triangulation.isEmpty() || triangulation2.isEmpty())
    {
        QMessageBox::warning(this, tr("Data Error"), tr("Triangulation data is empty. Please ensure valid input before proceeding."));
        return;
    }

    if (inputFilePath.endsWith(".stl", Qt::CaseInsensitive))
    {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"), "", tr("files (*.obj)"));
        ObjWriter writer;
        writer.Write(fileName.toStdString(), outputTriangulation);
    }
    else if (inputFilePath.endsWith(".obj", Qt::CaseInsensitive))
    {
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save File"), "", tr("files (*.stl)"));
        STLWriter writer;
        writer.Write(fileName.toStdString(), outputTriangulation);
    }
}

OpenGlWidget::Data Visualizer::convertTrianglulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    for each (Triangle triangle in inTriangulation.Triangles)
    {
        for each (Point point in triangle.Points())
        {
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Z()]);
        }

        Point normal = triangle.Normal();

        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Z()]);
        }

        for (size_t i = 0; i < 3; i++)
        {
            data.colors.push_back(1.0);
            data.colors.push_back(1.0);
            data.colors.push_back(0.0);
        }
    }
    data.drawStyle = OpenGlWidget::DrawStyle::TRIANGLES;

    return data;
}