#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> // std::stringstream
#include <QDir>
#include "csv.h"

csv::csv()
{
}

std::vector<QPolygon> csv::readCsv(std::string &filename)
{
    // Reads csv file and creates polygons from it

    // Creates a vector to store the result
    std::vector<QPolygon> result;

    // Variables, input filestream
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

    // Read csv file
    while(std::getline(file, line))
    {
        // Edit linestring
        line.erase(remove(line.begin(), line.end(), '"'), line.end());

        // Stringstream from current line
        std::stringstream stringstream(line);

        // Current column ID
        int columnID = 0;

        // Variables
        int coords = 0;
        int x, y;
        std::string value;
        QPolygon polygon;

        // Process all objects in line
        while(std::getline(stringstream, value, ','))
        {
            if (columnID > 1)
            {
                if (value != "")
                {
                    // Coordinates must have x and y
                    if (coords != 2)
                    {
                        if (coords%2 == 0)
                        {
                            x = std::stoi(value);
                            coords++;
                        }
                        else
                        {
                            // Convert string to integer
                            y = std::stoi(value);
                            coords++;
                        }
                    }

                    // Store coordinates to point
                    if (coords == 2)
                    {
                        QPoint p(x,y);
                        polygon << p;
                        coords = 0;
                    }
                }
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
