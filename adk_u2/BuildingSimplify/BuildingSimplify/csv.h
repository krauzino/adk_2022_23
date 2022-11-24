#ifndef CSV_H
#define CSV_H

#include <string>
#include <vector>
#include <QtGui>

class CSV
{
public:
    CSV();
    std::vector<QPolygonF> read_CSV(std::string &filename, double &xmin, double &xmax, double &ymin, double &ymax);
};

#endif // CSV_H
