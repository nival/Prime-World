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

#ifndef __avmplus_MathClass__
#define __avmplus_MathClass__


namespace avmplus
{
	/**
	 * class Math
	 */
	class MathClass : public ClassClosure
	{
	public:
		MathClass(VTable* cvtable);
		~MathClass() 
		{ 
			seed.uValue = 0;
			seed.uXorMask = 0;
			seed.uSequenceLength = 0; 
		}

		// this = argv[0] (ignored)
		// arg1 = argv[1]
		// argN = argv[argc]
		Atom construct(int argc, Atom* argv);		

		// this = argv[0]
		// arg1 = argv[1]
		// argN = argv[argc]
        Atom call(int argc, Atom* argv);

		double abs(double x);
		double acos(double x);
		double asin(double x);
		double atan(double x);
		double atan2(double y, double x);
		double ceil(double x);
		double cos(double x);
		double exp(double x);
		double floor(double x);
		double log(double x);
		double pow(double x, double y);
		double random();
		double round(double x);
		double sin(double x);
		double sqrt(double x);
		double tan(double x);
		double _min(double x, double y);
		double _max(double x, double y);

		inline double min2(double x, double y) { return _min(x, y); }
		inline double max2(double x, double y) { return _max(x, y); }

		// cn:  max/min declared with rest args so we can implement ES3 spec'd length property of 2
		//      and still allow any number of arguments.
		double max(double x, double y, const Atom* argv, uint32_t argc);
		double min(double x, double y, const Atom* argv, uint32_t argc);

	private:
		TRandomFast seed;
        
		DECLARE_SLOTS_MathClass;
	};
}

#endif /* __avmplus_MathClass__ */
