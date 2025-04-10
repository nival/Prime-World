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

package flash.sampler
{
    /**
     * The StackFrame class provides access to the properties of a data block
     * containing a function. For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword StackFrame      
     */
    [native(cls="StackFrameClass", instance="StackFrameObject", methods="auto", constsetters="true")] // @todo: native only for slot getter/setter
    public final class StackFrame
    {
    
		/**
		 * The function name in the stack frame. For Flash Player debugger version only.
		 * @playerversion Flash 9.0.115.0
		 * @langversion 3.0     
		 * @keyword StackFrame.name, name      
		 */    
		public const name:String;
    
		/**
		 * The file name of the SWF file being debugged. For Flash Player debugger version only.
		 * @playerversion Flash 9.0.115.0
		 * @langversion 3.0     
		 * @keyword StackFrame.file, file      
		 */       
		public const file:String;
    
		/**
		 * The line number for the function in the SWF file being debugged. For Flash Player debugger version only.
		 * @playerversion Flash 9.0.115.0
		 * @langversion 3.0     
		 * @keyword StackFrame.line, line      
		 */      
		public const line:uint;
	
		/**
		 * The identifier for the script function in the application being profiled.
		 * @langversion 3.0
		 * @keyword StackFrame.scriptID, scriptID      
		 */
		public const scriptID:Number;
    
		/**
		 * Converts the StackFrame to a string of its properties.
		 * @return A string containing the <code>name</code> property, and optionally the <code>file</code> 
		 * and <code>line</code> properties (if a SWF file is being debugged) of the StackFrame object. For Flash Player debugger version only.
		 * @playerversion Flash 9.0.115.0
		 * @langversion 3.0     
		 * @keyword StackFrame.toString, toString      
		 */      
		public function toString():String
		{
			return name + "()" + (file ? "[" + file + ":" + line + "]" : "");
		}
    };
	

    /**
     * The Sample class creates objects that hold memory analysis information over distinct durations.
     * For Flash Player debugger version only.
     *
     * @includeExample examples\SampleTypesExample.as -noswf     
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword Sample      
     * @see package.html#getSamples() flash.sampler.getSamples()
     */
    [native(cls="SampleClass", instance="SampleObject", methods="auto", constsetters="true")]
    public class Sample
    {
		/**
	     * The microseconds that define the duration of the Sample instance. For Flash Player debugger version only.
		 * 
		 * @playerversion Flash 9.0.115.0
	     * @langversion 3.0     
	     * @keyword Sample, Sample.time, time         
		 */
        public const time:Number;

		/**
		 * Contains information about the methods executed by Flash Player over a specified period of time. The format for the 
	     * stack trace is similiar to the content shown in the exception dialog box of the Flash Player debugger version.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
	     * @langversion 3.0     
	     * @keyword Sample, Sample.stack, stack     
		 */
        public const stack:Array;
    };

    /**
    * The NewObjectSample class represents objects that are created within a <code>getSamples()</code> stream.
    * For Flash Player debugger version only.
    * @playerversion Flash 9.0.115.0
    * @langversion 3.0     
    * @keyword NewObjectSample 
    * @see package.html#getSamples() flash.sampler.getSamples()
    * @includeExample examples\SampleTypesExample.as -noswf    
    */
    [native(cls="NewObjectSampleClass", instance="NewObjectSampleObject", methods="auto", constsetters="true")]
    public final class NewObjectSample extends Sample
    {
    	/** 
    	 * The unique identification number that matches up with a DeleteObjectSample's identification number.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword NewObjectSample, NewObjectSample.id, id  
         * @see flash.sampler.DeleteObjectSample#id
    	 */
    	public const id:Number;
    	
    	/**
         * The Class object corresponding to the object created within a <code>getSamples()</code> stream.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword NewObjectSample, NewObjectSample.type, type 
    	 */
    	public const type:Class;
    	
    	/**
    	 * The NewObjectSample object if it still exists. If the object has been garbage collected, this property is
    	 * undefined and a corresponding DeleteObjectSample exists. For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword NewObjectSample, NewObjectSample.object, object 
         * @see flash.sampler.DeleteObjectSample         
    	 */
    	public native function get object():*;

        public native function get size() : Number;
    };
	
	/**
    * The DeleteObjectSample class represents objects that are created within a <code>getSamples()</code> stream; each
    * DeleteObjectSample object corresponds to a NewObjectSample object. For Flash Player debugger version only.
    * @playerversion Flash 9.0.115.0
    * @langversion 3.0     
    * @keyword DeleteObjectSample 
    * @see package.html#getSamples() flash.sampler.getSamples()
    * @includeExample examples\SampleTypesExample.as -noswf    
    */    
    [native(cls="DeleteObjectSampleClass", instance="DeleteObjectSampleObject", methods="auto", constsetters="true")] // @todo: native only for slot getter/setter
    public final class DeleteObjectSample extends Sample
    {
    	/** 
         * The unique identification number that matches up with a NewObjectSample's identification number.
         * For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword DeleteObjectSample, DeleteObjectSample.id, id  
         * @see flash.sampler.NewObjectSample#id
         */
    	public const id:Number;

	    /**
         * The size of the DeleteObjectSample object before it is deleted. For Flash Player debugger version only.
         * @playerversion Flash 9.0.115.0
         * @langversion 3.0     
         * @keyword DeleteObjectSample, DeleteObjectSample.size, size  
         * @see flash.sampler.NewObjectSample#id
         */
		public const size:Number;
    };


    /**
     * Clears the current set of Sample objects. This method is usually called after calling <code>getSamples()</code>
     * and iterating over the Sample objects.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword clearSamples      
     * @see package.html#getSamples() getSamples()
     */
    [native("SamplerScript::clearSamples")]
	public native function clearSamples():void;

    /**
     * Begins the process of collecting memory usage Sample objects.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @includeExample examples\StartSamplingExample.as -noswf      
     * @keyword startSampling      
     * @see flash.sampler.Sample Sample class
     */
    [native("SamplerScript::startSampling")]
	public native function startSampling():void;

	/**
	 * Ends the process of collecting memory usage Sample objects and frees resources dedicated to the sampling process.
     * You start the sampling process with <code>startSampling()</code>.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword stopSampling      
     * @see flash.sampler.Sample Sample class
	 */
    [native("SamplerScript::stopSampling")]
	public native function stopSampling():void;

	/**
     * Stops the sampling process momentarily. Restart the sampling process using <code>startSampling()</code>.
     * For Flash Player debugger version only.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword pauseSampling      
     * @see package.html#startSampling() startSampling()
	 */
    [native("SamplerScript::pauseSampling")]
	public native function pauseSampling():void;
	
	/**
     * Tells the sampler if it should create NewObjectSamples for internal allocations from the flash player.
     * If this is set to true, then every allocation will generate a NewObjectSample.  These internal allocs will
     * not have a type, or a reference to the Object.  They will have the ActionScript stack trace that triggered the
     * allocation.  Defaults to false, which only collects allocations for ActionScript objects.
     * @langversion 3.0
     * @keyword sampleInternalAllocs
     */
    [native("SamplerScript::sampleInternalAllocs")]
	public native function sampleInternalAllocs(b:Boolean):void;

	/**
     * Set a callback function for the sampler - this function will be called when the sample stream is almost
     * exhausted.  This should be used to process samples before the sample buffer is filled.  pauseSampling will be called
     * before the callback is called, and startSampling will be called after the callback has been executed.
     * @langversion 3.0
     * @keyword sampleInternalAllocs
     */
	public function setSamplerCallback(f:Function):void
    {
        if( f != null )
        {
            // Use a wrapper to swallow any exceptions thrown by the callback.
            var wrapper = function() 
            {
                var ret:Boolean = true;
                try
                {
                    f();
                }
                catch(e)
                {
                    ret = false; 
                }
                return ret;
            }
            _setSamplerCallback(wrapper);
        }
        else
        {
            _setSamplerCallback(null);
        }
    }
    [native("SamplerScript::_setSamplerCallback")]
    native function _setSamplerCallback(f:Function):void;
    
	/**
	* Returns the size in memory of a specified object when used with the Flash Player 9.0.115.0 or later debugger version. If 
    * used with a Flash Player that is not the debugger version, this method returns <code>0</code>.
    * @param o The object to analyze for memory usage.
    * @return The byte count of memory used by the specified object.
    * @includeExample examples\DeletedObjectSizeExample.as -noswf      
    * @playerversion Flash 9.0.115.0
    * @langversion 3.0     
    * @keyword getSize      
	*/
    [native("SamplerScript::getSize")]
	public native function getSize(o:*):Number;

    /**
     * Returns an object containing all members of a specified object, including private members. You can then 
     * iterate over the returned object to see all values. This method is similar to the flash.utils.describeType() 
     * method but also allows you to see private members and skips the intermediate step of creating an XML object.
     * For Flash Player debugger version only.
     *
     * @param o The object to analyze.
     * @param instanceNames If object is a Class and instanceNames is true report the instance names as if o was an instance of class instead of the class's member names.
     * @return An Object that you must iterate over with a <code>for each..in</code> loop to retrieve the QNames for
     * each property. 
     * @includeExample examples\GetMemberNamesExample.as -noswf       
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getMemberNames
     * @see flash.utils#describeType()
     * @see ../../statements.html#for_each..in for each..in    
     * 
     */
    [native("SamplerScript::getMemberNames")]
    public native function getMemberNames(o:Object, instanceNames:Boolean=false):Object;

 
    /**
     * Returns an object of memory usage Sample instances from the last sampling session. For Flash Player debugger version only.
     *
     * @return An iterator of Sample instances.
     * @playerversion Flash 9.0.115.0 
     * @langversion 3.0     
     * @keyword getSamples     
     * @see flash.sampler.Sample
     */
    [native("SamplerScript::getSamples")]
    public native function getSamples():Object;

    /** 
     * Returns the number of samples collected. For Flash Player debugger version only.
     *
     * @return An iterator of Sample instances.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getSampleCount     
     * @see flash.sampler.Sample    
     */
    [native("SamplerScript::getSampleCount")]
    public native function getSampleCount():Number;
 
   /**
     * Returns the number of times a method was executed. If the parameter <code>obj</code>
     * is a Class and the parameter <code>qname</code> is <code>undefined</code> then this method
     * returns the number of iterations of the constructor function. For Flash Player debugger version only.
     * @param obj A method instance or a class. A class can be used to get the invocation count of 
     * instance functions when a method instance isn't available. If <code>obj</code> is <code>undefined</code>,
     * this method returns the count of the package-scoped function named by <code>qname</code>.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return The number of times a method was executed.
     * @includeExample examples\GetInvocationCountExample.as -noswf       
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount     
     */
    public function getInvocationCount(obj:Object, qname:QName):Number { return _getInvocationCount(obj, qname, 0); }
    
    /**
     * Returns the number of times a set function was executed. Use 
     * <code>isGetterSetter()</code> to verify that you have a get/set function before you use
     * <code>getSetterInvocationCount()</code>. For Flash Player debugger version only.
     * @param obj A method instance or a class.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return The number of times a set method was executed.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount   
     * @see package.html#isGetterSetter() isGetterSetter()
     * @see package.html#getInvocationCount() getInvocationCount()
     */    
    public function getSetterInvocationCount(obj:Object, qname:QName):Number { return _getInvocationCount(obj, qname, 2); }
    
    /**
     * Returns the number of times a get function was executed. Use 
     * <code>isGetterSetter()</code> to verify that you have a get/set function before you use
     * <code>getGetterInvocationCount()</code>. For Flash Player debugger version only.
     * @param obj A method instance or a class.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return The number of times a get method was executed.
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount   
     * @see package.html#isGetterSetter() isGetterSetter()
     * @see package.html#getInvocationCount() getInvocationCount()
     */        
    public function getGetterInvocationCount(obj:Object, qname:QName):Number { return _getInvocationCount(obj, qname, 1); }

    /** 
    * @private
    */
    [native("SamplerScript::_getInvocationCount")]
    native function _getInvocationCount(obj:Object, qname:QName, type:uint):Number;

   /**
     * Checks to see if a property is defined by a get/set function. If you want to use 
     * <code>getInvocationCount()</code> on a get/set function for a property,
     * first call <code>isGetterSetter()</code> to check to see if it is a get/set function,
     * and then use either <code>getSetterInvocationCount</code>
     * or <code>getGetterInvocationCount</code> to get the respective counts. For Flash Player debugger version only.
     * @param obj A method instance or a class.
     * @param qname If qname is <code>undefined</code> return the number of iterations of the constructor function.
     * @return A Boolean value indicating if the property is defined by a get/set function (<code>true</code>)
     * or not (<code>false</code>).
     * @includeExample examples\GetInvocationCountExample.as -noswf       
     * @playerversion Flash 9.0.115.0
     * @langversion 3.0     
     * @keyword getInvocationCount   
     * @see package.html#getInvocationCount() getInvocationCount()
     * @see package.html#getSetterInvocationCount() getSetterInvocationCount() 
     * @see package.html#getGetterInvocationCount() getGetterInvocationCount() 
     */
    [native("SamplerScript::isGetterSetter")]
    public native function isGetterSetter(obj:Object, qname:QName):Boolean;
};
