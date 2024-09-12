var plugloc = "Nival3dPlugin_inst_Win.xpi";
// Plugins list
var children = navigator.plugins;
var needInstall  = true;
for (var i = 0; i < children.length; ++i) 
{
  if("npDllLoader native renderer plug-in" == children[i].name)
  {
    needInstall = false; 
  }
}
if(needInstall)
{
  this.location.href = plugloc;
}
