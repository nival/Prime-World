/* ***** BEGIN LICENSE BLOCK *****
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are subject to the Mozilla Public License Version
* 1.1 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* The Original Code is [Open Source Virtual Machine.].
*
* The Initial Developer of the Original Code is
* Adobe System Incorporated.
* Portions created by the Initial Developer are Copyright (C) 2004-2006
* the Initial Developer. All Rights Reserved.
*
* Contributor(s):
*   Adobe AS3 Team
*
* Alternatively, the contents of this file may be used under the terms of
* either the GNU General Public License Version 2 or later (the "GPL"), or
* the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
* in which case the provisions of the GPL or the LGPL are applicable instead
* of those above. If you wish to allow use of your version of this file only
* under the terms of either the GPL or the LGPL, and not to allow others to
* use your version of this file under the terms of the MPL, indicate your
* decision by deleting the provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */

#ifndef __avmshell_File__
#define __avmshell_File__

#include "avmshell.h"

namespace avmshell
{
	/**
	* Abstract base class for performing platform-specific file operations
	* This class needs to be derived and its methods implemented by platform to enable the shell to perform file I/O
	*/
	class File
	{
	public:
		/**
		*  An enum defining the open modes for a file
		*/
		typedef enum 
		{
			OPEN_READ = 0,
			OPEN_WRITE,
			OPEN_APPEND,
			OPEN_READ_BINARY,
			OPEN_WRITE_BINARY,
			OPEN_APPEND_BINARY
		}OpenAttribute;

		/**
		* Virtual Destructor
		*/
		virtual ~File() {}

		/**
		* Method to open a file on platform's file system
		* The implementation should open the file with the given name and attributes for open mode
		* @param filename represents the path and name of the file to be opened.  filename is UTF-8
		* @param flags one of the values from OpenAttribute enumeration indicating the  mode of file
		* @return true if file was opened successfully, false otherwise
		* @see enum OpenAttribute
		*/
		virtual bool open(const char* filename, OpenAttribute flags) = 0;

		/**
		* Method to close an opened file.
		* If the file was not opened this method should do nothing
		* @return none
		*/
		virtual void close() = 0;

		/**
		* Method to read a chunk of data from the file
		* This method can return 0 in event of a read error or if the file marker was at end-of-file.
		* So a return value of zero should not be treated as an error condition by default.
		* Instead method isEOF() should be used to detect a end-of-file .
		* @param buffer buffer to read the data into
		* @param bytesToRead number of bytes to read
		* @return number of bytes actually read.  0 or less than bytesToRead in case of error or end-of-file was reached
		*/
		virtual size_t read(void* buffer, size_t bytesToRead) = 0;

		/**
		* Method to write a chunk of data to the file
		* @param buffer buffer containing the data to write to file
		* @param bytesToWrite number of bytes to write from the buffer
		* @return number of bytes actually written.  If this value is less than bytesToWrite then that indicates an error
		*/
		virtual size_t write(const void* buffer, size_t bytesToWrite) = 0;

		/**
		* Method to get the current position of the file head
		* @return returns the current byte position of the file head, -1 if an error occurred
		*/
		virtual int64_t getPosition() const = 0;

		/**
		* Method to move the file head to a certain position
		* @param pos number indicating the byte position in file to move the file head to
		* @return returns true if the operation was successful, false if an error occurred
		*/
		virtual bool setPosition(int64_t pos) = 0;

		/**
		* Method to get the size of file
		* @return size of the file, -1 if an error occurred
		*/
		virtual int64_t size() const = 0;

		/**
		* Method to check if the end-of-file has reached
		* @return true if end if reached, false otherwise
		*/
		virtual bool isEOF() const = 0;
	};
}

#endif /* __avmshell_File__ */
