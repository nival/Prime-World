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

#include "PosixFile.h"

namespace avmshell
{
	PosixFile::~PosixFile()
	{
		if(file)
		{
			fclose(file);
		}
	}

	bool PosixFile::open(const char* filename, File::OpenAttribute flags)
	{
		const char* fileAttributes[] = { "r", "w", "a", "rb", "wb", "ab" };

		file = fopen(filename, fileAttributes[flags] );

		return file != 0;
	}

	void PosixFile::close()
	{
		fclose(file);
		file = 0;
	}

	size_t PosixFile::read(void* buffer, size_t bytesToRead)
	{
		return fread(buffer, 1, bytesToRead, file);
	}

	size_t PosixFile::write(const void* buffer, size_t bytesToWrite)
	{
		return fwrite(buffer, 1, bytesToWrite, file);
	}

	int64_t PosixFile::getPosition() const
	{
		return ftell(file);
	}

	bool PosixFile::setPosition(int64_t pos)
	{
		return fseek(file, pos, SEEK_SET) == 0;
	}

	int64_t PosixFile::size() const 
	{
		fseek(file, 0L, SEEK_END);
		int64_t pos = ftell(file);
		fseek (file, 0L, SEEK_SET);
	
		return pos;
	}
	
	bool PosixFile::isEOF() const
	{
		return feof(file) != 0;
	}
	
}
