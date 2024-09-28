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

#ifndef __avmplus_DateObject__
#define __avmplus_DateObject__


namespace avmplus
{
	/**
	 * The DateObject class is the C++ implementation of instances
	 * of the Date class in the ECMA-262 Specification.
	 */
	class DateObject : public ScriptObject
	{
	public:
		Date date;

		/**
		 * This variant is only used for creating the prototype
		 */
		DateObject(DateClass *type, ScriptObject *objectPrototype)
			: ScriptObject(type->ivtable(), objectPrototype)
		{
			SAMPLE_FRAME("Date", core());
			AvmAssert(traits()->getSizeOfInstance() == sizeof(DateObject));
			date.setTime(MathUtils::kNaN);  // Date.prototype should be the "Invalid Date"
		}

		/**
		 * This variant is used for creating all dates other
		 * than Date.prototype
		 */
		DateObject(DateClass *type, const Date& date)
			: ScriptObject(type->ivtable(), type->prototype)
		{
			AvmAssert(traits()->getSizeOfInstance() == sizeof(DateObject));
			this->date = date;
		}
		
		// renamed to avoid hiding ScriptObject::toString
		Stringp _toString(int index);
		double AS3_valueOf();
		double _setTime(double value);
		double _get(int index);
		double _set(int index, Atom* argv, int argc);

		double AS3_getUTCFullYear() { return _get(Date::kUTCFullYear); }
		double AS3_getUTCMonth() { return _get(Date::kUTCMonth); }
		double AS3_getUTCDate() { return _get(Date::kUTCDate); }
		double AS3_getUTCDay() { return _get(Date::kUTCDay); }
		double AS3_getUTCHours() { return _get(Date::kUTCHours); }
		double AS3_getUTCMinutes() { return _get(Date::kUTCMinutes); }
		double AS3_getUTCSeconds() { return _get(Date::kUTCSeconds); }
		double AS3_getUTCMilliseconds() { return _get(Date::kUTCMilliseconds); }
		double AS3_getFullYear() { return _get(Date::kFullYear); }
		double AS3_getMonth() { return _get(Date::kMonth); }
		double AS3_getDate() { return _get(Date::kDate); }
		double AS3_getDay() { return _get(Date::kDay); }
		double AS3_getHours() { return _get(Date::kHours); }
		double AS3_getMinutes() { return _get(Date::kMinutes); }
		double AS3_getSeconds() { return _get(Date::kSeconds); }
		double AS3_getMilliseconds() { return _get(Date::kMilliseconds); }
		double AS3_getTimezoneOffset() { return _get(Date::kTimezoneOffset); }
		double AS3_getTime() { return _get(Date::kTime); }

		double _setUTCFullYear(Atom* argv, int argc) { return _set(-1, argv, argc); }
		double _setUTCMonth(Atom* argv, int argc) { return _set(-2, argv, argc); }
		double _setUTCDate(Atom* argv, int argc) { return _set(-3, argv, argc); }
		double _setUTCHours(Atom* argv, int argc) { return _set(-4, argv, argc); }
		double _setUTCMinutes(Atom* argv, int argc) { return _set(-5, argv, argc); }
		double _setUTCSeconds(Atom* argv, int argc) { return _set(-6, argv, argc); }
		double _setUTCMilliseconds(Atom* argv, int argc) { return _set(-7, argv, argc); }

		double _setFullYear(Atom* argv, int argc) { return _set(1, argv, argc); }
		double _setMonth(Atom* argv, int argc) { return _set(2, argv, argc); }
		double _setDate(Atom* argv, int argc) { return _set(3, argv, argc); }
		double _setHours(Atom* argv, int argc) { return _set(4, argv, argc); }
		double _setMinutes(Atom* argv, int argc) { return _set(5, argv, argc); }
		double _setSeconds(Atom* argv, int argc) { return _set(6, argv, argc); }
		double _setMilliseconds(Atom* argv, int argc) { return _set(7, argv, argc); }

#ifdef AVMPLUS_VERBOSE
	public:
		Stringp format(AvmCore* core) const;
#endif
		DECLARE_SLOTS_DateObject;
	};
}

#endif /* __avmplus_DateObject__ */
