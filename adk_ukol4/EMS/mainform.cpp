#include "mainform.h"
#include "ui_mainform.h"
#include "algorithms.h"
#include "csv.h"
#include "settings.h"
#include <QFileDialog>

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);

    // Initialization
    iterDisplace1 = 500;
    iterDisplace2 = 500;

}

MainForm::~MainForm()
{
    delete ui;
}


void MainForm::on_actionElement_Barrier_changed()
{
    // Change drawn element
    ui->Canvas->switchDrawnElement();
}


void MainForm::on_actionDisplace_triggered()
{
    // Run displacement
    std::vector<QPointF> element = ui->Canvas->getElement();
    std::vector<QPointF> barrier = ui->Canvas->getBarrier();

    // Set parameters
    double dmin = settings.getdmin();
    double alfa = settings.getalfa();
    double beta = settings.getbeta();
    double gamma = settings.getgamma();
    double lambda = settings.getlambda();
    int iterDisplace1 = settings.getIterDispl1();

    /*
    // Set parameters
    double dmin = 100;
    double alfa = 0.3;
    double beta = 10000;
    double gamma = 10000;
    double lambda = 20;
    int iterDisplace1 = settings.getIterDispl1();

    */


    // Run displacement
    Algorithms a;
    std::vector<QPointF> displaced_1 = a.minEnergySpline1Element1Barrier(element, barrier, alfa, beta, gamma, lambda, dmin, iterDisplace1);

    // Set results
    ui->Canvas->setDisplaced(displaced_1);

    repaint();
}


void MainForm::on_actionDisplace_2_elements_triggered()
{
    // Run displacement
    std::vector<QPointF> element1 = ui->Canvas->getElement();
    std::vector<QPointF> element2 = ui->Canvas->getBarrier();

    // Set parameters
    double dmin = settings.getdmin();
    double alfa = settings.getalfa();
    double beta = settings.getbeta();
    double gamma = settings.getgamma();
    double lambda = settings.getlambda();
    int iterDisplace2 = settings.getIterDispl2();

  /*
    // Set parameters
    double dmin = 1;
    double alfa = 0.3;
    double beta = 10000;
    double gamma = 10000;
    double lambda = 20;
    int iterDisplace2 = settings.getIterDispl2();
   */

    // Run displacement
    Algorithms a;
    auto [displaced1, displaced2] = a.minEnergySpline2Elements(element1, element2, alfa, beta, gamma, lambda, dmin, iterDisplace2);

    // Set results
    ui->Canvas->setDisplaced(displaced1);
    ui->Canvas->setDisplaced2(displaced2);

    repaint();
}


 void MainForm::on_actionOpen_element_triggered()
            {
                // Open file and import data
                // Create min-max box coordinates for loaded data
                CSV csvObject;
                double x_min =  1e10;
                double x_max = -1e10;
                double y_min =  1e10;
                double y_max = -1e10;

                // Choose file
                QString path(QFileDialog::getOpenFileName(this, tr("Open file with points"), "../", tr("CSV Files (*.csv)")));

                // Convert to string path
                std::string filename = path.toStdString();
                if (filename.length() > 0)
                    {
                // Read chosen file
                std::vector<QPointF> pointsElement = csvObject.readCSV(filename, x_min, x_max, y_min, y_max);

                // Get canvas size
                int canvas_width = ui->Canvas->size().width();
                int canvas_height = ui->Canvas->size().height();

                // Size ratio for transformation to canvas
                double dataset_width = x_max - x_min;
                double dataset_height = y_max - y_min;
                double x_ratio = canvas_width/dataset_width;
                double y_ratio = canvas_height/dataset_height;

                // Get scale for whole dataset
                double scale;
                if (x_ratio < y_ratio)
                    scale = x_ratio;
                else
                    scale = y_ratio;
                ui->Canvas->setScale(scale);

                // Coordinates of top left corner of the canvas
                int x_left_top = ui->Canvas->geometry().x();
                int y_left_top = ui->Canvas->geometry().y();

                // Top left corner (origin offset)
                int offset_x = ui->Canvas->x();
                int offset_y = ui->Canvas->y();

                // Offsets
                ui->Canvas->setOffsets(offset_x, offset_y);

                // Translation parameter for transformation
                double x_trans = x_min - x_left_top;
                double y_trans = y_min - y_left_top;

                // Translations
                ui->Canvas->setTrans(x_trans, y_trans);

                // Draw points
                ui->Canvas->drawCSVPointsElement(pointsElement);
            }

            }
            void MainForm::on_actionOpen_barrier_triggered()
            {
                // Open file and import data
                // Create min-max box coordinates for loaded data
                CSV csvObject;
                double x_min =  1e10;
                double x_max = -1e10;
                double y_min =  1e10;
                double y_max = -1e10;

                // Choose file
                QString path(QFileDialog::getOpenFileName(this, tr("Open file with points"), "../", tr("CSV Files (*.csv)")));

                // Convert to string path
                std::string filename = path.toStdString();
                if (filename.length() > 0)
                    {
                // Read chosen file
                std::vector<QPointF> pointsBarrier = csvObject.readCSV(filename, x_min, x_max, y_min, y_max);

                // Get canvas size
                int canvas_width = ui->Canvas->size().width();
                int canvas_height = ui->Canvas->size().height();

                // Size ratio for transformation to canvas
                double dataset_width = x_max - x_min;
                double dataset_height = y_max - y_min;
                double x_ratio = canvas_width/dataset_width;
                double y_ratio = canvas_height/dataset_height;

                // Get scale for whole dataset
                double scale;
                if (x_ratio < y_ratio)
                    scale = x_ratio;
                else
                    scale = y_ratio;
                ui->Canvas->setScale(scale);

                // Coordinates of top left corner of the canvas
                int x_left_top = ui->Canvas->geometry().x();
                int y_left_top = ui->Canvas->geometry().y();

                // Top left corner (origin offset)
                int offset_x = ui->Canvas->x();
                int offset_y = ui->Canvas->y();

                // Offsets
                ui->Canvas->setOffsets(offset_x, offset_y);

                // Translation parameter for transformation
                double x_trans = x_min - x_left_top;
                double y_trans = y_min - y_left_top;

                // Translations
                ui->Canvas->setTrans(x_trans, y_trans);

                // Draw points
                ui->Canvas->drawCSVPointsBarrier(pointsBarrier);
            }}

            void MainForm::on_actionClear_all_triggered()
            {
                // Clear all
                ui->Canvas->clearElement();
                ui->Canvas->clearBarrier();
                ui->Canvas->clearDisplaced();
                ui->Canvas->clearDisplaced2();
                ui->Canvas->clearPointsElement();
                ui->Canvas->clearPointsBarrier();
                repaint();
            }

void MainForm::on_actionSettings_triggered()
{
    // OK button
    if (settings.exec() == QDialog::Accepted)
    {
        // Set properties
        iterDisplace1 = settings.getIterDispl1();
        iterDisplace2 = settings.getIterDispl2();
        double dmin = settings.getdmin();
        double alfa = settings.getalfa();
        double beta = settings.getbeta();
       double  gamma = settings.getgamma();
        double lambda = settings.getlambda();

    }

}
