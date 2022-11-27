#ifndef CSV_H
#define CSV_H
#include <string>
#include <vector>
#include <QtGui>


class csv
{
public:
    csv();

    std::vector<QPolygon> readCsv(std::string &filename);
};

#endif // CSV_H
