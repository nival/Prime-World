using System.ComponentModel;
using System.Reflection;
using DBTypes;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace EditorPlugins.Editors.AnimGraph
{
  public class RandomNode : Node
  {
    public RandomNode(AnimGraphContext _context, AnGrMacronode _agNode)
      : base (_context, _agNode)
    {
      SubNodes = new OwnedReportingList<SubNode, RandomNode>(this, 1);
      SubNodes.OnListChanged += OnSubNodesListChanged;
      SubNodes.OnItemDeleting += OnSubNodeDeleting;
      SubNodes.OnItemInserted += OnSubNodeInserted;
    }

    #region SubNodes

    public OwnedReportingList<SubNode, RandomNode> SubNodes { get; private set; }

    private void OnSubNodeInserted(int _pos)
    {
      //это событие происходит в двух случаях, при создании рандом ноды и при добавлении сабноды через PE
      if (SupressEvents) return;

      SupressEvents = true;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Insert SubNode" ) )
      {
        SubNode snode = SubNodes[_pos];

        if( !snode.IsValid )//нода была добавлена из Properties Editor'а
        {
          snode = Context.CreateSubNode( "subnode" );
          //заменяем сабноду
          SubNodes[_pos] = snode;
        }

        // прилинкуемся к субноде
        AgLinkTo( snode );

        string nextNode;

        // скопируем ей линки с уже существующей субноды
        if( SubNodes.Count > 1 )
        {
          //если вставка осуществляется в нулевую позицию, то берем линки из первой сабноды
          int idx = ( _pos == 0 ) ? 1 : 0;
          
          foreach( var link in SubNodes[idx].Links )
          {
            var newLink = snode.LinkTo( link.ToNode );           
						newLink.AgLink.Assign(link.AgLink);
						#if DEBUG 
						ValidateLinks( link, newLink );
						#endif
          }

          nextNode = SubNodes[idx].NextNode;
        }
        else
        {
          //создадим линк на макроноду
          snode.LinkTo( this ).Duration = 0.1f;
          nextNode = this.Name;
        }

        snode.NextNode = nextNode;
      	snode.SurfaceSpeed = this.SurfaceSpeed;

        trans.Commit();
      }
			
      SupressEvents = false;
    }

    private void OnSubNodeDeleting(int _pos)
    {
      if (SupressEvents) return;

      SupressEvents = true;

      using(UndoRedoTransaction trans = new UndoRedoTransaction("Delete SubNode"))
      {
        //удаляем линки из RandomNode в сабноду
        for( int i = agNode.simpleTransactions.Count - 1; i >= 0; --i )
        {
          var agLink = agNode.simpleTransactions[i];

          if( agLink.targetNode == SubNodes[_pos].Name )
          {
            agNode.simpleTransactions.Remove( agLink );
          }
        }

        //удаляем сабноду
        Context.RemoveNode( SubNodes[_pos] );
        Context.SetInvalid();

        trans.Commit();
      }

      SupressEvents = false;
    }

    private void OnSubNodesListChanged()
    {
      UpdatedMajor();
    }

    private void LoadSubnodesInternal()
    {
      foreach (var link in agNode.simpleTransactions)
      {
        var subNode = Context.GetNode(link.targetNode) as SubNode;

        if (subNode != null)
          SubNodes.Add(subNode);
      }
    }

    /// <summary>
    /// Заполняет коллекцию сабнод и создает фейковые линки
    /// </summary>
    public void LoadSubnodes()
    {
      SupressEvents = true;

      //подгружаем сабноды
      LoadSubnodesInternal();

      //строим фейковые линки
      CreateFakeLinks();

      SupressEvents = false;
    }

    #endregion

    #region FakeLinks

    private void CreateFakeLinks()
    {
      if (SubNodes.Count > 0)
      {
        foreach (var link in SubNodes[0].Links)
        {
          if (link.ToNode != this)//не в свой диспатчер
          {
            //добавляем фейковые линки
            var fakeLink = new Link( null, new AnGrFlMultiTransaction( null, link.AgLink ), this, link.ToNode );
            fakeLink.PropertyChanged += OnLinkPropertyChanged;
            Links.Add(fakeLink);
          }
        }
      }
    }

    protected override void OnLinkInserted(int _pos)
    {
      if(SupressEvents) return;

      SupressEvents = true;

      using(UndoRedoTransaction trans = new UndoRedoTransaction("Add link"))
      {
        var link = Links[_pos];
        link.PropertyChanged += OnLinkPropertyChanged;

        foreach (var subnode in SubNodes)
        {
        	var newLink = subnode.LinkTo( link.ToNode );
        	#if DEBUG 
					ValidateLinks(link, newLink);
					#endif
        }

      	trans.Commit();
      }

      SupressEvents = false;
    }

#if DEBUG
  	private void ValidateLinks(Link link, Link newLink)
  	{
  		Log.Assert( newLink.AgLink.targetNode == link.AgLink.targetNode );
  		Log.Assert( newLink.AgLink.parameters.duration == link.AgLink.parameters.duration );
  		Log.Assert( newLink.AgLink.parameters.blending == link.AgLink.parameters.blending );
  		Log.Assert( newLink.AgLink.parameters.fromMin.value == link.AgLink.parameters.fromMin.value );
  		Log.Assert( newLink.AgLink.parameters.fromMax.value == link.AgLink.parameters.fromMax.value );
  	}
#endif

  	protected override void OnLinkDeleting(int _pos)
    {
      if (SupressEvents) return;

      SupressEvents = true;

      var fakeLink = Links[_pos];

      foreach (var subnode in SubNodes)
      {
        subnode.UnlinkFrom(fakeLink.ToNode);
      }

      SupressEvents = false;
    }

    private void OnLinkPropertyChanged(object _sender, PropertyChangedEventArgs _args)
    {
      var fakeLink = _sender as Link;

      if(fakeLink == null) return;

      object value = fakeLink.GetType().GetProperty(_args.PropertyName).GetValue(fakeLink, null);

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Change link properties" ) )
      {
        for ( int i = 0; i < SubNodes.Count; i++ )
        {
          foreach ( Link link in SubNodes[i].Links )
          {
            if ( link.ToNode == fakeLink.ToNode )
            {
              //обновляем свойства линка
              if ( _args.PropertyName == "MaxFrom" )
              {
                link.SetMaxFrom( fakeLink.GetMaxFrom() );
              }
              else if ( _args.PropertyName == "MinFrom" )
              {
                link.SetMinFrom( fakeLink.GetMinFrom() );
              }
              else
              {
                PropertyInfo pinfo = link.GetType().GetProperty( _args.PropertyName );
                pinfo.SetValue( link, value, null );
              }
            }
          }
        }

        trans.Commit(); 
      }
    }

    #endregion

    public override void LoadLinks()
    {
      //ничего не делаем, у нас фейковые линки и другая логика их формирования
    }

    public override Link LinkTo(Node _toNode)
    {
      var fakeLink = new AnGrFlMultiTransaction()
      {
        targetNode = _toNode.Name,
        probability = 0
      };

      fakeLink.parameters.fromMin.value = 0;
      fakeLink.parameters.fromMax.value = 1;
      fakeLink.parameters.duration = 1.0f / 10.0f;
      
      Links.Add( new Link( null, fakeLink, this, _toNode ) );
      return Links[Links.Count - 1];
    }

    public AnGrFlMultiTransaction GetSublink(string _subnodeName)
    {
      foreach (var agLink in agNode.simpleTransactions)
      {
        if(agLink.targetNode == _subnodeName)
        {
          return agLink;
        }
      }

      return null;
    }

    [Description("Default next node to play. Not applicable if this node has one or more links with probability > 0.")]
    [NextNodeSelected]
    public override string NextNode
    {
      get { return SubNodes[0].NextNode; }
      set
      {
        using(UndoRedoTransaction trans = new UndoRedoTransaction("Set NextNode"))
        {
          if( Context.GetNode( value ) is SubNode )
          {
            Log.AlwaysAssert( "Incorrect value passed to NextNode property. NextNode can't be SubNode." );
            return;
          }

          //выставляем NextNode у всех своих сабнод
          foreach( var subNode in SubNodes )
          {
            subNode.NextNode = value;
          }

          base.NextNode = SubNodes[0].NextNode;

          trans.Commit(); 
        }
      }
    }

    [Browsable( false )]
    public override float In 
    { 
      get { return SubNodes[0].In; }
      set { SubNodes[0].In = value; }
    }

    [Browsable( false )]
    public override float Out
    {
      get { return SubNodes[0].Out; }
      set { SubNodes[0].Out = value; }
    }

    public float BlendDuration
    {
      get
      {
				Link link = SubNodes[0].FindLinkTo(this);

				if ( link != null )
					return link.Duration;

        return -1;
      }
      set
      {
        using( UndoRedoTransaction trans = new UndoRedoTransaction( "Change duration" ) )
        {
          foreach( SubNode subNode in SubNodes )
          {
          	Link link = subNode.FindLinkTo(this);

						if ( link != null )
							link.Duration = value;
          }

          trans.Commit(); 
        }
      }
    }

    public override float SurfaceSpeed
    {
      get
      {
        return base.SurfaceSpeed;
      }
      set
      {
        base.SurfaceSpeed = value;

        foreach( SubNode subNode in SubNodes )
        {
          subNode.SurfaceSpeed = SurfaceSpeed;
        }
      }
    }

    protected override AnGrFlMultiTransaction InitAgLink(Node _toNode)
    {
      var result = new AnGrFlMultiTransaction
      {
        targetNode = _toNode.Name,
        parameters = InitAgLinkParams(_toNode),
        probability = 1
      };

      UpdatedMajor();

      return result;
    }

		//линк из макроноды в сабноду
    private AnGrFlTransaction InitAgLinkParams(Node _toNode)
    {
      var result = new AnGrFlTransaction();

      var subNode = _toNode as SubNode;

      if (subNode != null)
      {
        if (this.SubNodes.Contains(subNode)) // в свою сабноду
        {
          result.fromMin.value = 0;
          result.fromMax.value = 0.01f;
          result.duration = 1.0f / 999.0f;
        }
      }

      return result;
    }

    /// <summary>
    /// Обновляет анимацию в диспетчере. Это необходимо при изменении анимации в сабноде.
    /// </summary>
    public void UpdateAnimation()
    {
      agNode.sequenceName = SubNodes[0].Animation;
    }
  }
}
