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

package __AS3__.vec
{
	[native(cls="VectorClass", instance="ObjectVectorObject", methods="auto")]
    dynamic final public class Vector
    {
    }

	[native(cls="ObjectVectorClass", instance="ObjectVectorObject", methods="auto")]
	dynamic final class Vector$object
	{
        public function Vector$object(length:uint=0, fixed:Boolean=false)
        {
            this.length = length;
            this.fixed = fixed;
        }
        
        private native function set type(t : Object):void;
        private native function get type():Object;
        
        // Private helper methods.  These allow most of the implementation to be abstracted into
        // a file that is included from the implementation of the different Vector types.  
        private static function castToThisType(item) : Vector$object {
            return item;
        }
        
        private function newThisType(length:uint=0) : Vector$object {
            var v : Vector$object = new Vector.<type>(length);
            //v.type = this.type;
            return v;
        }

        // Include most of the vector implementation.
        include "VectorImpl.as";
        
        // Methods with the specific type in their sig.  Can't be in the impl file since it doesn't
        // know what "type" vector this is (int, uint, Number, Object)
        // Most of these just call generic versions in impl, but some small ones are implemented here.
        AS3 function concat(...items) : Vector$object {
            return _concat(items);
        }

        AS3 function filter(checker : Function, thisObj: Object=null): Vector$object {
            return _filter(checker, thisObj);
        }
        
        AS3 native function pop();

        AS3 function reverse() : Vector$object {
            this._reverse();
            return this;
        }

        AS3 function shift() {
            return private::_shift();
        }

        AS3 function slice(start:Number=0, end:Number=0x7fffffff): Vector$object {
            return this._slice(start, end);
        }

        AS3 function sort(comparefn): Vector$object {
            var a : Array = [comparefn];
            _sort(this, a);
            return this;
        }
        AS3 function splice(start: Number, deleteCount: Number, ...items): Vector$object {
            return this._splice(start, deleteCount, items);
        }

        AS3 function indexOf(value:Object, from:Number=0): Number {
            var start:uint = clamp( from, length );
            for ( var i:uint=start, limit:uint=length ; i < limit ; i++ )
                if (this[i] === value)
                    return i;
            return -1;
        }

        AS3 function lastIndexOf(value:Object, from: Number=0x7fffffff): Number { 
            var start:uint = clamp( from, length );
            if( start == length )
                --start;
            for ( var i:int=start ; i >= 0 ; i-- ) {
                if (this[i] === value)
                    return i;
            }
            return -1;
        }

	}
    
	[native(cls="IntVectorClass", instance="IntVectorObject", methods="auto")]
	dynamic final class Vector$int
	{
        
        public function Vector$int(length:uint=0, fixed:Boolean=false)
        {
            this.length = length;
            this.fixed = fixed;
        }
        
        // Private helper methods.  These allow most of the implementation to be abstracted into
        // a file that is included from the implementation of the different Vector types.  
        private static function castToThisType(item) : Vector$int {
            return item;
        }
        
        private static function newThisType(length:uint=0) : Vector$int {
            return new Vector$int(length);
        }

        // Include most of the vector implementation.
        include "VectorImpl.as";
        
        // Methods with the specific type in their sig.  Can't be in the impl file since it doesn't
        // know what "type" vector this is (int, uint, Number, Object)
        // Most of these just call generic versions in impl, but some small ones are implemented here.
        AS3 function concat(...items) : Vector$int {
            return _concat(items);
        }

        AS3 function filter(checker:Function, thisObj: Object=null): Vector$int {
            return _filter(checker, thisObj);
        }
        
        AS3 native function pop(): int ;

        AS3 function reverse() : Vector$int {
            this._reverse();
            return this;
        }
        AS3 function shift(): int {
            return private::_shift();
        }

        AS3 function slice(start:Number=0, end:Number=0x7fffffff): Vector$int {
            return this._slice(start, end);
        }
        
        AS3 function sort(comparefn): Vector$int {
            var a : Array = [comparefn];
            _sort(this, a);
            return this;
        }
        AS3 function splice(start: Number, deleteCount: Number, ...items): Vector$int {
            return this._splice(start, deleteCount, items);
        }

        AS3 function indexOf(value:int, from:Number=0): Number {
            var start:uint = clamp( from, length );
            for ( var i:uint=start, limit:uint=length ; i < limit ; i++ )
                if (this[i] === value)
                    return i;
            return -1;
        }

        AS3 function lastIndexOf(value:int, from: Number=0x7fffffff): Number { 
            var start:uint = clamp( from, length );
            if( start == length )
                --start;
            for ( var i:int=start ; i >= 0 ; i-- ) {
                if (this[i] === value)
                    return i;
            }
            return -1;
        }
        
	}
    
    
	[native(cls="UIntVectorClass", instance="UIntVectorObject", methods="auto")]
	dynamic final class Vector$uint
	{
        public function Vector$uint(length:uint=0, fixed:Boolean=false)
        {
            this.length = length;
            this.fixed = fixed;
        }

        // Private helper methods.  These allow most of the implementation to be abstracted into
        // a file that is included from the implementation of the different Vector types.  
        private static function castToThisType(item) : Vector$uint {
            return item;
        }
        
        private static function newThisType(length:uint=0) : Vector$uint {
            return new Vector$uint(length);
        }

        // Include most of the vector implementation.
        include "VectorImpl.as";
        
        // Methods with the specific type in their sig.  Can't be in the impl file since it doesn't
        // know what "type" vector this is (int, uint, Number, Object)
        // Most of these just call generic versions in impl, but some small ones are implemented here.
        AS3 function concat(...items) : Vector$uint {
            return _concat(items);
        }

        AS3 function filter(checker:Function, thisObj: Object=null): Vector$uint {
            return _filter(checker, thisObj);
        }
        
        AS3 native function pop(): uint ;

        AS3 function reverse() : Vector$uint {
            this._reverse();
            return this;
        }

        AS3 function shift(): uint {
            return private::_shift();
        }

        AS3 function slice(start:Number=0, end:Number=0x7fffffff): Vector$uint {
            return this._slice(start, end);
        }

        AS3 function sort(comparefn): Vector$uint {
            var a : Array = [comparefn];
            _sort(this, a);
            return this;
        }
        AS3 function splice(start: Number, deleteCount: Number, ...items): Vector$uint {
            return this._splice(start, deleteCount, items);
        }

        AS3 function indexOf(value:uint, from:Number=0): Number {
            var start:uint = clamp( from, length );
            for ( var i:uint=start, limit:uint=length ; i < limit ; i++ )
                if (this[i] === value)
                    return i;
            return -1;
        }

        AS3 function lastIndexOf(value:uint, from: Number=0x7fffffff): Number { 
            var start:uint = clamp( from, length );
            if( start == length )
                --start;
            for ( var i:int=start ; i >= 0 ; i-- ) {
                if (this[i] === value)
                    return i;
            }
            return -1;
        }

	}
    
	[native(cls="DoubleVectorClass", instance="DoubleVectorObject", methods="auto")]
	dynamic final class Vector$double
	{
        public function Vector$double(length:uint=0, fixed:Boolean=false)
        {
            this.length = length;
            this.fixed = fixed;
        }

        // Private helper methods.  These allow most of the implementation to be abstracted into
        // a file that is included from the implementation of the different Vector types.  
        private static function castToThisType(item) : Vector$double {
            return item;
        }
        
        private static function newThisType(length:uint=0) : Vector$double {
            return new Vector$double(length);
        }

        // Include most of the vector implementation.
        include "VectorImpl.as";
        
        // Methods with the specific type in their sig.  Can't be in the impl file since it doesn't
        // know what "type" vector this is (int, uint, Number, Object)
        // Most of these just call generic versions in impl, but some small ones are implemented here.
        AS3 function concat(...items) : Vector$double {
            return _concat(items);
        }

        AS3 function filter(checker:Function, thisObj: Object=null): Vector$double {
            return _filter(checker, thisObj);
        }
        
        AS3 native function pop(): Number ;

        AS3 function reverse() : Vector$double {
            this._reverse();
            return this;
        }

        AS3 function shift(): Number {
            return private::_shift();
        }

        AS3 function slice(start:Number=0, end:Number=0x7fffffff): Vector$double {
            return this._slice(start, end);
        }

        AS3 function sort(comparefn): Vector$double {
            var a : Array = [comparefn];
            _sort(this, a);
            return this;
        }
        AS3 function splice(start: Number, deleteCount: Number, ...items): Vector$double {
            return this._splice(start, deleteCount, items);
        }

        AS3 function indexOf(value:Number, from:Number=0): Number {
            var start:uint = clamp( from, length );
            for ( var i:uint=start, limit:uint=length ; i < limit ; i++ )
                if (this[i] === value)
                    return i;
            return -1;
        }

        AS3 function lastIndexOf(value:Number, from: Number=0x7fffffff): Number { 
            var start:uint = clamp( from, length );
            if( start == length )
                --start;
            for ( var i:int=start ; i >= 0 ; i-- ) {
                if (this[i] === value)
                    return i;
            }
            return -1;
        }
	}
}