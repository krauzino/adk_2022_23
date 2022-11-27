#include <QFileDialog>
#include <string>
#include "mainform.h"
#include "ui_mainform.h"
#include "algorithms.h"
#include "csv.h"

MainForm::MainForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_pushButton_File_clicked()
{
    csv csvObject;

    // Choose file
    QString file_path(QFileDialog::getOpenFileName(this, tr("Open CSV with polygons"), "../", tr("CSV Files (*.csv)")));

    // Convert to string path
    std::string filename = file_path.toStdString();

    // Read the chosen file
    std::vector<QPolygon> polygonVector = csvObject.readCsv(filename);

    // Draw polygons
    ui->Canvas->drawPolygons(polygonVector);
}

void MainForm::on_pushButton_Position_clicked()
{
    // Analyze position of the point
    QPointF q = ui->Canvas->getPoint();
    QString alg = ui->comboBox->currentText();
    QPolygon pol;
    std::vector<int> results;
    std::vector<QPoint> vertices = ui->Canvas->getVertices();

    // Create polygon that will be processed
    for (QPoint vertex : vertices)
        pol << vertex;

    ui->Canvas->pushPolygon(pol);
    std::vector<QPolygon> pols = ui->Canvas->getPolygons();

    // Get position
    Algorithms a;
    int pos;
    pos = a.processPols(q, pols, alg, results);

    // Store position of the point
    ui->Canvas->addResults(results);
    results.clear();
    ui->Canvas->repaint();
}

void MainForm::on_pushButton_Clear_clicked()
{
    ui->Canvas->clearScreen();
    repaint();
}
