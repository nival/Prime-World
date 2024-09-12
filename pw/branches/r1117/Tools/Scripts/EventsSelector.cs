/*
#about Add reference to System.Drawing to system references for script machine. Add new script for selecting possible events
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using libdb.DB;
using EditorLib.ObjectSelector;
using System.Collections;
using libdb.Diagnostics;
using EditorLib;
using EditorLib.Extensions;
using WeifenLuo.WinFormsUI.Docking;

public class EventsSelectorForm : DockContent
{
  #region Form's controls and initializers

  private System.Windows.Forms.SplitContainer splitContainer1;
  private System.Windows.Forms.ListBox listBoxItems;
  private System.Windows.Forms.ListBox listBoxEvents;
  private System.Windows.Forms.Label labelHint1;
  private System.Windows.Forms.Label labelHint2;
  private System.Windows.Forms.PropertyGrid propertyGrid;

  private void InitializeComponent()
  {
    this.splitContainer1 = new System.Windows.Forms.SplitContainer();
    this.listBoxItems = new System.Windows.Forms.ListBox();
    this.labelHint1 = new System.Windows.Forms.Label();
    this.listBoxEvents = new System.Windows.Forms.ListBox();
    this.labelHint2 = new System.Windows.Forms.Label();
    this.propertyGrid = new System.Windows.Forms.PropertyGrid();
    this.splitContainer1.Panel1.SuspendLayout();
    this.splitContainer1.Panel2.SuspendLayout();
    this.splitContainer1.SuspendLayout();
    this.SuspendLayout();
    // 
    // splitContainer1
    // 
    this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
    this.splitContainer1.Location = new System.Drawing.Point( 0, 0 );
    this.splitContainer1.Name = "splitContainer1";
    // 
    // splitContainer1.Panel1
    // 
    this.splitContainer1.Panel1.Controls.Add( this.listBoxItems );
    this.splitContainer1.Panel1.Controls.Add( this.labelHint1 );
    // 
    // splitContainer1.Panel2
    // 
    this.splitContainer1.Panel2.Controls.Add( this.listBoxEvents );
    this.splitContainer1.Panel2.Controls.Add( this.labelHint2 );
    this.splitContainer1.Size = new System.Drawing.Size( 468, 314 );
    this.splitContainer1.SplitterDistance = 232;
    this.splitContainer1.TabIndex = 8;
    // 
    // listBoxItems
    // 
    this.listBoxItems.Dock = System.Windows.Forms.DockStyle.Fill;
    this.listBoxItems.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
    this.listBoxItems.FormattingEnabled = true;
    this.listBoxItems.IntegralHeight = false;
    this.listBoxItems.Location = new System.Drawing.Point( 0, 0 );
    this.listBoxItems.Name = "listBoxItems";
    this.listBoxItems.Size = new System.Drawing.Size( 232, 297 );
    this.listBoxItems.TabIndex = 1;
    // 
    // labelHint1
    // 
    this.labelHint1.Dock = System.Windows.Forms.DockStyle.Bottom;
    this.labelHint1.Location = new System.Drawing.Point( 0, 297 );
    this.labelHint1.Name = "labelHint1";
    this.labelHint1.Size = new System.Drawing.Size( 232, 17 );
    this.labelHint1.TabIndex = 2;
    this.labelHint1.Text = "Hint: Double-click to add item";
    // 
    // listBoxEvents
    // 
    this.listBoxEvents.Dock = System.Windows.Forms.DockStyle.Fill;
    this.listBoxEvents.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawVariable;
    this.listBoxEvents.FormattingEnabled = true;
    this.listBoxEvents.IntegralHeight = false;
    this.listBoxEvents.Location = new System.Drawing.Point( 0, 0 );
    this.listBoxEvents.Name = "listBoxEvents";
    this.listBoxEvents.Size = new System.Drawing.Size( 232, 297 );
    this.listBoxEvents.TabIndex = 5;
    // 
    // labelHint2
    // 
    this.labelHint2.Dock = System.Windows.Forms.DockStyle.Bottom;
    this.labelHint2.Location = new System.Drawing.Point( 0, 297 );
    this.labelHint2.Name = "labelHint2";
    this.labelHint2.Size = new System.Drawing.Size( 232, 17 );
    this.labelHint2.TabIndex = 6;
    this.labelHint2.Text = "Hint: Double-click to remove item";
    // 
    // propertyGrid1
    // 
    this.propertyGrid.CommandsVisibleIfAvailable = false;
    this.propertyGrid.Dock = System.Windows.Forms.DockStyle.Right;
    this.propertyGrid.HelpVisible = false;
    this.propertyGrid.LineColor = System.Drawing.SystemColors.ControlDark;
    this.propertyGrid.Location = new System.Drawing.Point( 468, 0 );
    this.propertyGrid.Name = "propertyGrid1";
    this.propertyGrid.PropertySort = System.Windows.Forms.PropertySort.NoSort;
    this.propertyGrid.Size = new System.Drawing.Size( 170, 314 );
    this.propertyGrid.TabIndex = 0;
    this.propertyGrid.ToolbarVisible = false;
    // 
    // Temp
    // 
    this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
    this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
    this.Size = new System.Drawing.Size( 650, 350 );
    this.Controls.Add( this.splitContainer1 );
    this.Controls.Add( this.propertyGrid );
    this.MaximizeBox = false;
    this.MinimizeBox = false;
    this.Name = "Temp";
    this.ShowIcon = false;
    this.ShowInTaskbar = false;
    this.ShowHint = DockState.Float;
    this.Text = "Possible Events List";
    this.splitContainer1.Panel1.ResumeLayout( false );
    this.splitContainer1.Panel2.ResumeLayout( false );
    this.splitContainer1.ResumeLayout( false );
    this.ResumeLayout( false );
  }

  private void InitializeEvents()
  {
    this.listBoxItems.DrawItem += new DrawItemEventHandler( listBoxItems_DrawItem );
    this.listBoxItems.MeasureItem += new MeasureItemEventHandler( listBoxItems_MeasureItem );
    this.listBoxItems.DoubleClick += new EventHandler( listBoxItems_DoubleClick );

    this.listBoxEvents.DrawItem += new DrawItemEventHandler( listBoxItems_DrawItem );
    this.listBoxEvents.MeasureItem += new MeasureItemEventHandler( listBoxItems_MeasureItem );
    this.listBoxEvents.DoubleClick += new EventHandler( listBoxEvents_DoubleClick );
    this.listBoxEvents.SelectedIndexChanged += new EventHandler( listBoxEvents_SelectedIndexChanged );
  }

  void listBoxEvents_DoubleClick( object sender, EventArgs e )
  {
    HierarchyItem item = ( sender as ListBox ).SelectedItem as HierarchyItem;
    if ( item == null )
      return;

    DataBase.UndoRedoManager.Start( "Remove Sound Event" );
    item.Deactivate();
    listBoxEvents.Items.Remove( item );
    DataBase.UndoRedoManager.Commit();
  }

  void listBoxItems_DoubleClick( object sender, EventArgs e )
  {
    ListBox lb = ( sender as ListBox );
    HierarchyItem item = lb.SelectedItem as HierarchyItem;
    if ( item == null )
      return;

    string group = "test";
    if ( listBoxEvents.Items.Count > 0 )
    {
      HierarchyItem hi = (listBoxEvents.Items[0] as HierarchyItem);
      group = hi.Group;
    }

    DataBase.UndoRedoManager.Start( "Create Sound Event" );
    int index = listBoxEvents.Items.Add( item.Activate( group ) );
    DataBase.UndoRedoManager.Commit();
    listBoxEvents.SelectedIndex = index;
  }

  void listBoxEvents_SelectedIndexChanged( object sender, EventArgs e )
  {
    propertyGrid.SelectedObject = ( sender as ListBox ).SelectedItem;
  }

  void listBoxItems_MeasureItem( object sender, MeasureItemEventArgs e )
  {
    System.Drawing.Size size = TextRenderer.MeasureText( "Ig", listBoxItems.Font );
    e.ItemHeight = Math.Max( 17, size.Height );
  }

  void listBoxItems_DrawItem( object sender, DrawItemEventArgs e )
  {
    e.DrawBackground();
    if ( e.Index >= 0 )
      ( ( sender as ListBox ).Items[e.Index] as HierarchyItem ).Draw( application, e, sender == listBoxItems );
    e.DrawFocusRectangle();
  }

  #endregion

  private abstract class HierarchyItem
  {
    private readonly DBTypes.DBSoundSceneComponent sound = new DBTypes.DBSoundSceneComponent();

    protected HierarchyItem() { }
    protected HierarchyItem( DBTypes.DBSoundSceneComponent sound ) { this.sound = sound; }

    protected void Draw( IEditorWinApplication application, DrawItemEventArgs e, int imageIndex, string text, System.Drawing.FontStyle style, System.Drawing.Color color )
    {
      if ( ( e.State & DrawItemState.Selected ) == DrawItemState.Selected )
        color = System.Drawing.Color.FromKnownColor( System.Drawing.KnownColor.HighlightText );

      string label = text;
      if ( sound != null && ( !string.IsNullOrEmpty( sound.desc.groupName ) || !string.IsNullOrEmpty( sound.desc.eventName ) ) )
        label = string.Format( "{0} + {1} ({2})", sound.desc.groupName, sound.desc.eventName, text );
      e.Graphics.DrawImage( application.Application.Extensions.GetTypesImageList().Images[imageIndex], e.Bounds.Location );
      TextRenderer.DrawText( e.Graphics, label, style == System.Drawing.FontStyle.Regular ? e.Font : new System.Drawing.Font( e.Font, style ),
        new System.Drawing.Point( e.Bounds.Location.X + 17, e.Bounds.Location.Y + 1 ), color );
    }

    protected DBTypes.DBSoundSceneComponent Sound { get { return sound; } }

    public abstract void Draw( IEditorWinApplication application, DrawItemEventArgs e, bool source );
    public abstract HierarchyItem Activate( string category );
    public abstract void Deactivate();

    public string Group { get { return sound.desc.groupName; } set { sound.desc.groupName = value; } }
    public string Event { get { return sound.desc.eventName; } set { sound.desc.eventName = value; } }
  }

  private class HierarchyNode : HierarchyItem
  {
    private readonly DBTypes.DBAnimatedSceneComponent owner;
    private readonly DBTypes.AnGrMacronode node;
    private readonly DBTypes.AnimationSCEvent animationEvent = new DBTypes.AnimationSCEvent();

    public HierarchyNode( DBTypes.DBAnimatedSceneComponent owner, DBTypes.AnGrMacronode node, DBTypes.AnimationSCEvent animationEvent, DBTypes.DBSoundSceneComponent sound )
      : base( sound )
    {
      this.owner = owner;
      this.node = node;
      this.animationEvent = animationEvent;
    }

    public HierarchyNode( DBTypes.DBAnimatedSceneComponent owner, DBTypes.AnGrMacronode node )
    {
      this.owner = owner;
      this.node = node;
    }

    public override void Draw( IEditorWinApplication application, DrawItemEventArgs e, bool source )
    {
      ExtensionsManager extensions = application.Application.Extensions;
      Draw( application, e, extensions.GetTypeIconIndex( typeof( DBTypes.AnimGraphCreator ), true ), node.nodeName,
        node.nodeType == DBTypes.EAnGrNodeType.Normal ? System.Drawing.FontStyle.Regular : System.Drawing.FontStyle.Bold,
        System.Drawing.Color.Maroon );
    }

    public override HierarchyItem Activate( string category )
    {
      owner.attached.Add( new DBTypes.AttachedSceneComponent() );
      DBTypes.AttachedSceneComponent attached = owner.attached[owner.attached.Count - 1];
      attached.events = DataBase.Create<DBTypes.EnableDisableSCEvents>( DBID.FromDBID( owner.DBId, true ), new DBTypes.EnableDisableSCEvents() );

      attached.events.Get().enableEvents.Add( DataBase.Create<DBTypes.SCEvent>( DBID.FromDBID( owner.DBId, true ), new DBTypes.AnimationSCEvent() ) );
      DBTypes.AnimationSCEvent animationEvent = attached.events.Get().enableEvents[attached.events.Get().enableEvents.Count - 1].Get<DBTypes.AnimationSCEvent>();

      animationEvent.type = DBTypes.EAnimEventType.NodeEnter;
      animationEvent.animParam = 0.0f;
      animationEvent.name = node.nodeName;

      attached.component = DataBase.Create<DBTypes.DBSceneComponent>( DBID.FromDBID( owner.DBId, true ), new DBTypes.DBSoundSceneComponent() );
      DBTypes.DBSoundSceneComponent sound = attached.component.Get<DBTypes.DBSoundSceneComponent>();
      sound.desc.projectName = "PF";
      sound.desc.groupName = category;
      sound.desc.eventName = node.nodeName;
      sound.caption = "sound_" + node.nodeName;

      return new HierarchyNode( owner, node, animationEvent, sound );
    }

    public override void Deactivate()
    {
      DBTypes.AttachedSceneComponent remove = null;
      foreach ( DBTypes.AttachedSceneComponent attached in owner.attached )
      {
        if ( attached.component.Get() == Sound )
        {
          remove = attached;
          break;
        }
      }

      if ( remove != null )
        owner.attached.Remove( remove );
    }

    public string Node { get { return animationEvent.name; } set { animationEvent.name = value; } }
    public DBTypes.EAnimEventType EventType { get { return animationEvent.type; } set { animationEvent.type = value; } }
    public float Param { get { return animationEvent.animParam; } set { animationEvent.animParam = value; } }
  }

  private class HierarchyComponent : HierarchyItem
  {
    private readonly DBTypes.DBSceneComponent component;

    public HierarchyComponent( DBTypes.DBSceneComponent component, DBTypes.DBSoundSceneComponent sound )
      : base( sound )
    {
      this.component = component;
    }

    public HierarchyComponent( DBTypes.DBSceneComponent component )
    {
      this.component = component;
    }

    public override void Draw( IEditorWinApplication application, DrawItemEventArgs e, bool source )
    {
      ExtensionsManager extensions = application.Application.Extensions;

      string text = string.IsNullOrEmpty( component.caption ) ? component.DBId.FileName : component.caption;

      Draw( application, e, extensions.GetTypeIconIndex( component.GetType(), true ), text,
        !component.DBId.IsInlined ? System.Drawing.FontStyle.Italic : System.Drawing.FontStyle.Regular,
        System.Drawing.Color.Navy );
    }

    public override HierarchyItem Activate( string category )
    {
      component.attached.Add( new DBTypes.AttachedSceneComponent() );
      DBTypes.AttachedSceneComponent attached = component.attached[component.attached.Count - 1];
      attached.component = DataBase.Create<DBTypes.DBSceneComponent>( DBID.FromDBID( component.DBId, true ), new DBTypes.DBSoundSceneComponent() );
      DBTypes.DBSoundSceneComponent sound = attached.component.Get<DBTypes.DBSoundSceneComponent>();
      sound.desc.projectName = "PF";
      sound.desc.groupName = category;
      sound.desc.eventName = component.caption;
      sound.caption = "sound";

      return new HierarchyComponent( component, sound );
    }

    public override void Deactivate()
    {
      DBTypes.AttachedSceneComponent remove = null;
      foreach ( DBTypes.AttachedSceneComponent attached in component.attached )
      {
        if ( attached.component.Get() == Sound )
        {
          remove = attached;
          break;
        }
      }

      if ( remove != null )
        component.attached.Remove( remove );
    }
  }

  private class HierarchyAsk : HierarchyItem
  {
    private readonly DBTypes.BaseHero hero;
    private readonly DBTypes.ETeamID team;
    private readonly DBTypes.EAskSounds ask;
    private readonly bool use3d;

    public HierarchyAsk( DBTypes.BaseHero hero, DBTypes.ETeamID team, DBTypes.EAskSounds ask, bool use3d, DBTypes.DBSoundSceneComponent sound )
      : base( sound )
    {
      this.hero = hero;
      this.team = team;
      this.ask = ask;
      this.use3d = use3d;
    }

    public HierarchyAsk( DBTypes.BaseHero hero, DBTypes.ETeamID team, DBTypes.EAskSounds ask, bool use3d )
    {
      this.hero = hero;
      this.team = team;
      this.ask = ask;
      this.use3d = use3d;
    }

    public override void Draw( IEditorWinApplication application, DrawItemEventArgs e, bool source )
    {
      ExtensionsManager extensions = application.Application.Extensions;

      string text = team.ToString().ToLower() + " " + ask.ToString().ToLower();
      if ( use3d )
        text += " (3D)";

      Draw( application, e, extensions.GetTypeIconIndex( typeof( DBTypes.DBSoundSceneComponent ), true ), text,
        System.Drawing.FontStyle.Regular, team == DBTypes.ETeamID.A ? System.Drawing.Color.Navy : System.Drawing.Color.Maroon );
    }

    public override HierarchyItem Activate( string category )
    {
      DBTypes.DBSoundSceneComponent sound;
      if ( use3d )
			{
        hero.askLists[(int)team].sounds3d[(int)ask] = DataBase.Create<DBTypes.DBSoundSceneComponent>( DBID.FromDBID( hero.DBId, true ), new DBTypes.DBSoundSceneComponent() );
				sound = hero.askLists[(int)team].sounds3d[(int)ask].Get<DBTypes.DBSoundSceneComponent>();
			}
      else
			{
        hero.askLists[(int)team].sounds[(int)ask] = DataBase.Create<DBTypes.DBSoundSceneComponent>( DBID.FromDBID( hero.DBId, true ), new DBTypes.DBSoundSceneComponent() );
				sound = hero.askLists[(int)team].sounds[(int)ask].Get<DBTypes.DBSoundSceneComponent>();
			}

      sound.desc.projectName = "PF";
      sound.desc.groupName = category;
      sound.desc.eventName = ( team.ToString() + "_" + ask.ToString() ).ToLower();
      sound.caption = "sound";
			if ( use3d )
			{
				sound.desc.eventName += "_3d";
				sound.caption += "_3d";
			}
      return new HierarchyAsk( hero, team, ask, use3d, sound );
    }

    public override void Deactivate()
    {
      if ( use3d )
        hero.askLists[(int)team].sounds3d[(int)ask] = new DBPtr<DBTypes.DBSoundSceneComponent>( null );
      else
        hero.askLists[(int)team].sounds[(int)ask] = new DBPtr<DBTypes.DBSoundSceneComponent>( null );
    }
  }

  private class HierarchySkinAsk : HierarchyItem
  {
    private readonly DBTypes.HeroSkin heroSkin;
    private readonly DBTypes.EAskSounds ask;
    private readonly bool use3d;

    public HierarchySkinAsk( DBTypes.HeroSkin heroSkin, DBTypes.EAskSounds ask, bool use3d, DBTypes.DBSoundSceneComponent sound )
      : base( sound )
    {
      this.heroSkin = heroSkin;
      this.ask = ask;
      this.use3d = use3d;
    }

    public HierarchySkinAsk( DBTypes.HeroSkin heroSkin, DBTypes.EAskSounds ask, bool use3d )
    {
      this.heroSkin = heroSkin;
      this.ask = ask;
      this.use3d = use3d;
    }

    public override void Draw( IEditorWinApplication application, DrawItemEventArgs e, bool source )
    {
      ExtensionsManager extensions = application.Application.Extensions;

      string text = ask.ToString().ToLower();
      if ( use3d )
        text += " (3D)";

      Draw( application, e, extensions.GetTypeIconIndex( typeof( DBTypes.DBSoundSceneComponent ), true ), text,
        System.Drawing.FontStyle.Regular, System.Drawing.Color.CadetBlue );
    }

    public override HierarchyItem Activate( string category )
    {
      DBTypes.DBSoundSceneComponent sound;
      if ( use3d )
      {
        heroSkin.askList.Get().asks.sounds3d[(int)ask] = DataBase.Create<DBTypes.DBSoundSceneComponent>( DBID.FromDBID( heroSkin.DBId, true ), new DBTypes.DBSoundSceneComponent() );
        sound = heroSkin.askList.Get().asks.sounds3d[(int)ask].Get<DBTypes.DBSoundSceneComponent>();
      }
      else
      {
        heroSkin.askList.Get().asks.sounds[(int)ask] = DataBase.Create<DBTypes.DBSoundSceneComponent>( DBID.FromDBID( heroSkin.DBId, true ), new DBTypes.DBSoundSceneComponent() );
        sound = heroSkin.askList.Get().asks.sounds[(int)ask].Get<DBTypes.DBSoundSceneComponent>();
      }

      sound.desc.projectName = "PF";
      sound.desc.groupName = category;
      sound.desc.eventName = ( ask.ToString() ).ToLower();
      sound.caption = "sound";
      if ( use3d )
      {
        sound.desc.eventName += "_3d";
        sound.caption += "_3d";
      }
      return new HierarchySkinAsk( heroSkin, ask, use3d, sound );
    }

    public override void Deactivate()
    {
      if ( use3d )
        heroSkin.askList.Get().asks.sounds3d[(int)ask] = new DBPtr<DBTypes.DBSoundSceneComponent>( null );
      else
        heroSkin.askList.Get().asks.sounds[(int)ask] = new DBPtr<DBTypes.DBSoundSceneComponent>( null );
    }
  }

  private readonly IEditorWinApplication application = null;

  private void TryProcessAnimGraph( DBTypes.DBSceneComponent sceneComponent )
  {
    Dictionary<string, DBTypes.AnGrMacronode> nodes = new Dictionary<string, DBTypes.AnGrMacronode>();

    if ( !TypeUtils.IsSubclassOf( sceneComponent.GetType(), typeof( DBTypes.DBAnimatedSceneComponent ) ) )
      return;

    DBTypes.DBAnimatedSceneComponent animSceneComponent = sceneComponent as DBTypes.DBAnimatedSceneComponent;
    if ( animSceneComponent.animGraph == null || animSceneComponent.animGraph.Get() == null )
      return;

    DBTypes.AnimGraphCreator ag = animSceneComponent.animGraph.Get() as DBTypes.AnimGraphCreator;
    foreach ( DBTypes.AnGrMacronode node in ag.macroNodes )
    {
      if ( node.nodeType == DBTypes.EAnGrNodeType.Normal || node.nodeType == DBTypes.EAnGrNodeType.SubNode )
      {
        listBoxItems.Items.Add( new HierarchyNode( animSceneComponent, node ) );
        nodes.Add( node.nodeName, node );
      }
    }

    foreach ( DBTypes.AttachedSceneComponent attached in animSceneComponent.attached )
    {
      if ( attached.component != null && attached.component.Get() != null && attached.component.Get() is DBTypes.DBSoundSceneComponent &&
        attached.events != null && attached.events.Get() != null && attached.events.Get().enableEvents.Count == 1 && attached.events.Get().enableEvents[0].Get() is DBTypes.AnimationSCEvent )
      {
        DBTypes.AnimationSCEvent animatedEvent = attached.events.Get().enableEvents[0].Get<DBTypes.AnimationSCEvent>();
		if ( !nodes.ContainsKey( animatedEvent.name ) )
		  Log.TraceWarning( "Node (\"{0}\") not found", animatedEvent.name );
		else
		  listBoxEvents.Items.Add( new HierarchyNode( animSceneComponent, nodes[animatedEvent.name], animatedEvent, attached.component.Get<DBTypes.DBSoundSceneComponent>() ) );
      }
    }
  }

  private void ProcessHierarcy( DBTypes.DBSceneComponent owner, IEnumerable<DBTypes.AttachedSceneComponent> sceneComponents )
  {
    foreach ( DBTypes.AttachedSceneComponent sceneComponent in sceneComponents )
    {
      if ( sceneComponent.component == null || sceneComponent.component.Get() == null )
        continue;

      if ( sceneComponent.component.Get() is DBTypes.DBSoundSceneComponent )
      {
        if ( owner != null )
          listBoxEvents.Items.Add( new HierarchyComponent( owner, sceneComponent.component.Get<DBTypes.DBSoundSceneComponent>() ) );
      }
      else
      {
        listBoxItems.Items.Add( new HierarchyComponent( sceneComponent.component.Get() ) );
        if ( sceneComponent.component.DBId.IsInlined )
        {
          ProcessHierarcy( sceneComponent.component.Get(), sceneComponent.component.Get().attached );
        }
      }
    }
  }

  private void ProcessHero( DBTypes.BaseHero hero )
  {
    foreach ( DBTypes.ETeamID team in Enum.GetValues( typeof( DBTypes.ETeamID ) ) )
    {
      foreach ( DBTypes.EAskSounds ask in Enum.GetValues( typeof( DBTypes.EAskSounds ) ) )
      {
        listBoxItems.Items.Add( new HierarchyAsk( hero, team, ask, false ) );
        if ( hero.askLists[(int)team].sounds[(int)ask] != null && hero.askLists[(int)team].sounds[(int)ask].Get() != null )
          listBoxEvents.Items.Add( new HierarchyAsk( hero, team, ask, false, hero.askLists[(int)team].sounds[(int)ask].Get() ) );
      }

      foreach ( DBTypes.EAskSounds ask in Enum.GetValues( typeof( DBTypes.EAskSounds ) ) )
      {
        listBoxItems.Items.Add( new HierarchyAsk( hero, team, ask, true ) );
        if ( hero.askLists[(int)team].sounds[(int)ask] != null && hero.askLists[(int)team].sounds3d[(int)ask].Get() != null )
          listBoxEvents.Items.Add( new HierarchyAsk( hero, team, ask, true, hero.askLists[(int)team].sounds3d[(int)ask].Get() ) );
      }
    }
  }

  private void ProcessHeroSkin( DBTypes.HeroSkin heroSkin )
  {
    foreach ( DBTypes.EAskSounds ask in Enum.GetValues( typeof( DBTypes.EAskSounds ) ) )
    {
      listBoxItems.Items.Add( new HierarchySkinAsk( heroSkin, ask, false ) );
      if ( heroSkin.askList != null && heroSkin.askList.Get().asks.sounds[(int)ask] != null && heroSkin.askList.Get().asks.sounds[(int)ask].Get() != null )
        listBoxEvents.Items.Add( new HierarchySkinAsk( heroSkin, ask, false, heroSkin.askList.Get().asks.sounds[(int)ask].Get() ) );
    }

    foreach ( DBTypes.EAskSounds ask in Enum.GetValues( typeof( DBTypes.EAskSounds ) ) )
    {
      listBoxItems.Items.Add( new HierarchySkinAsk( heroSkin, ask, true ) );
      if ( heroSkin.askList != null && heroSkin.askList.Get().asks.sounds3d[(int)ask] != null && heroSkin.askList.Get().asks.sounds3d[(int)ask].Get() != null )
        listBoxEvents.Items.Add( new HierarchySkinAsk( heroSkin, ask, true, heroSkin.askList.Get().asks.sounds3d[(int)ask].Get() ) );
    }
  }

  public EventsSelectorForm( IEditorWinApplication application, DBTypes.DBSceneObject sceneObject )
  {
    this.application = application;
    InitializeComponent();
    InitializeEvents();
    Text = Text + ": " + sceneObject.DBId.ToString();

    if ( sceneObject.attached.Count == 1 )
      TryProcessAnimGraph( sceneObject.attached[0].component.Get() );

    ProcessHierarcy( null, sceneObject.attached );
  }

  public EventsSelectorForm( IEditorWinApplication application, DBTypes.DBSceneComponent sceneComponent )
  {
    this.application = application;
    InitializeComponent();
    InitializeEvents();
    Text = Text + ": " + sceneComponent.DBId.ToString();

    TryProcessAnimGraph( sceneComponent );
    listBoxItems.Items.Add( new HierarchyComponent( sceneComponent ) );
    ProcessHierarcy( sceneComponent, sceneComponent.attached );
  }

  public EventsSelectorForm( IEditorWinApplication application, DBTypes.BaseHero hero )
  {
    this.application = application;
    InitializeComponent();
    InitializeEvents();
    Text = Text + ": " + hero.DBId.ToString();

    ProcessHero( hero );
  }

  public EventsSelectorForm( IEditorWinApplication application, DBTypes.HeroSkin heroSkin )
  {
    this.application = application;
    InitializeComponent();
    InitializeEvents();
    Text = Text + ": " + heroSkin.DBId.ToString();

    ProcessHeroSkin( heroSkin );
  }
}

public class EventsSelector
{
  public IEnumerable Main( IEditorWinApplication app )
  {
    ObjectSelectorForm selector = new ObjectSelectorForm();
    //selector.SetPossibleTypes( typeof( DBTypes.AnimGraphCreator ) );
    if ( selector.ShowDialog() == DialogResult.OK )
    {
      DBPtr<DBResource> resource = DataBase.Get<DBResource>( selector.SelectedObject );
      if ( TypeUtils.IsSubclassOf( resource.Get().GetType(), typeof( DBTypes.DBSceneComponent ) ) )
      {
        EventsSelectorForm form = new EventsSelectorForm( app, resource.Get() as DBTypes.DBSceneComponent );
        app.Panels.Add( form );
        form.Size = new System.Drawing.Size( 650, 350 );
      }
      else if ( TypeUtils.IsSubclassOf( resource.Get().GetType(), typeof( DBTypes.DBSceneObject ) ) )
      {
        EventsSelectorForm form = new EventsSelectorForm( app, resource.Get() as DBTypes.DBSceneObject );
        app.Panels.Add( form );
        form.Size = new System.Drawing.Size( 650, 350 );
      }
      else if ( TypeUtils.IsSubclassOf( resource.Get().GetType(), typeof( DBTypes.BaseHero ) ) )
      {
        EventsSelectorForm form = new EventsSelectorForm( app, resource.Get() as DBTypes.BaseHero );
        app.Panels.Add( form );
        form.Size = new System.Drawing.Size( 650, 350 );
      }
      else if ( TypeUtils.IsSubclassOf( resource.Get().GetType(), typeof( DBTypes.HeroSkin ) ) )
      {
        EventsSelectorForm form = new EventsSelectorForm( app, resource.Get() as DBTypes.HeroSkin );
        app.Panels.Add( form );
        form.Size = new System.Drawing.Size( 650, 350 );
      }
      else
        Log.TraceWarning( "Invalid type (\"{0}\") of selected object", resource.Get().GetType() );
    }

    yield return true;
  }
}
