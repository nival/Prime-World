/* -*- Mode: Java; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
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
package abcasm;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Map;
import java.util.TreeMap;

/**
 * Abstract representation of an ABC pool,
 * which can be sorted according to some
 * criterion (e.g., most used elements to
 * lowest positions).
 *
 * @param <T>
 */
public class Pool<T extends Comparable>
{
	Map<T,Integer> refs = new TreeMap<T,Integer>();
	ArrayList<T> values = new ArrayList<T>();
	int countFrom;
	
	public Pool(int countFrom)
	{
		this.countFrom = countFrom;
	}
	
	public int add(T e)
	{
		if ( !refs.containsKey(e) )
		{
			values.add(e);
			refs.put(e, size());
		}

		return refs.get(e);
	}
	
	public ArrayList<T> getValues()
	{
		return values;
	}
	
	public int id(T e)
	{
		if ( !refs.containsKey(e))
			throw new IllegalArgumentException("Unknown pool item \"" + e.toString() + "\"");
		return refs.get(e);
	}
	
	public String toString()
	{
		return String.valueOf(refs);
	}
	
	public int size()
	{
		return countFrom + refs.size();
	}
}

