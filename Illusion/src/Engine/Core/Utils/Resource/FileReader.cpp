/*****************************************************************//**
 * \file   FileReader.cpp
 * \brief  The FileReader class, contains some static helper
 * functions
 * 
 * \author Mian Li
 * \date   January 2024
 *********************************************************************/

#include "pch.h"
#include "FileReader.h"

#include <fstream>


 //--------------------namespace: Illusion starts--------------------
namespace Illusion
{

	// Read the file from the path
	std::string FileReader::ReadFileBin(const std::string filepath)
	{
		std::string result;

		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			ENGINE_CORE_ERROR("Could not open file: {0}", filepath);
		}

		return result;
	}



	//--------------------namespace: Illusion ends--------------------
}