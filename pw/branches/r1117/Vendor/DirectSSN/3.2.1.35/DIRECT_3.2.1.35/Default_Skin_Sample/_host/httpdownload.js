

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
   /*!
   * Triggered when a write is required.
   * \type event
   * \tparam string buffer Hex converted buffer for the download.
   * \return bool: true to continue download, false to cancel
   */
   this.onWrite = null;
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
* gets the determines if the write callback is used in the http request
* \type bool
* \returns Determines if the write callback is used in the http request
*/
HttpDownload.prototype.getUseWriteCallback = function(){
   var methodBinding = {
      "method":"getUseWriteCallback"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the determines if the write callback is used in the http request
* \tparam bool value Determines if the write callback is used in the http request
*/
HttpDownload.prototype.setUseWriteCallback = function(value){
   var methodBinding = {
      "method":"setUseWriteCallback", 
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
* gets the number of times to retry
* \type int
* \returns Number of times to retry
*/
HttpDownload.prototype.getRetryCount = function(){
   var methodBinding = {
      "method":"getRetryCount"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the number of times to retry
* \tparam int value Number of times to retry
*/
HttpDownload.prototype.setRetryCount = function(value){
   var methodBinding = {
      "method":"setRetryCount", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the seconds to wait for connection before timeout
* \type int
* \returns Seconds to wait for connection before timeout
*/
HttpDownload.prototype.getConnectTimeout = function(){
   var methodBinding = {
      "method":"getConnectTimeout"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the seconds to wait for connection before timeout
* \tparam int value Seconds to wait for connection before timeout
*/
HttpDownload.prototype.setConnectTimeout = function(value){
   var methodBinding = {
      "method":"setConnectTimeout", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the exit code for download
* \type int
* \returns Exit code for download
*/
HttpDownload.prototype.getExitCode = function(){
   var methodBinding = {
      "method":"getExitCode"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the proxy host and port
* \type string
* \returns Proxy host and port
*/
HttpDownload.prototype.getProxy = function(){
   var methodBinding = {
      "method":"getProxy"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the proxy realm
* \type string
* \returns Proxy realm
*/
HttpDownload.prototype.getProxyRealm = function(){
   var methodBinding = {
      "method":"getProxyRealm"
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

