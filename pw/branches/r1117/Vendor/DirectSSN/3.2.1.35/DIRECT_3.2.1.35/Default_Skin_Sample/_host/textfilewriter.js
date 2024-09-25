

/*!
* \file TextFileWriter.js
* \brief File containing TextFileWriter class and creation function
*/

/*!
* \class TextFileWriter
* \brief Text file writer
*/

function TextFileWriter(instanceId)
{
   /*!
   * Instance id used to bind proxy object to native object
   * \type string
   */
   this.instanceId = instanceId;
}

/*!
* releases the object
*/
TextFileWriter.prototype.release = function()
{
   Interop.releaseInstance(this.instanceId);
};

/*!
* Open file for writing
* \tparam string fileName name of the file to close.
* \type bool
* \returns true if successful, false otherwise.
*/
TextFileWriter.prototype.open = function(fileName)
{
   var methodBinding = {
      "method":"open", 
      "fileName":fileName
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Write string to file
* \tparam string value string to write to file.
* \type int
* \returns number of bytes written to file.
*/
TextFileWriter.prototype.write = function(value)
{
   var methodBinding = {
      "method":"write", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Close file
* \type bool
* \returns true if successful, false otherwise.
*/
TextFileWriter.prototype.close = function()
{
   var methodBinding = {
      "method":"close"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};


/*!
* Create instance of textFileWriter
*/
function createTextFileWriter()
{
   return Interop.createInstance("SSN.TextFileWriter", TextFileWriter);
}

