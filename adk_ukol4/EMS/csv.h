#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>
#include <QtGui>

class CSV
{
public:
    static std::vector<std::vector<std::string>> readCSV(std::string &filename);
    static std::vector<QPointF> getPoints(std::vector<std::vector<std::string>> &csv_content, double &x_min, double &x_max, double &y_min, double &y_max);
};

#endif // CSV_H
