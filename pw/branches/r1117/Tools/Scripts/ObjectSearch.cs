/*
#about Ищет объекты по указанному пути с указанными параметрами.
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
#ref sharpsvn.dll
*/

using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using DBTypes;
using EditorLib;
using EditorLib.IO;
using EditorLib.Operations;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using SharpSvn;
using libdb.Diagnostics;
using System.Reflection;

public class MyFirstScript
{

	//*****************************************************************************//

	private string path = "/Heroes/Faceless"; // Корневой путь для поиска { "" == "Root"}
	private string key = "emissive"; // Ключевое поле поиска { регистр не учитывается при поиске }
	private string value = "0"; // Значение поля

	//*****************************************************************************//


	private List<DBResource> foundedItems = new List<DBResource>();
	private IEditorCommonApplication application;

	public IEnumerable Main(IEditorCommonApplication app )
	{
		application = app;
		app.OperationExecutor.Start(Search);
		yield return true;
	}

	private bool Search( IOperationContext context )
	{
		context.Start( true, true );
		Log.TraceMessage( "Starting search.");

		List<DBID> dbids;
		Log.TraceMessage( "Collecting objects..." );
		ObjectsSelector.CollectObjects( application, path, typeof( DBResource ), true, true, out dbids );
		Log.TraceMessage( "Objects collected." );
		float progress = 0;
		foreach ( DBID dbid in dbids )
		{
			progress++;
			DBResource obj = DataBase.Get<DBResource>( dbid ).Get();

			if ( CheckObject( obj ) )
				foundedItems.Add( obj );

			context.Progress("Processing ", (int)((progress/dbids.Count)*100));
		}
		
		Log.TraceMessage( "Done." );
		Log.TraceMessage( "***************************RESULTS********************************" );

		ShowResult();

		context.Progress( "Ready");
		return true;
	}
	private bool CheckObject(DBResource obj)
	{
		Type type = obj.GetType();

		PropertyInfo[] properties;
		FieldInfo[] fields;

		properties = type.GetProperties();
		fields = type.GetFields();

		foreach ( PropertyInfo prop in properties )
		{
			if (string.Equals(prop.Name, key, StringComparison.InvariantCultureIgnoreCase))
			{
				object result = prop.GetValue( obj, new object[] { } );
				if ( result != null )
				{
					if ( result.ToString() == value )
					{
						return true;
					}
				}
			}
		}

		foreach ( FieldInfo field in fields )
		{
			if ( field.Name.ToLower().Contains( key.ToLower() ) )
			{
				object result = field.GetValue( obj );
				if ( result != null )
				{
					if ( result.ToString() == value )
					{
						return true;
					}
				}
			}
		}

		return false;
	}
	private void ShowResult()
	{
		foreach(DBResource obj in foundedItems )
		{
			Log.TraceMessage(obj.DBId.ToString());
		}
	}
}