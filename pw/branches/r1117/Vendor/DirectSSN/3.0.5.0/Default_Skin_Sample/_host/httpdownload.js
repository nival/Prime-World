

/*!
* \file HttpDownload.js
* \brief File containing HttpDownload class and creation function
*/

/*!
* \class HttpDownload
* \brief HTTP downloader
*/

function HttpDownload(instanceId)
{
   /*!
   * Instance id used to bind proxy object to native object
   * \type string
   */
   this.instanceId = instanceId;
   /*!
   * Triggered when download is started.
   * \type event
   */
   this.onStart = null;
   /*!
   * Triggered when download has made progress.
   * \type event
   * \tparam double percent (-1.0: Still calculating) (0.0 to 1.0: Percent completed)
   */
   this.onProgress = null;
   /*!
   * Triggered when download is complete.
   * \type event
   * \tparam bool successful true if the download was successful, false otherwise.
   */
   this.onComplete = null;
   /*!
   * Triggered when an actual download is required.
   * \type event
   */
   this.onDownloadRequired = null;
}

/*!
* releases the object
*/
HttpDownload.prototype.release = function()
{
   Interop.releaseInstance(this.instanceId);
};

/*!
* gets the determines if caching is used in the http request
* \type bool
* \returns Determines if caching is used in the http request
*/
HttpDownload.prototype.getUseCache = function(){
   var methodBinding = {
      "method":"getUseCache"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the determines if caching is used in the http request
* \tparam bool value Determines if caching is used in the http request
*/
HttpDownload.prototype.setUseCache = function(value){
   var methodBinding = {
      "method":"setUseCache", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the url to download
* \type string
* \returns Url to download
*/
HttpDownload.prototype.getUrl = function(){
   var methodBinding = {
      "method":"getUrl"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the url to download
* \tparam string value Url to download
*/
HttpDownload.prototype.setUrl = function(value){
   var methodBinding = {
      "method":"setUrl", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the file name where url is saved
* \type string
* \returns File name where url is saved
*/
HttpDownload.prototype.getFileName = function(){
   var methodBinding = {
      "method":"getFileName"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the file name where url is saved
* \tparam string value File name where url is saved
*/
HttpDownload.prototype.setFileName = function(value){
   var methodBinding = {
      "method":"setFileName", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Start downloading
*/
HttpDownload.prototype.start = function()
{
   var methodBinding = {
      "method":"start"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};


/*!
* Create instance of httpDownload
*/
function createHttpDownload()
{
   return Interop.createInstance("SSN.HttpDownload", HttpDownload);
}

