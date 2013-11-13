//*************************************************************************************************
// Title: SumFileSystem.cpp
// Author: Gael Huber
// Description: A wrapper for file systems and directory structure
//*************************************************************************************************
#include "SumFileSystem.h"

namespace SumEngine
{

	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	FileSystem::FileSystem()
	{ }

	//*************************************************************************************************
	// Constructor
	// @param
	//	name The name of the filesystem
	//*************************************************************************************************
	FileSystem::FileSystem(const String& name)
		:	_name(name)
	{ }

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	FileSystem::~FileSystem()
	{ }

	//*************************************************************************************************
	// Add a directory to the filesystem
	// @param
	//	dirPath The path to the directory
	//*************************************************************************************************
	void FileSystem::addDirectory(const String& dirPath)
	{
		// Add the directory path to the list of directories in the file system if we don't already have
		// it in the directory list
		SUINT index;
		if(_dirs.find(dirPath, index) == false)
		{
			_dirs.push_back(dirPath);
		}
	}

	//*************************************************************************************************
	// Find a file within the file system
	// @param 
	//	fileName The name of the file we want to find
	// @return
	//	FileInfo Struct representing file info
	//*************************************************************************************************
	FileInfo FileSystem::findFile(const String& fileName)
	{
		// The file info struct to return
		FileInfo fileInfo;
		
		// Iterate through the list of directories
		Array<String>::Iterator end = _dirs.end();
		for(Array<String>::Iterator itr = _dirs.begin(); itr != end; ++itr)
		{
			// Given the current element, get the full path based on the relative path
			SCHAR path[256];
			_fullpath(path, *itr, 256);

			// Try to locate the file
			String pattern = String(path);
			pattern.append("\\");
			pattern.append(fileName);
			intptr_t result = _findfirst(pattern, &fileInfo.fileData);

			// Free resources from _findfirst
			if(result != -1)
			{
				_findclose(result);

				// We found a match so exit loop
				fileInfo.fullPath = pattern;
				break;
			}
		}
		
		return fileInfo;
	}



}	// Namespace