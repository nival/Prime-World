

/*!
* \file App.js
* \brief File containing App class and creation function
*/

/*!
* \class App
* \brief Solid State's Application Interface
*/

function App(instanceId)
{
   /*!
   * Instance id used to bind proxy object to native object
   * \type string
   */
   this.instanceId = instanceId;
   /*!
   * Triggered when a bundle is attached.
   * \type event
   * \tparam string bundleName name of the bundle to attach.
   * \tparam string path path of the bundle to attach.
   * \tparam bool successful true if the attach was successful, false otherwise.
   */
   this.onBundleAttached = null;
   /*!
   * Triggered when an interop library is loaded.
   * \type event
   * \tparam string fileName file name of the interop library.
   * \tparam bool successful true if the load was successful, false otherwise.
   */
   this.onInteropLoaded = null;
   /*!
   * Triggered when an restart is required.
   * \type event
   */
   this.onWillRestart = null;
   /*!
   * This event is triggered whenever a http get is attempted.
   * \type event
   * \tparam string url url for the http get.
   * \return string: new url for the http get.
   */
   this.onWillConstructWebGetTarget = null;
}

/*!
* releases the object
*/
App.prototype.release = function()
{
   Interop.releaseInstance(this.instanceId);
};

/*!
* gets the host's current elevation status
* \type bool
* \returns host's current elevation status
*/
App.prototype.getElevated = function(){
   var methodBinding = {
      "method":"getElevated"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the flag value to remove the local storage directory on shutdown
* \type bool
* \returns flag value to remove the local storage directory on shutdown
*/
App.prototype.getRemoveLocalStorage = function(){
   var methodBinding = {
      "method":"getRemoveLocalStorage"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the flag value to remove the local storage directory on shutdown
* \tparam bool value flag value to remove the local storage directory on shutdown
*/
App.prototype.setRemoveLocalStorage = function(value){
   var methodBinding = {
      "method":"setRemoveLocalStorage", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the flag value to restart the host
* \type bool
* \returns flag value to restart the host
*/
App.prototype.getRestart = function(){
   var methodBinding = {
      "method":"getRestart"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the flag value to restart the host
* \tparam bool value flag value to restart the host
*/
App.prototype.setRestart = function(value){
   var methodBinding = {
      "method":"setRestart", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the flag value to elevate the restart
* \type bool
* \returns flag value to elevate the restart
*/
App.prototype.getRestartElevated = function(){
   var methodBinding = {
      "method":"getRestartElevated"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the flag value to elevate the restart
* \tparam bool value flag value to elevate the restart
*/
App.prototype.setRestartElevated = function(value){
   var methodBinding = {
      "method":"setRestartElevated", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the self delete on exit
* \type bool
* \returns self delete on exit
*/
App.prototype.getImplode = function(){
   var methodBinding = {
      "method":"getImplode"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the self delete on exit
* \tparam bool value self delete on exit
*/
App.prototype.setImplode = function(value){
   var methodBinding = {
      "method":"setImplode", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the application command line
* \type string
* \returns application command line
*/
App.prototype.getCommandLine = function(){
   var methodBinding = {
      "method":"getCommandLine"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* sets the application command line
* \tparam string value application command line
*/
App.prototype.setCommandLine = function(value){
   var methodBinding = {
      "method":"setCommandLine", 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method expands the string with the current macros.
* \tparam string expand Name of string to be expanded.
* \type string
* \returns expanded string.
*/
App.prototype.expandString = function(expand)
{
   var methodBinding = {
      "method":"expandString", 
      "expand":expand
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method retrieves a config setting.
* \tparam string key Name of config setting to be retrieved.
* \tparam string defaultValue Default value of key if nothing is found.
* \type string
* \returns value of key's setting.
*/
App.prototype.getConfig = function(key, defaultValue)
{
   var methodBinding = {
      "method":"getConfig", 
      "key":key, 
      "defaultValue":defaultValue
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method sets a config setting.
* \tparam string key Name of config setting to be retrieved.
* \tparam string value Value store in key parameter.
*/
App.prototype.setConfig = function(key, value)
{
   var methodBinding = {
      "method":"setConfig", 
      "key":key, 
      "value":value
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method checks if a url is in the app config whitelist.
* \tparam string url Url to be checked.
* \type bool
* \returns true if authorized, false otherwise.
*/
App.prototype.authorizeUrl = function(url)
{
   var methodBinding = {
      "method":"authorizeUrl", 
      "url":url
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method checks if a bundle name has already been attached.
* \tparam string bundleName Name of bundle to be checked.
* \type bool
* \returns true if attached, false otherwise.
*/
App.prototype.hasBundle = function(bundleName)
{
   var methodBinding = {
      "method":"hasBundle", 
      "bundleName":bundleName
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method attaches a bundle.
* \tparam string bundleName Name of bundle to be checked.
* \tparam string path Local location of the bundle.
*/
App.prototype.attachBundle = function(bundleName, path)
{
   var methodBinding = {
      "method":"attachBundle", 
      "bundleName":bundleName, 
      "path":path
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method loads an interop library.
* \tparam string fileName Name of interop library to be loaded.
*/
App.prototype.loadInterop = function(fileName)
{
   var methodBinding = {
      "method":"loadInterop", 
      "fileName":fileName
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Adds an information line to the host log file.
* \tparam string message string to add to the log file.
*/
App.prototype.info = function(message)
{
   var methodBinding = {
      "method":"info", 
      "message":message
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Adds a warning line to the host log file.
* \tparam string message string to add to the log file.
*/
App.prototype.warn = function(message)
{
   var methodBinding = {
      "method":"warn", 
      "message":message
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Adds an error line to the host log file.
* \tparam string message string to add to the log file.
*/
App.prototype.error = function(message)
{
   var methodBinding = {
      "method":"error", 
      "message":message
   };
   return Interop.invoke(this.instanceId, methodBinding);
};


/*!
* Create instance of app
*/
function createApp()
{
   return Interop.createInstance("SSN.App", App);
}

