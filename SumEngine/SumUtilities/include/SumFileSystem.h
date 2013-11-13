//*************************************************************************************************
// Title: SumFileSystem.h
// Author: Gael Huber
// Description: A wrapper for file systems and directory structure
//*************************************************************************************************
#ifndef __SUMFILESYSTEM_H__
#define __SUMFILESYSTEM_H__

#include "SumInclude.h"
#include "SumArray.h"
#include "SumString.h"
#include <io.h>

namespace SumEngine
{
	/** \addtogroup Utilities
	*	@{
	*/

	// Struct to wrap _finddata_t as FileInfo for easier reference and include a few other variable types
	struct FileInfo
	{
		_finddata_t fileData;
		String fullPath;
	};

	class FileSystem
	{
	public:
		/** Default constructor
		*/
		FileSystem();

		/** Constructor
		* @param
		*	name The name of the filesystem
		*/
		FileSystem(const String& name);

		/** Destructor
		*/
		~FileSystem();

		/** Add a directory to the filesystem
		* @param
		*	dirPath The path to the directory
		*/
		void addDirectory(const String& dirPath);

		/** Find a file within the file system
		* @param 
		*	fileName The name of the file we want to find
		* @return
		*	FileInfo Struct representing file info
		*/
		FileInfo findFile(const String& fileName);


	private:
		/** The name of the file system
		*/
		String _name;

		/** Array of directory locations to use when searching for a file
		*/
		Array<String> _dirs;
	};

	/** @} */

}	// Namespace

#endif	// __SUMFILESYSTEM_H__