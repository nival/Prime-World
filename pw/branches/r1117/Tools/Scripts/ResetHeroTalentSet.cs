/*
#about Сброс талантов и очков мастерства героя (выбранный герой будет отмечен для единовременной отвязки талантов при первом заходе)
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
#ref EditorPlugins.dll
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using EditorPlugins.Importer.Texture;
using libdb;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;
using System.Windows.Forms;

public class ResetHeroTalentSet
{
    public IEnumerable Main(IEditorCommonApplication app, string[] parameters)
    {
        string heroFilePath;

        if (parameters.Length == 0)
        {
            //Called from editor UI
            var openFileDialog = new OpenFileDialog
            {
                InitialDirectory = Convert.ToString(Environment.SpecialFolder.Recent),
                Filter = @"Xdb (*.xdb)|*.xdb|All Files (*.*)|*.*",
                Title = @"Choose hero for reseting talents",
                FilterIndex = 1
            };

            if (openFileDialog.ShowDialog() == DialogResult.OK)
                heroFilePath = openFileDialog.FileName;
            else
                yield break;
        }
        else
            heroFilePath = parameters[0];

        var fullRootPath = Path.GetFullPath(app.FileSystem.RootPath);
        if (heroFilePath.Contains(fullRootPath))
            heroFilePath = heroFilePath.Substring(fullRootPath.Length);

        Hero hero = DataBase.Get<Hero>(DBID.FromFileName(heroFilePath, false));

        if (hero == null)
        {
            Log.TraceMessage("Wrong hero path: {0}", heroFilePath);
            yield break;
        }
        Log.TraceMessage("Reset talents for hero \"{0}\"...", hero.persistentId);
        hero.lobbyData.Version++;
        Log.TraceMessage("Save results..");
        DataBase.Store();

        yield return true;
    }
}