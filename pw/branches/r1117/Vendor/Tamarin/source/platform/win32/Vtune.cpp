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
*   Adobe AS3 Team. Modified by Shengnan Cong@Intel.
*   Tamarin. Refactored by Rick Reitmaier
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
#include "avmplus.h"

#ifdef VTUNE
#include "CodegenLIR.h"

namespace avmplus
{
	void wtoc(char* Dest, const char* Source, int append)
	{
		int i = 0;
		if (Source) {
			if (append) {
				int j = -1;
				while(Source[i] != '\0')
				{
					Dest[i] = Source[i];
					if (Dest[i] == ':') {
						//Dest[i] = '|';
						j = i;
					} else if (Dest[i] == '.') {
						//Dest[i] = '-';
						j = i;
					} else if (Dest[i] == '$') {
						j = i;
					}
					++i;
				}

				// extract just the method name
				if (j >= 0) {
					i = 0;
					while(Source[++j] != '\0')
					{
						Dest[i++] = Source[j];
					}
				}

				Dest[i++] = '(';
				Dest[i++] = ')';
			} else {
				while(Source[i] != '\0')
				{
					Dest[i] = Source[i];
					++i;
				}
			}
		}
		Dest[i] = '\0';
	}

	void CallBack(AvmCore* core, void *UserData, iJIT_ModeFlags Flags)
	{
		// This is all busy work to prevent the resulting warnings
		// from causing an error.  I don't want to change the build
		// settings.
		AvmCore* dummy_core;
		void* dummy_user;
		iJIT_ModeFlags dummy_flags;

		dummy_core = core;
		dummy_user = UserData;
		dummy_flags = Flags;
	}

	void DumpVTuneMethodInfo(AvmCore* core, iJIT_Method_Load* ML)
	{
		core->console << "method_id = " << ML->method_id << "\n";
		core->console << "method_name = '" << ML->method_name << "'\n";
		core->console << "method_load_address = " << (int) ML->method_load_address << "\n";
		core->console << "method_size = " << ML->method_size << "\n";
		core->console << "line_number_size = " << ML->line_number_size << "\n";
		core->console << "line_number_table = " << (int) ML->line_number_table << "\n";
            
		if (ML->line_number_table) 
		{
			core->console << "\tline\toffset\n";
			LineNumberInfo* lines = ML->line_number_table; 
			for (int j = 0; j < (int) ML->line_number_size; j++) 
			{
				core->console 
					<< "\t" 
					<< lines[j].LineNumber 
					<< "\t" 
					<< lines[j].Offset 
					<< "\n";
			}
		}
		
		core->console << "class_id = " << ML->class_id << "\n";
		core->console << "class_file_name = '" << ML->class_file_name << "'\n";
		core->console << "source_file_name = '" << ML->source_file_name << "'\n";
		core->console << "user_data = " << (int) ML->user_data << "\n";
		core->console << "user_data_size = " << ML->user_data_size << "\n";
		core->console << "env = " << ML->env << "\n\n";
	}

   char* string2char(AvmCore* core, Stringp str)
   {
       if (!str->length()) return 0;
       StringNullTerminatedUTF8 s(core->gc, str);
       const char* cstr = s.c_str();
       size_t max = VMPI_strlen(cstr);
       char* to = (char*)malloc((max+1)*sizeof(char));
       VMPI_strncpy(to,cstr,max);
       to[max]='\0';
       return to;
   }

   /** 
     * parse a given MethodInfo.format() 'ed name and provide
     * the starting and ending indcies of each 
    * @param String* - formatted method name
    * @param int[4]  - array that will be filled with class/method 
    *                  indicies into    
    * @return true, if a class name exists
    */
   bool locateNames(AvmCore* core, Stringp name, int* idx)
   {
       bool hasClass = true;
       VMPI_memset(idx,0,sizeof(*idx));
       if (!name) return false;

       // class
       // idx[0] = 0;
       if ( (idx[1]=name->indexOf(core->newString("."))) >= 0 )
           hasClass = false;  // match means no class name 
       else if ( (idx[1]=name->indexOf(core->newString("$"))) >=0 )
           idx[1]; // match
       else if ( (idx[1]=name->indexOf(core->newString("/"))) >= 0 )
           idx[1]; // match
       else
           hasClass = false;  // nothing looks like a class here

       // method
       if ( (idx[2]=name->lastIndexOf(core->newString("/"))) >= 0 )
           idx[2]++;  // match
       else if ( (idx[2]=name->lastIndexOf(core->kcolon)) >= 0 )
           idx[2]++;  // match
       else
           ;  // idx[2] = 0; 
       idx[3] = name->length()-2; // get rid of paren
               
       return hasClass;
   }
	
   void VTune_RegisterMethod(AvmCore* core, JITCodeInfo* inf) 
   {       
		// assume no method inlining so start/end of JIT code gen = method start/end
       uintptr startAt = inf->startAddr;
       uintptr endAt = inf->endAddr;
		uint32 methodSize = endAt - startAt;

       Stringp name = inf->method->format(core);
       int idx[4];
       bool hasClass = locateNames(core, name, idx);

		// register the method
		iJIT_Method_Load ML;
       Stringp mname = name->substring(idx[2],idx[3]);
		VMPI_memset(&ML, 0, sizeof(iJIT_Method_Load));
       ML.method_id = (inf->vtune) ? inf->vtune->method_id : iJIT_GetNewMethodID();
       ML.method_name = string2char(core, mname);
		ML.method_load_address = (void *)startAt;	// virtual address of that method  - This determines the method range for the iJVM_EVENT_TYPE_ENTER/LEAVE_METHOD_ADDR events
		ML.method_size = methodSize;	// Size in memory - Must be exact

		// md position / line number table
       SortedMap<int,LineNumberRecord*,LIST_GCObjects>* tbl = &inf->lineNumTable;
		int size = tbl->size();
		LineNumberInfo* lines = 0;
		if (size)
		{
			int bsz = size*sizeof(LineNumberInfo);
			lines = (LineNumberInfo*) malloc(bsz);
			VMPI_memset(lines, 0, bsz);
		}

       String* fileName = 0;
       int at = 0;
       for(int i=0; i<size; i++) 
		{
			sintptr mdPos = tbl->keyAt(i);
			LineNumberRecord* entry = tbl->at(i);
           if (entry->filename && entry->lineno)
           {
               if (!fileName) fileName = entry->filename;

               // @todo file name should be part of the lines[] record, no?
               lines[at].LineNumber = entry->lineno;
               lines[at].Offset = mdPos - startAt;
               at++;
           }
       }

       // @todo hack for vtune since it can't process multiple records with the same method name 
       if (inf->sid>0 && at>0) {
           mname = core->concatStrings(mname,core->newString("_L"));
           mname = core->concatStrings(mname,core->intToString(lines[0].LineNumber));
           mname = core->concatStrings(mname,core->newString("_"));
           mname = core->concatStrings(mname,core->intToString(inf->sid));
           if (ML.method_name) free(ML.method_name);
           ML.method_name = string2char(core,mname);
       }

       ML.line_number_table = lines;   // Pointer to the begining of the line numbers info array
       ML.line_number_size = at;       // Line Table size in number of entries - Zero if none

       UTF8String* utf = ( fileName ) ? fileName->toUTF8String() : core->kEmptyString->toUTF8String();
		
		ML.class_id = 0;                // uniq class ID
       ML.class_file_name = (hasClass) ? string2char(core,name->substring(idx[0],idx[1])) : 0;     // class file name 
		ML.source_file_name = (char *)(malloc((utf->length()+3)*sizeof(char)));   // +1 for \0 and +2 for wtoc's ()
		wtoc(ML.source_file_name, utf->c_str(), 0);	// source file name 

		ML.user_data = NULL;            // bits supplied by the user for saving in the JIT file...
		ML.user_data_size = 0;          // the size of the user data buffer
		ML.env = iJDE_JittingAPI;

		// DumpVTuneMethodInfo(core, &ML); // Uncommented to debug VTune
		iJIT_NotifyEvent(iJVM_EVENT_TYPE_METHOD_LOAD_FINISHED, &ML);

       if (inf->vtune && core->VTuneStatus == iJIT_CALLGRAPH_ON) 
		{
			MMgc::GCHeap* heap = core->GetGC()->GetGCHeap();
           heap->SetPageProtection(inf->vtune, sizeof (iJIT_Method_NIDS), false, true);   
       }

		// free everything we alloc'd  ( @todo did vtune really copy all the strings?!? )
		if (ML.line_number_table) free(ML.line_number_table);
       if (ML.class_file_name && hasClass) free(ML.class_file_name);
		if (ML.method_name) free(ML.method_name);
		if (ML.source_file_name) free(ML.source_file_name);
	}	
}

#endif /* VTUNE */
