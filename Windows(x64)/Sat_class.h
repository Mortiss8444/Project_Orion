#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "math_lib.h"

namespace Project_Orion
{
	class Satellite
	{
	public:
		struct vec2
		{
			float x, y;
		};
		struct vec3
		{
			float r, g, b;
		};
		/*----Satellite attributes-----*/
		std::string m_Stl_name;
		vec2 m_Pos = {0, 0};
		vec3 m_Color= {0, 0, 0};
		float m_Sides = 32.0f;
		vec2 m_actLatLong = {0, 0};
		/*----------------------------*/
		Satellite() {};
		Satellite(std::string inp_name, vec2 inp_xy, vec3 inp_rgb, vec2 inp_latLong) { m_Stl_name = inp_name; m_Pos = inp_xy; m_Color = inp_rgb; m_actLatLong = inp_latLong; };
		//Accessing to satellites name 
		const std::string getName() const { return m_Stl_name; };
		std::string addToArray(std::vector<Satellite>& vectorOfSats, std::string& name, vec2 xy, size_t index, vec2 ltlg);
		std::string deleteFromArray(std::vector<Satellite>& vectorOfSats, std::string& name);
		void displayVec(std::vector<Satellite>& vectorOfSats);
	};
	extern std::vector<Satellite::vec3> colors;
	extern std::vector<Satellite> satelliteStorage;
	extern std::atomic_bool displayInitWindow;
	extern std::atomic_bool terminateGL;
}