#include "csv.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <QDir>

CSV::CSV()
{
}

std::vector<QPointF> CSV::readCSV(std::string &filename, double &xmin, double &xmax, double &ymin, double &ymax)
{
    // Read CSV file and create polygons from it
    // Vector for storing result
    std::vector<QPointF> result;

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
        // Stringstream of the current line
        std::stringstream stringstream(line);

        // Current column ID
        int columnID = 0;

        // Supplementary variables
        int coordinates = 0;
        int x, y;
        std::string coordinate_pair, coordinate;

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
                result.push_back(p);
                coordinates = 0;
            }
            // Column index
            columnID++;
        }
    }

    // Close file
    file.close();

    return result;
}


