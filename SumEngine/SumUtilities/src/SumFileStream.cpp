//*************************************************************************************************
// Title: SumFileStream.cpp
// Author: Gael Huber
// Description: Wrapper for a basic data stream. Specific stream types (such as string streams) may
//	inherit from this class.
//*************************************************************************************************
#include "SumFileStream.h"

namespace SumEngine
{
	//*************************************************************************************************
	// Default constructor
	//*************************************************************************************************
	FileStream::FileStream()
		:	_filePath("")
	{
	}

	//*************************************************************************************************
	// Constructor
	// @param
	//	filePath The file path of the stream to open
	//*************************************************************************************************
	FileStream::FileStream(const String& filePath)
		:	_filePath(filePath)
	{
		open();
	}

	//*************************************************************************************************
	// Destructor
	//*************************************************************************************************
	FileStream::~FileStream()
	{
		// Make sure the stream is closed
		close();
	}

	//*************************************************************************************************
	// Close the stream
	//*************************************************************************************************
	void FileStream::close()
	{
		if(_stream.is_open() == true)
		{
			_stream.close();
		}
	}

	//*************************************************************************************************
	// Is the stream open?
	// @return
	//	SBOOL True if open, false otherwise
	//*************************************************************************************************
	SBOOL FileStream::isOpen() const
	{
		return _stream.is_open();
	}

	//*************************************************************************************************
	// Is the stream at the end of the file?
	// @return
	//	SBOOL True if the stream is at the end of the file, false otherwise
	//*************************************************************************************************
	SBOOL FileStream::isEOF() const
	{
		return _stream.eof();
	}

	//*************************************************************************************************
	// Seek a position within the file
	//*************************************************************************************************
	void FileStream::seek(SUINT pos)
	{
		// If the seek position is not past the length of the file
		if(isOpen())
		{
			_stream.seekg(pos);
		}
	}

	//*************************************************************************************************
	// Read from the file
	// @param
	//	data A pointer to the data
	// @param
	//	bytes The number of bytes to read
	//*************************************************************************************************
	void FileStream::read(String& data, SUINT bytes)
	{
		if(isOpen() == true)
		{
			_stream.read(data.c_str(), bytes);
			data.calcLength();
		}
	}

	//*************************************************************************************************
	// Read a line from the file
	// @param
	//	data The array to store the data
	// @param
	//	bytes The max number of bytes to store in the data array
	//*************************************************************************************************
	void FileStream::readLine(String& data, SUINT bytes)
	{
		if(isOpen() == true)
		{
			_stream.getline(data.c_str(), bytes);
			data.calcLength();
		}
	}

	//*************************************************************************************************
	// Determine the length of the stream
	// @return
	//	SUINT The size of the stream
	//*************************************************************************************************
	SLONGLONG FileStream::getLength()
	{
		// Get the current position
		SLONGLONG start = _stream.tellg();

		// Seek to the end
		_stream.seekg(0, std::ios::end);

		// Get the new position
		SLONGLONG end = _stream.tellg();

		// Calculate the length
		return end - start;
	}

	//*************************************************************************************************
	// Open the specified file path
	//*************************************************************************************************
	void FileStream::open()
	{
		_stream.open(_filePath);
	}

}	// Namespace