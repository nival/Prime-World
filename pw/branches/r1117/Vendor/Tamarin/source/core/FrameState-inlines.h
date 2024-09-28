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

REALLY_INLINE Value& FrameState::value(int32_t i)
{
    AvmAssert(i >= 0 && i < verifier->frameSize);
    return locals[i];
}

REALLY_INLINE const Value& FrameState::value(int32_t i) const
{
    AvmAssert(i >= 0 && i < verifier->frameSize);
    return locals[i];
}

REALLY_INLINE Value& FrameState::scopeValue(int32_t i)
{
    AvmAssert(i >= 0 && i < scopeDepth);
    return value(verifier->scopeBase+i);
}

REALLY_INLINE const Value& FrameState::scopeValue(int32_t i) const
{
    AvmAssert(i >= 0 && i < scopeDepth);
    return value(verifier->scopeBase+i);
}

REALLY_INLINE Value& FrameState::stackValue(int32_t i)
{
    AvmAssert(i >= 0 && i < stackDepth);
    return value(verifier->stackBase+i);
}

REALLY_INLINE Value& FrameState::stackTop()
{
    return value(verifier->stackBase+stackDepth-1);
}

REALLY_INLINE int32_t FrameState::sp() const
{
    return verifier->stackBase+stackDepth-1;
}

REALLY_INLINE void FrameState::setType(int32_t i, Traits* t, bool notNull, bool isWith)
{
    Value& v = value(i);
    v.traits = t;
    v.notNull = notNull;
    v.isWith = isWith;
}

REALLY_INLINE void FrameState::pop(int32_t n)
{
    stackDepth -= n;
    AvmAssert(stackDepth >= 0);
}

REALLY_INLINE Value& FrameState::peek(int32_t n)
{
    return value(verifier->stackBase+stackDepth-n);
}

REALLY_INLINE void FrameState::pop_push(int32_t n, Traits* type, bool notNull)
{
    int32_t _sp = stackDepth - n;
    setType(verifier->stackBase+_sp, type, notNull);
    stackDepth = _sp+1;
}

REALLY_INLINE void FrameState::push(Value& _value)
{
    AvmAssert(verifier->stackBase+stackDepth+1 <= verifier->frameSize);
    setType(verifier->stackBase+stackDepth++, _value.traits, _value.notNull);
}

REALLY_INLINE void FrameState::push(Traits* traits, bool notNull)
{
    AvmAssert(verifier->stackBase+stackDepth+1 <= verifier->frameSize);
    setType(verifier->stackBase+stackDepth++, traits, notNull);
}

} // namespace avmplus
