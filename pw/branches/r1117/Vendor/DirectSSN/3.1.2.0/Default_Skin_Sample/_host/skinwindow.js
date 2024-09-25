

/*!
* \file SkinWindow.js
* \brief File containing SkinWindow class and creation function
*/

/*!
* \class SkinWindow
* \brief Solid State's HTML Skinned Window
*/

function SkinWindow(instanceId)
{
   /*!
   * Instance id used to bind proxy object to native object
   * \type string
   */
   this.instanceId = instanceId;
   /*!
   * Triggered before the window is closed.
   * \type event
   * \return bool: true to allow the window to close, false otherwise.
   */
   this.onWillClose = null;
   /*!
   * Triggered when the window is closed.
   * \type event
   */
   this.onDidClose = null;
}

/*!
* releases the object
*/
SkinWindow.prototype.release = function()
{
   Interop.releaseInstance(this.instanceId);
};

/*!
* gets the x origin of the window.
* \type int
* \returns X origin of the window.
*/
SkinWindow.prototype.getX = function(){
   var methodBinding = {
      "method":"getX"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the y origin of the window.
* \type int
* \returns Y origin of the window.
*/
SkinWindow.prototype.getY = function(){
   var methodBinding = {
      "method":"getY"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the width of the window.
* \type int
* \returns Width of the window.
*/
SkinWindow.prototype.getWidth = function(){
   var methodBinding = {
      "method":"getWidth"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* gets the height of the window.
* \type int
* \returns Height of the window.
*/
SkinWindow.prototype.getHeight = function(){
   var methodBinding = {
      "method":"getHeight"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Set the origin of the launcher window
* \tparam int x The desired x value of the launcher window.
* \tparam int y The desired y value of the launcher window.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.setOrigin = function(x, y)
{
   var methodBinding = {
      "method":"setOrigin", 
      "x":x, 
      "y":y
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Set the size of the launcher window
* \tparam int width The desired width of the launcher window.
* \tparam int height The desired height of the launcher window.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.setSize = function(width, height)
{
   var methodBinding = {
      "method":"setSize", 
      "width":width, 
      "height":height
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* Set the title of the launcher window
* \tparam string title The title of the launcher window.
*/
SkinWindow.prototype.setTitle = function(title)
{
   var methodBinding = {
      "method":"setTitle", 
      "title":title
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method informs the native window of any movement so that the native/browser windows can be synchronized.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.beginMove = function()
{
   var methodBinding = {
      "method":"beginMove"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method informs the native window of any movement so that the native/browser windows can be synchronized.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.beginSize = function()
{
   var methodBinding = {
      "method":"beginSize"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method will show the window.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.show = function()
{
   var methodBinding = {
      "method":"show"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method will hide the window.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.hide = function()
{
   var methodBinding = {
      "method":"hide"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method will minimize the launcher application.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.minimize = function()
{
   var methodBinding = {
      "method":"minimize"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method will restore a minimized launcher application.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.restore = function()
{
   var methodBinding = {
      "method":"restore"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This method will exit the launcher application.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.close = function()
{
   var methodBinding = {
      "method":"close"
   };
   return Interop.invoke(this.instanceId, methodBinding);
};

/*!
* This creates a loads a new window.
* \tparam string windowConfigUrl URL to the window configuration file.
* \type bool
* \returns true upon success, false upon failure.
*/
SkinWindow.prototype.load = function(windowConfigUrl)
{
   var methodBinding = {
      "method":"load", 
      "windowConfigUrl":windowConfigUrl
   };
   return Interop.invoke(this.instanceId, methodBinding);
};


/*!
* Create instance of skinWindow
*/
function createSkinWindow()
{
   return Interop.createInstance("SSN.SkinWindow", SkinWindow);
}

