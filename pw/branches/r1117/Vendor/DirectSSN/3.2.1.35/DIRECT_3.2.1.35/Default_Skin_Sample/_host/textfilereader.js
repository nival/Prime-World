

/*!
* \file TextFileReader.js
* \brief File containing TextFileReader class and creation function
*/

/*!
* \class TextFileReader
* \brief Text file reader
*/

function TextFileReader(instanceId)
{
   /*!
   * Instance id used to bind proxy object to native object
   * \type string
   */
   this.instanceId = instanceId;
   /*!
   * Triggered when file reader is started.
   * \type event
   */
   this.onStart = null;
   /*!
   * Triggered when file reader has made progress.
   * \type event
   * \tparam double percent (-1.0: Still calculating) (0.0 to 1.0: Percent completed)
   */
   this.onProgress = null;
   /*!
   * Triggered when file reader is complete.
   * \type event
   * \tparam bool successful true if the file reader was successful, false otherwise.
   */
   this.onComplete = null;
   /*!
   * Triggered when file reader reads new bytes.
   * \type event
   * \tparam string text Bytes read from file.
   */
   this.onRead = null;
}

/*!
* releases the object
*/
TextFileReader.prototype.release = function()
{
   Interop.releaseInstance(this.instanceId);
};

/*!
* gets the determines the max size of the buffer being read into
* \type int
* \returns Determines the max size of the buffer being read into
*/
TextFileReader.prototype.getBufferSize = function(){
   var methodBinding = {
      "method":"getBufferSize"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the determines the max size of the buffer being read into
* \tparam int value Determines the max size of the buffer being read into
*/
TextFileReader.prototype.setBufferSize = function(value){
   var methodBinding = {
      "method":"setBufferSize", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the file name where url is saved
* \type string
* \returns File name where url is saved
*/
TextFileReader.prototype.getFileName = function(){
   var methodBinding = {
      "method":"getFileName"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the file name where url is saved
* \tparam string value File name where url is saved
*/
TextFileReader.prototype.setFileName = function(value){
   var methodBinding = {
      "method":"setFileName", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Start file reading
*/
TextFileReader.prototype.start = function()
{
   var methodBinding = {
      "method":"start"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};


/*!
* Create instance of textFileReader
*/
function createTextFileReader()
{
   return Interop.createInstance("SSN.TextFileReader", TextFileReader);
}

