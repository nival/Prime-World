  var isInstalled = true;
	try {
		// just attempt to create one
		var axo = new ActiveXObject("Nival.PluginHostCtrl.1");
		var version = axo.PluginVersion;
		document.write("Version detected: " + version);
	} catch (e) {
	  isInstalled = false;
	}
	if(!isInstalled)
	{
	  document.write("<br>Required version of Nival 3d control is not installed. Make sure in Tools ->Internet options->Security->internet->Custom:Initialize and script activeX controls not marked as safe =>Prompt and Download unsigned activeX control Prompt => Prompt<br>");
	}

