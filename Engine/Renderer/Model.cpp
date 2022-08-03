#include "Model.h"
#include "../Core/File.h"

#include <iostream>
#include <sstream>

namespace jemgine
{
	Model::Model(const std::string filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}
	void Model::Draw(Renderer& renderer, const Vector2& position, float angle, float scale)
	{

		//draw model
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			jemgine::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
			jemgine::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}
	}
	void Model::Load(const std::string& filename)
	{
		std::string buffer;
		
		jemgine::ReadFile(filename, buffer);

		//read color
		std::istringstream stream(buffer);
		stream >> m_color;

		std::string line;
		std::getline(stream, line);

		//get number of points
		size_t numPoints = std::stoi(line);

		// read model points
		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}
	}
	float Model::CalculateRadius()
	{
		float radius = 0;

		//find the largest length (radius)
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}
}
