#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <QDir>
#include "csv.h"

CSV::CSV()
{

}

std::vector<QPolygonF> CSV::readCSV(std::string &filename, double &xmin, double &xmax, double &ymin, double &ymax)
{
    // Read CSV file and create polygons from it
    // Vector for storing result
    std::vector<QPolygonF> result;

    // Supplementary variables
    std::string line, column;
    std::ifstream file(filename);

    // Check if file is opened
    if(!file.is_open()) throw std::runtime_error("File not opened.");

    // Read column names
    if(file.good())
    {
        // Get first line from file and create stringstream
        std::getline(file, line);
        std::stringstream stringstream(line);

        // Get column names
        while(std::getline(stringstream, column, ',')){
        }
    }

    // Read CSV file
    while(std::getline(file, line))
    {
        // Edit linestring
        line.erase(remove(line.begin(), line.end(), '"'), line.end());
        line.erase(remove(line.begin(), line.end(), '('), line.end());
        line.erase(remove(line.begin(), line.end(), ')'), line.end());

        // Remove text symbols of string ("MultiPolygon")
        line.erase(0,12);

        // Stringstream of the current line
        std::stringstream stringstream(line);

        // Current column ID
        int columnID = 0;

        // Supplementary variables
        int coordinates = 0;
        int x, y;
        std::string coordinate_pair, coordinate;
        QPolygonF polygon;

        // Go through all points in polygon
        while(std::getline(stringstream, coordinate_pair, ','))
        {
            std::stringstream ss2(coordinate_pair);

            // Go through all coordinates in point
            while(std::getline(ss2, coordinate, ' '))
            {
                if (coordinate == "")
                    continue;

                // Coordinate must be x and y
                if (coordinates < 2)
                {
                    // Coordinate x
                    if (coordinates == 0)
                    {
                        // Convert string to integer
                        x = (std::stod(coordinate));

                        // Update min-max box coordinates
                        if (x < xmin)
                            xmin = x;

                        if (x > xmax)
                            xmax = x;

                        coordinates++;
                    }
                    // Coordinate y
                    else if (coordinates == 1)
                    {
                        // Convert string to integer
                        y = (std::stod(coordinate));

                        // Update min-max box coordinates
                        if (y < ymin)
                            ymin = y;

                        if (y > ymax)
                            ymax = y;

                        coordinates++;
                    }
                }
            }

            // Store coordinates to point
            if (coordinates == 2)
            {
                QPointF p(x,y);
                polygon << p;
                coordinates = 0;
            }
            // Column index
            columnID++;
        }

        // Store object
        result.push_back(polygon);
    }

    // Close file
    file.close();

    return result;
}

