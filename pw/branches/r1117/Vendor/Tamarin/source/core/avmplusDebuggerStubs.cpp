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
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
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


#include "avmplus.h"

#ifdef DEBUGGER

namespace avmplus
{
    using namespace MMgc;
    
    Debugger::Debugger(avmplus::AvmCore*, TraceLevel)
    {
    }

    Debugger::~Debugger()
    {
    }
    
    void Debugger::stepInto()
    {
    }

    void Debugger::stepOver()
    {
    }

    void Debugger::stepOut()
    {
    }

    void Debugger::stepContinue()
    {
    }

    bool Debugger::breakpointSet(SourceInfo* source, int linenum)
    {
        return false;
    }

    bool Debugger::breakpointClear(SourceInfo* source, int linenum)
    {
        return false;
    }

    void Debugger::debugLine(int linenum)
    {
    }

    void Debugger::debugFile(Stringp filename)
    {
    }

    void Debugger::debugMethod(MethodEnv* /*env*/)
    {
    }

    void Debugger::_debugMethod(MethodEnv* env)
    {
    }

    void Debugger::disableAllTracing()
    {
    }
    
    void Debugger::traceMethod(MethodInfo* fnc, bool ignoreArgs)
    {
    }

    void Debugger::traceLine(int line)
    {
    }

    void Debugger::processAbc(PoolObject* pool, ScriptBuffer code)
    {
    }

    int Debugger::frameCount()
    {
        return 0;
    }

    DebugFrame* Debugger::frameAt(int frameNbr)
    {
        return NULL;
    }

    int Debugger::abcCount() const
    {
        return 0;
    }

    AbcInfo* Debugger::abcAt(int index) const
    {
        return NULL;
    }

    AbcFile::AbcFile(AvmCore* core, int size)
    {
    }

    int AbcFile::sourceCount() const
    {
        return 0; 
    }

    SourceInfo* AbcFile::sourceAt(int index) const
    {
        return NULL;
    }

    int AbcFile::size() const 
    { 
        return 0; 
    }

    SourceFile* AbcFile::sourceNamed(Stringp name)
    {
        return NULL;
    }

    void AbcFile::sourceAdd(SourceFile* s)
    {
    }

    SourceFile::SourceFile(MMgc::GC* gc, Stringp name)
    {
    }

    Stringp SourceFile::name() const 
    { 
        return NULL; 
    }

    void SourceFile::addLine(int linenum, MethodInfo* func, int offset)
    {
    }

    int SourceFile::functionCount() const 
    { 
        return 0;
    }

    MethodInfo* SourceFile::functionAt(int index) const 
    {
        return NULL; 
    }

    bool SourceFile::setBreakpoint(int linenum)
    {
        return false;
    }

    bool SourceFile::clearBreakpoint(int linenum)
    {
        return false;
    }

    bool SourceFile::hasBreakpoint(int linenum)
    {
        return false;
    }

    DebugStackFrame::DebugStackFrame(int nbr, CallStackNode* tr, Debugger* debug)
    {
    }

    bool DebugStackFrame::sourceLocation(SourceInfo*& source, int& linenum)
    {
        return false;
    }

    bool DebugStackFrame::dhis(Atom& a)
    {
        return false;
    }

    bool DebugStackFrame::arguments(Atom*& ar, int& count)
    {
        return false;
    }

    bool DebugStackFrame::setArgument(int which, Atom& val)
    {
        return false;
    }

    bool DebugStackFrame::locals(Atom*& ar, int& count)
    {
        return false;
    }

    bool DebugStackFrame::setLocal(int which, Atom& val)
    {
        return false;
    }
}

#endif /* DEBUGGER */
