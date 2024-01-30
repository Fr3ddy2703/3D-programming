#pragma once
#include "iostream"
#include <vector>
#include <cmath>
#include <fstream>
#include <limits>
#include <iomanip>
#include <glm/glm.hpp>

struct Vertex
{
   float x, y, z;
	glm::vec3 color;
};

struct Calculations
{

	double f(double x)
	{
		return x * x;
	}
	double df(double x, double y)
	{
		return x * x * x * x * y * y;
	}

	double a = 0.f;
	double b = 5.f;
	int iterative = 10;

	double h = (b - a) / iterative;

	double derivative (double x)
	{
		double h = 0.00001;
		return (f(x + h) - f(x)) / h;
	}


	 
	std::vector<Vertex>PointsInGraph(float startpoint, float endpoint, float increment)
	{
		std::ofstream out;
		std::string filename("Task1.txt");
		out.open(filename);
		out << std::fixed << std::setprecision(3);
		out << "Amount of points printed: "<< 3600 << std::endl;
		const char* comma = ", ";
		std::vector<Vertex> VertexPoint;
		for (float i = startpoint; i < endpoint; i += increment)
		{
			Vertex temp;
			temp.x = i;
			temp.y = i * i ;
			temp.z = 0.f;
			double yderivative = derivative(temp.x);
			if(yderivative > 0)
			{
				temp.color = glm::vec3(0.f, 1.f, 0.f);
			}
			else
			{
				temp.color = glm::vec3(1.f, 0.f, 0.f);
			}
			VertexPoint.push_back(temp);
			std::string color = yderivative > 0 ? "green" : "red";
			out << temp.x << comma << temp.y << comma << temp.z << " " << color << "\n";

		}
		out.close();
		std::cout << "The file " << filename << " has been made.";
		return VertexPoint;

	}

	std::vector<Vertex>Spiral(float distance)
	{
		std::ofstream out;
		std::string filename("Task2.txt");
		out.open(filename);
		out << std::fixed << std::setprecision(3);
		out << "Amount of points printed: "<< 3600 << std::endl;
		const char* comma = ", ";
		std::vector<Vertex> Spiralpoints;
		for (float i = 0.5f; i <= (360); i += distance)
		{
			Vertex temp;
			temp.x = glm::cos(i / 3.14) * 0.1f;
			temp.y = i * 0.01f;
			temp.z = glm::sin(i / 3.14) * 0.1f;
			
			double yderivative = derivative(temp.z);
			if(yderivative > 0)
			{
				temp.color = glm::vec3(0.f, 1.f, 0.f);
			}
			else
			{
				temp.color = glm::vec3(1.f, 0.f, 0.f);
			}
			std::string color = yderivative > 0 ? "green" : "red";
			out << temp.x << comma << temp.y << comma << temp.z << " " << color << "\n";
			Spiralpoints.push_back(temp);

		}
		out.close();
		std::cout << "The file " << filename << " has been made.";
		return Spiralpoints;
	}

	void CreatePlane()
	{
		std::ofstream file("Task3.txt");

		int iterator = 10;

		for (float i = 0; i <= iterator; i++)
		{
			for (float g = 0; g < iterator; g++)
			{
				int x = i;
				int y = g;

				df(i, g);

				file << x << " " << y << " " << df(i , g) << "\n";
			}
		}

		file.close();
	}
};
