using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using EditorLib;
using EditorLib.Menu;
using libdb.Diagnostics;
using libdb.IO;
using System.Windows.Forms;

namespace PF_Editor.ExportToSocial
{
    public class ExportToSocialAsCommand : IEditorCommand
    {
        private const string scriptName = "../Tools/Scripts/ExportSocialData.cs";
        public override void Execute(IEditorWinApplication application)
        {
            var config = application.Application.Settings.Get<ExportToSocialConfig>();

            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.InitialDirectory = Convert.ToString(Environment.SpecialFolder.MyDocuments);
            saveFileDialog.Filter = "Xml (*.xml)|*.xml|All Files (*.*)|*.*";
            saveFileDialog.FilterIndex = 1;
            saveFileDialog.FileName = "ExportedSocialData";

            if (saveFileDialog.ShowDialog() == DialogResult.OK)
                config.saveAsPath = saveFileDialog.FileName;
            else
                return;

            var scriptMachine = application.Application.Scripts;
            scriptMachine.LoadScript(Path.GetFullPath(scriptName), new string[] { config.saveAsPath });
        }

        public override string Name { get { return "Save for Social As..."; } }

        public override string TooltipText
        {
            get { return "Open Save As dialog for exporting data"; }
        }
    }

    public class ExportToSocialServerAsCommand : IEditorCommand
    {
      private const string scriptName = "../Tools/Scripts/ExportSocialData.cs";
      public override void Execute(IEditorWinApplication application)
      {
        var config = application.Application.Settings.Get<ExportToSocialConfig>();

        SaveFileDialog saveFileDialog = new SaveFileDialog();
        saveFileDialog.InitialDirectory = Convert.ToString(Environment.SpecialFolder.MyDocuments);
        saveFileDialog.Filter = "Xml (*.xml)|*.xml|All Files (*.*)|*.*";
        saveFileDialog.FilterIndex = 1;
        saveFileDialog.FileName = "ExportedSocialData";

        if (saveFileDialog.ShowDialog() == DialogResult.OK)
          config.saveAsPath = saveFileDialog.FileName;
        else
          return;

        var scriptMachine = application.Application.Scripts;
        scriptMachine.LoadScript(Path.GetFullPath(scriptName), new string[] { "server", config.saveAsPath });
      }

      public override string Name { get { return "Save for Social Server As..."; } }

      public override string TooltipText
      {
        get { return "Open Save As dialog for exporting data"; }
      }
    }

    public class ExportToSocialCommand : IEditorCommand
    {
        private const string scriptName = "../Tools/Scripts/ExportSocialData.cs";

        public override void Execute(IEditorWinApplication application)
        {
            var config = application.Application.Settings.Get<ExportToSocialConfig>();
                       
            if (string.IsNullOrEmpty(config.saveAsPath))
            {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                saveFileDialog.InitialDirectory = Convert.ToString(Environment.SpecialFolder.MyDocuments);
                saveFileDialog.Filter = "Xml (*.xml)|*.xml|All Files (*.*)|*.*";
                saveFileDialog.FilterIndex = 1;
                saveFileDialog.FileName = "ExportedSocialData";

                if (saveFileDialog.ShowDialog() == DialogResult.OK)
                    config.saveAsPath = saveFileDialog.FileName;
                else
                    return;
            }

            var scriptMachine = application.Application.Scripts;
            scriptMachine.LoadScript(Path.GetFullPath(scriptName), new string[] { config.saveAsPath });
        }

        public override string Name { get { return "Save for Social"; } }

        public override string TooltipText
        {
            get { return "Save exporting data"; }
        }
    }
}
