#include "csv.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <QDir>

CSV::CSV()
{

}

std::vector<QPolygonF> CSV::read_CSV(std::string &filename, double &x_min, double &x_max, double &y_min, double &y_max)
{
    // Reads CSV file and creates polygons from it

    // Create a vector to store the all loaded polygons
    std::vector<QPolygonF> result;

    // Variables, input filestream
    std::string line, column;
    std::ifstream file(filename);

    // Check if file is opened
    if(!file.is_open()) throw std::runtime_error("File not opened.");

    // Read column
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

        //In WKT format we need to remove first 12 symbols (Because every line starts with Multipolygon)
        line.erase(0,12);

        // Stringstream of the current line
        std::stringstream stringstream(line);

        // Current column ID
        int columnID = 0;

        // Variables
        int coords = 0;
        int x, y;
        std::string coordinate_pair, coordinate;
        QPolygonF polygon;

        //Go through every point in polygon
        while(std::getline(stringstream, coordinate_pair, ','))
        {
            std::stringstream ss2(coordinate_pair);

            //Go through every coordinate in point
            while(std::getline(ss2, coordinate, ' '))
            {
                if (coordinate == "")
                    continue;

                //If coordinate pair incomplete (must include both x and y)
                if (coords < 2)
                {
                    //If there is x coor to read
                    if (coords == 0)
                    {
                        //Convert string to integer
                        x = (std::stod(coordinate));

                        //Update MMB coordinates
                        if (x < x_min)
                            x_min = x;

                        if (x > x_max)
                            x_max = x;

                        coords++;
                    }
                    //If there is y coor to read
                    else if (coords == 1)
                    {
                        //Convert string to integer
                        y = (std::stod(coordinate));

                        //Update MMB coordinates
                        if (y < y_min)
                            y_min = y;

                        if (y > y_max)
                            y_max = y;

                        coords++;
                    }
                }
            }

            // Store coordinates to point
            if (coords == 2)
            {
                QPointF p(x,y);
                polygon << p;
                coords = 0;
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

