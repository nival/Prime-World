/*
#about (Not used)
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System.Collections;
using System.Collections.Generic;
using DBTypes;
using libdb.DB;
using System.IO;
using System.Diagnostics;
using System;

public class HeloWorld
{
  private int counter = 0;

  private bool IsZero( string expression )
  {
    return expression == "0" || expression == "0." || expression == "0.0" || expression == "0f" || expression == "0.f" || expression == "0.0f";
  }

  private bool IsOne( string expression )
  {
    return expression == "1" || expression == "1." || expression == "1.0" || expression == "1f" || expression == "1.f" || expression == "1.0f";
  }

  private void ProcessApplicator( BaseApplicator applicator, string name, List<string> nodes, List<string> links )
  {
    string node = string.Empty;
    if ( applicator is PermanentStatModApplicator )
    {
      PermanentStatModApplicator a = applicator as PermanentStatModApplicator;
      node = a.modifier.stat.ToString();
      if ( !IsOne( a.modifier.multValue.sString ) )
        node += " x" + a.modifier.multValue.sString;
      if ( !IsZero( a.modifier.addValue.sString ) )
        node += " +" + a.modifier.addValue.sString;
    }

    if ( !string.IsNullOrEmpty( node ) )
    {
      string id = "applicator" + ( ++counter ).ToString();
      nodes.Add( string.Format( "{0} [shape=\"box\", label=\"{1}\"]", id, node ) );
      links.Add( string.Format( "{0} -> {1}", name, id ) );
    }
  }

  private void ProcessAbility( Ability ability, string name, List<string> nodes, List<string> links )
  {
    for( int i = 0; i < ability.passiveApplicators.Count; ++i )
    {
      BaseApplicator passive = ability.passiveApplicators[i].Get();
      string id = "passiveApplicator" + (++counter).ToString();
      nodes.Add( string.Format( "{0} [shape=\"box\", label=\"{1}\\n{2}\", style=\"filled\", fillcolor=\"gray80\"]", id, passive.GetType().Name, string.IsNullOrEmpty( passive.caption ) ? "passive" + i.ToString() : passive.caption ) );
      links.Add( string.Format( "{0} -> {1}", name, id ) );
      ProcessApplicator( passive, id, nodes, links );
    }
  }

  private void ProcessHero( EditorLib.IEditorWinApplication app )
  {
    List<string> nodes = new List<string>();
    List<string> links = new List<string>();
    Hero hero = DataBase.Get<Hero>( DBID.FromString( "/Heroes/Rockman/_.HROB" ) );

    nodes.Add( string.Format( "Hero [shape=\"box\", label=\"{0}\"]", hero.description ) );
    nodes.Add( string.Format( "attackAbility [shape=\"box\", label=\"{0}\"]", string.IsNullOrEmpty( hero.attackAbility.Get().name.ToString() ) ? "attackAbility" : hero.attackAbility.Get().name.ToString() ) );
    links.Add( "Hero -> attackAbility" );
    ProcessAbility( hero.attackAbility.Get(), "attackAbility", nodes, links );
    for ( int i = 0; i < 5; ++i )
    {
      EAbility id = (EAbility)i;
      Ability ability = hero.abilities[i].Get();
      nodes.Add( string.Format( "{0} [shape=\"box\", label=\"{1}\"]", id.ToString(), string.IsNullOrEmpty( ability.name.ToString() ) ? id.ToString() : ability.name.ToString() ) );
      links.Add( string.Format( "Hero -> {0}", id.ToString() ) );
      ProcessAbility( ability, id.ToString(), nodes, links );
    }

    using ( StreamWriter writer = new StreamWriter( "output.dot" ) )
    {
      writer.WriteLine( "digraph G {" );
      writer.WriteLine( "  truecolor=true;" );
      writer.WriteLine( "  rankdir=LR;" );
      foreach ( string node in nodes )
        writer.WriteLine( "  " + node + ";" );
      foreach ( string link in links )
        writer.WriteLine( "  " + link + ";" );
      writer.WriteLine( "}" );
      writer.Flush();
      writer.Close();
    }

    ProcessStartInfo dotStartInfo = new ProcessStartInfo( "dot.exe", string.Format( "-Tpng \"{0}\" -O", Path.GetFullPath( "output.dot" ) ) ) { CreateNoWindow = true, WorkingDirectory = "c:\\Program Files\\Graphviz2.26.3\\bin\\" };
    Process dot = Process.Start( dotStartInfo );
    dot.Start();
    dot.WaitForExit();

    Process.Start( "output.dot.png" ).Start();
  }

  public IEnumerable Main( EditorLib.IEditorWinApplication app )
  {
    //ProcessHero( app );
    DataBase.UndoRedoManager.Start( "Clear map" );
    AdvMap map = DataBase.Get<AdvMap>( DBID.FromString( "/Maps/Multiplayer/PFmap/pf.ADMP" ) ).Get();
    for ( int i = map.objects.Count - 1; i >= 0; --i )
    {
      if ( map.objects[i].gameObject.DBId.FileName.IndexOf( "/Terrain/", StringComparison.InvariantCultureIgnoreCase ) >= 0 ||
        map.objects[i].gameObject.DBId.FileName.IndexOf( "/Effects/Environment/", StringComparison.InvariantCultureIgnoreCase ) >= 0 ||
        map.objects[i].gameObject.DBId.FileName.IndexOf( "/Misc", StringComparison.InvariantCultureIgnoreCase ) >= 0 ||
        map.objects[i].gameObject.DBId.FileName.IndexOf( "/Wall", StringComparison.InvariantCultureIgnoreCase ) >= 0 )
        map.objects.RemoveAt( i );
    }
    DataBase.UndoRedoManager.Commit();
    yield return true;
  }
}
