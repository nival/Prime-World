/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
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
 * Portions created by the Initial Developer are Copyright (C) 2009
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

namespace avmplus
{

REALLY_INLINE int AbcParser::readU16(const byte* p) const
{
    if (p < abcStart || p+1 >= abcEnd)
        toplevel->throwVerifyError(kCorruptABCError);
    return p[0] | p[1]<<8;
}

REALLY_INLINE int AbcParser::readS32(const byte *&p) const
{
    // We have added kBufferPadding bytes to the end of the main swf buffer.
    // Why?  Here we can read from 1 to 5 bytes.  If we were to
    // put the required safety checks at each byte read, we would slow
    // parsing of the file down.  With this buffer, only one check at the
    // top of this function is necessary. (we will read on into our own memory)
    if ( p < abcStart || p >= abcEnd )
        toplevel->throwVerifyError(kCorruptABCError);

    int result = p[0];
    if (!(result & 0x00000080)) {
        p++;
        return result;
    }
    result = (result & 0x0000007f) | p[1]<<7;
    if (!(result & 0x00004000)) {
        p += 2;
        return result;
    }
    result = (result & 0x00003fff) | p[2]<<14;
    if (!(result & 0x00200000)) {
        p += 3;
        return result;
    }
    result = (result & 0x001fffff) | p[3]<<21;
    if (!(result & 0x10000000)) {
        p += 4;
        return result;
    }
    result = (result & 0x0fffffff) | p[4]<<28;
    p += 5;
    return result;
}

} // namespace avmplus
