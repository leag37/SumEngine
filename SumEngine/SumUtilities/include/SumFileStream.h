//*************************************************************************************************
// Title: SumFileStream.h
// Author: Gael Huber
// Description: Wrapper for a basic data stream. Specific stream types (such as string streams) may
//	inherit from this class.
//*************************************************************************************************
#ifndef __SUMFILESTREAM_H__
#define __SUMFILESTREAM_H__

#include "SumInclude.h"
#include "SumString.h"
#include "SumSharedPtr.h"
#include <fstream>

namespace SumEngine
{
	/** \addtogroup Utilities
	*	@{
	*/
	/**	\addtogroup IO
	*	@{
	*/

	class FileStream
	{
	public:
		/** Default constructor
		*/
		FileStream();

		/** Constructor
		* @param
		*	filePath The file path of the stream to open
		*/
		FileStream(const String& filePath);

		/** Destructor
		*/
		virtual ~FileStream();

		/** Close the stream
		*/
		void close();

		/** Is the stream open?
		* @return
		*	SBOOL True if open, false otherwise
		*/
		SBOOL isOpen() const;

		/** Is the stream at the end of the file?
		* @return
		*	SBOOL True if the stream is at the end of the file, false otherwise
		*/
		SBOOL isEOF() const;

		/** Seek a position within the file
		* @param
		*	pos The position we want to seek to
		*/
		void seek(SUINT pos);

		/** Read from the file
		* @param
		*	data A pointer to the data
		* @param
		*	bytes The number of bytes to read
		*/
		void read(SCHAR* data, SUINT bytes);

		/** Read a line from the file
		* @param
		*	data The array to store the data
		* @param
		*	bytes The max number of bytes to store in the data array
		*/
		void readLine(SCHAR* data, SUINT bytes);

		/** Determine the length of the stream
		* @return
		*	SLONGLONG The size of the stream
		*/
		SLONGLONG getLength();

	protected:
		/** Open the specified file path
		*/
		void open();

	private:
		/** The file stream
		*/
		fstream _stream;

		/** The file path for the stream
		*/
		String _filePath;
	};

	/** Declare the class for a pointer specific to a data stream
	*/
	class FileStreamPtr : public SharedPtr<FileStream>
	{
	public:
		/** Constructor
		* @param
		*	stream The data stream
		*/
		FileStreamPtr(FileStream* stream);

		/** Destructor
		*/
		~FileStreamPtr();
	};

	/** @} */
	/** @} */

}	// Namespace

#endif // __SUMDATASTREAM_H__