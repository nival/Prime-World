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

#ifndef __Platform__
#define __Platform__

#include "VMPI.h"

namespace avmshell 
{
	/**
	* function pointer for the timer callback function
	* @see setTimer()
	*/
	typedef void (*AvmTimerCallback)(void*);

	class File;

	/**
	* Abstract base class representing the platform on which avm is ported to.
	* The class defines APIs that need to be implemented by the platform
	*/
	class Platform
	{
	public:
		/**
		* Method to get access to the platform defined and created singleton
		* Required by the shell to call platform-specific implementations
		* @return Pointer to singleton instance of the platform defined implementation of this base class
		*/
		static Platform* GetInstance();
		
		/**
		* Virtual Destructor
		*/
		virtual ~Platform() {}

		/**
		* Method to terminate the shell application
		* A call to this method should never return
		* @param code  a numeric value indicating the result of program execution or an error code
		* @return none
		*/
		virtual void exit(int code) = 0;

		/**
		* Method to create a file handle to execute file I/O
		* The implementation should create a platform specific file instance
		* @return a handle to platform-specific file instance, NULL if an error occurred
		*/
		virtual File* createFile() = 0;

		/**
		* Method to destroy the file handle created via createFile
		* After this function is called the corresponding file handle becomes invalid
		* @param file file handle to be destroyed
		* @return none
		* @see createFile()
		*/
		virtual void destroyFile(File* file) = 0;

		/**
		* Method for setting up logging functionality
		* A platform can implement this method to open a file for logging messages
		* @param filename - name of the log file.  File name is UTF-8 encoded
		* @return none
		*/
		virtual void initializeLogging(const char* filename) = 0;

		/**
		* Method to write debug/log messages in a platform-defined way
		* The message is UTF-8 encoded
		* @param message - message to output
		* @return  number of bytes actually written
		* @see initializeLogging()
		*/
		virtual int logMessage(const char* message) = 0;

		/**
		* Method to receive a NULL-terminated string of user data via console or other source 
		* This method is useful while running shell in interactive mode and for debugging purposes
		* Currently the expected encoding of the data is Latin-1
		* @param buffer buffer for storing the input data
		* @param bufferSize size of the buffer being passed indicating the max number of bytes it can accept
		* @return pointer to the beginning of input data
		*/
		virtual char* getUserInput(char* buffer, int bufferSize) = 0;

		/**
		* Method to retrieve the lowest address (the limit) of the program stack pointer
		* for the main program thread.  This function makes /no sense/ on any other thread.
		* The limit returned has been adjusted so that some amount of space is available
		* at addresses below the limit, for use by native code.
		*
		* The amount of space made available for native code will typically depend on the
		* platform class (64-bit, 32-bit, embedded), and is heuristic - we have no true
		* estimation at this time (now == Apr-2009) for how much space native code might need.
		*
		* The returned value is used by the VM execution engines to check heuristically
		* (and conservatively) for stack overflow.
		*
		* @return address indicating the lower limit of the current program's execution stack,
		*         less a safety margin.
		*/
		virtual uintptr_t getMainThreadStackLimit() = 0;

		/**
		* Method to set a platform-specific timer for a callback after specific interval of time
		* This method should implement a one-shot timer
		* @param seconds number of seconds indicating the timer expiration
		* @param callback function that will be invoked when the timer fires
		* @param callbackData context data that will be passed as an argument during "callback" invocation
		* @return none
		*/
		virtual void setTimer(int seconds, AvmTimerCallback callback, void* callbackData) = 0;
	};
}

#endif /* __Platform__ */
