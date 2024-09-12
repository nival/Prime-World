using System.ComponentModel;
using DBTypes;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace EditorPlugins.Editors.AnimGraph
{
  [IndexField("Name")]
  public abstract class Node
  {
    protected readonly AnGrMacronode agNode = null;//Представление ноды в базе

    protected AnimInfo animInfo = null;
    private int playIndex = -1;

    [Browsable(false)]
    public int PlayIndex
    {
      get { return playIndex; }
      set { playIndex = value; }
    }

    [Browsable(false), HideInOutliner]
    public AnimGraphContext Context { get; set; }
    
    [Browsable(false)]
    public int AnGrNodeIndex { get { return Context.animGraphCreator.macroNodes.IndexOf(agNode); } }
    
    [Browsable(false)]
    public int X { get { return agNode.posX; } set { agNode.posX = value; } }
    
    [Browsable(false)]
    public int Y { get { return agNode.posY; } set { agNode.posY = value; } }
    
    [Description("Unique node name")]
    public string Name
    {
      get { return agNode.nodeName; }
      set
      {
        // проверим уникальность имени
        if (Context.GetNode(value) != null)
        {
          Log.TraceError("Node with name \"" + value + "\" already exsists in this graph.");
          return;
        }

        using(UndoRedoTransaction trans = new UndoRedoTransaction("Rename node"))
        {
          string old = agNode.nodeName;
        
          agNode.nodeName = value;
        
          OnNameChanged(old);

          trans.Commit(); 
        }

        UpdatedMajor();
      }
    }

    private void OnNameChanged(string _oldName)
    {
      // изменим все ссылки на это имя 
      foreach (var agItem in Context.animGraphCreator.macroNodes)
      {
        if (agItem.nextNode == _oldName)
          agItem.nextNode = this.Name;

        foreach (var link in agItem.simpleTransactions)
        {
          if (link.targetNode == _oldName)
            link.targetNode = this.Name;
        }
      }

      //сообщим контексту, что мы изменили имя ноды
      Context.FixNodeName(_oldName);
    }

    [Description("Default next node to play. Not applicable if this node has one or more links with probability > 0.")]
    [NextNodeSelected]
    public virtual string NextNode
    {
      get { return agNode.nextNode; }
      set
      {
        if (Name == value || HasLinkTo(value))
        {
          agNode.nextNode = value;
          UpdatedMinor();
        }
        else
          Log.TraceError("Incorrect value passed to NextNode property" +
                         " of '{0}' node. Current node not linked to '{0}'",
                         Name, value);
      }
    }

    [Description("Node is looped when its NextNode == its Name")]
    public virtual bool Looped
    {
      get { return NextNode == Name; }
      set
      {
        if(Looped == value) return;

        if (value)
        {
          NextNode = Name;
        }
        else
        {
          // Если нода не имеет связей она может быть только зацикленной
          if(Links.Count == 0)
          {
            Log.TraceError("Node must be looped while it has no outgoing links");
            return;
          }
          
          // если исходящие связи есть, то nextNode становится первая попавшаяся связанная нода
          NextNode = Links[0].ToNode.Name;
        }
      }
    }

    [Description( "Node movement speed (float value)" )]
    public virtual float SurfaceSpeed
    {
      get { return -agNode.surfSpeedY; }
      set
      {
        agNode.surfSpeedY = -value;
        UpdatedMinor();
      }
    }

    protected OutlinerReadOnlyList<Link> links = new OutlinerReadOnlyList<Link>();

    [ReadOnly(true)]
    public virtual OutlinerReadOnlyList<Link> Links { get { return links; } }

    protected AnimInfo FindAnimInfo(string _value)
    {
      foreach (var item in Context.animInfos)
      {
        if(item.animName == _value) return item;
      }
      return null;
    }

    [Browsable(false), ReadOnly(true)]
    public int FramesCount
    {
      get { return animInfo.animFrames; }
    }

    public abstract float In { get; set; }
    public abstract float Out { get; set; }

    [Browsable(false)]
    public bool SupressEvents { get; set; }

    #region Creation and initialization methods

    protected Node()
    {
      InitLinks();
    }

    protected Node(AnimGraphContext _context, AnGrMacronode _agNode)
    {
      Context = _context;
      agNode = _agNode;
      InitLinks();

      // Добавим сиквенсы
      animInfo = FindAnimInfo(agNode.sequenceName);
    }

    private void InitLinks()
    {
      links.OnItemInserted += OnLinkInserted;
      links.OnItemDeleting += OnLinkDeleting;
      links.OnListChanged += OnLinksChanged;
    }

    #endregion

    #region Event Handlers

    // Отправляет изменения данной ноды контроллеру, не перезагружая его целиком
    protected void UpdatedMinor()
    {
      Context.Controller.SetNodeInfo(AnGrNodeIndex, agNode);
    }

    // сбрасывает контроллер целиком, запрашивая его перестройку
    protected void UpdatedMajor()
    {
      if (SupressEvents)
        return;
      Context.SetInvalid();
    }

    public void OnMoved(int _x, int _y)
    {
      agNode.posX = _x;
      agNode.posY = _y;
      UpdatedMinor();
    }

    #endregion

    protected virtual void OnLinkInserted(int _pos)
    {
    }

    protected virtual void OnLinkDeleting(int _pos)
    {
      var link = Links[_pos];

      using(UndoRedoTransaction trans = new UndoRedoTransaction("Remove link"))
      {
        agNode.simpleTransactions.Remove( link.AgLink );

        if( NextNode == link.ToNode.Name )
        {
          int idx = ( _pos == 0 ) ? 1 : 0;//линк еще не удален, нам надо найти индекс линка, который останется
          NextNode = Links.Count > 1 ? Links[idx].ToNode.Name : Name;
        }

        //if (!Looped)//если нода не зацикленная надо пофиксить defaultNextNode
        //{
        //  int idx = (_pos == 0) ? 1 : 0;//линк еще не удален, нам надо найти индекс линка, который останется
        //  NextNode = Links.Count > 1 ? Links[idx].ToNode.Name : Name;
        //}

        trans.Commit(); 
      }

      UpdatedMajor();
    }

    protected virtual void OnLinksChanged()
    {
    }

    /// <summary>
    /// Создает представление линка в БД
    /// </summary>
    /// <param name="_toNode">Нода, к которой надо прилинковаться</param>
    /// <returns></returns>
    protected AnGrFlMultiTransaction AgLinkTo(Node _toNode)
    {
      var result = InitAgLink(_toNode);

      // обновить ссылку на объект надо в связи с особенностями базы
      agNode.simpleTransactions.Add(result);
      result = agNode.simpleTransactions[agNode.simpleTransactions.Count - 1];

      UpdatedMajor();

      return result;
    }

    protected abstract AnGrFlMultiTransaction InitAgLink(Node _toNode);

    public virtual void LoadLinks()
    {
      foreach (var link in agNode.simpleTransactions)
        Links.Add(new Link(Context, link, this, Context.GetNode(link.targetNode)));
    }

    protected bool HasLinkTo(string _nodeName)
    {
      foreach (var link in Links)
      {
        if (link.ToNode.Name == _nodeName)
          return true;
      }

      return false;
    }

    public virtual Link LinkTo(Node _toNode)
    {
      Links.Add(new Link(Context, AgLinkTo(_toNode), this, _toNode));
      return Links[Links.Count - 1];
    }

    /// <summary>
    /// Удаляем линк на ноду из Links, если в Links есть линк на указанную ноду
    /// </summary>
    /// <param name="_node">Нода, линк на которую надо удалить</param>
    public void UnlinkFrom(Node _node)
    {
      for (int i = Links.Count - 1; i >= 0; --i)
      {
        if (Links[i].ToNode == _node)
        {
          Links.RemoveAt(i);
        }
      }
    }

		public Link FindLinkTo(Node _node)
		{
			foreach ( Link link in Links )
			{
				if ( link.ToNode == _node )
					return link;
			}

			return null;
		}

  }
}
