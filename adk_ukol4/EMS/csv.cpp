#include "csv.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <QDir>

std::vector<std::vector<std::string>> CSV::readCSV(std::string &filename)
{
    // Load CSV file into a vector of string vectors
    std::vector<std::string> lines;
    std::vector<std::vector<std::string>> result;

    // Supplementary variables
    std::string csv_line, csv_colnames;

    // Create input filestream
    std::ifstream myFile(filename);

    // Check if file is opened
    if(!myFile.is_open()) throw std::runtime_error("File not opened.");

    // Read file line by line
    while(std::getline(myFile, csv_line))
    {
        // Create stringstream of current line
        std::stringstream ss(csv_line);
        std::string field;

        // Go through every field in line
        while(std::getline(ss, field, ',')) lines.push_back(field);

        result.push_back(lines);
        lines.clear();
    }

    // Close file
    myFile.close();

    return result;
}

std::vector<QPointF> CSV::getPoints(std::vector<std::vector<std::string>> &csv_content, double &x_min, double &x_max, double &y_min, double &y_max)
{
    // Create vector of points from vector of lines (from CSV file)
    std::vector<QPointF> points;
    double x, y;

    // Go through every line
    for(std::vector<std::string> line:  csv_content)
    {
        // Convert string to double
        x  = -std::stod(line[0]);
        y  = std::stod(line[1]);

        // Update min-max box
        if(x < x_min) x_min = x;

        if(x > x_max) x_max = x;

        if(y < y_min) y_min = y;

        if(y > y_max) y_max = y;

        points.push_back(QPointF(x,y));
    }

    return points;
}
