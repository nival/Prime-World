using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Settings;

namespace PF_Editor.ExportToSocial
{
    [ConfigObject(true)]
    public class ExportToSocialConfig : SimpleConfigObject
    {
        public string saveAsPath;
    }
}
