using System.Collections.Generic;
using DBTypes;
using EditorLib;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace EditorPlugins.Editors.AnimGraph
{
  public class AnimGraphContext
  {
    //ноды графа
    private readonly Dictionary<string, Node> nodes = new Dictionary<string, Node>();

    public IAgController Controller { get; private set; }
    public AnimGraphCreator animGraphCreator = null;
    public List<AnimInfo> animInfos;
    public bool RecreateNeeded = false;

  	public static bool MeasureInFrames 
		{ 
			get
			{
				AnimGraphPanelConfig config = EditorCommonApplication.ApplicationSingleton.Settings.Get<AnimGraphPanelConfig>();
				return config.MeasureInFrames;
			}
		}

  	public const float FramesPerSecond = 30.0f;

    public DBID AGCDbid = null;

    //класс можно создавать только через CreateContext
    private AnimGraphContext()
    {
    }

    /// <summary>
    /// Создает экземпляр контекста по контролееру, если это возможно, иначе возвращает null
    /// </summary>
    public static AnimGraphContext CreateContext(IAgController _controller)
    {
      if (_controller == null)
        return null;

      var context = new AnimGraphContext
      {
        Controller = _controller,
        AGCDbid = _controller.DbId,
        animGraphCreator = DataBase.Get<AnimGraphCreator>(_controller.DbId)
      };

      // нет графа в базе - нет контекста, это просто анимация без графа
      if (context.animGraphCreator == null)
        return null;

      // берем список анимаций
      context.animInfos = (List<AnimInfo>)_controller.GetAnimInfos();

      // берем ноды
      foreach (var node in context.animGraphCreator.macroNodes)
      {
        context.AddNode(ConvertToNode(context, node));
      }

      // строим линки
      foreach (var node in context.ListNodes())
        node.LoadLinks();

      // заполняем коллекции subnodes у multi-нод
			foreach ( RandomNode node in context.ListNodes( n => n is RandomNode ) )
      {
				node.LoadSubnodes();
      }

      return context;
    }

    public void SetInvalid()
    {     
      Controller.SetInvalid();  
    }

    public bool IsValid
    {
      get { return Controller.IsValid(); }
    }

    public IEnumerable<Node> ListNodes()
    {
      return nodes.Values;
    }

		public IEnumerable<Node> ListWithoutSubnodes( )
		{
			return ListNodes(node => !(node is SubNode));
		}

		/// <summary>
		/// Возвращает ноды, удволетворяющие условию _match
		/// </summary>
		public IEnumerable<Node> ListNodes(System.Predicate<Node> _match)
		{
			foreach(var node in nodes.Values)
			{
				if ( _match( node ) )
					yield return node;
			}
		}

    public Node GetNode(string _nodeName)
    {
      Node result = null;

      if (_nodeName != null)
        nodes.TryGetValue(_nodeName, out result);

      return result;
    }

    private void AddNode(Node _node)
    {
      nodes.Add(_node.Name, _node);
    }

    public bool RemoveNode(Node _node)
    {
      if (_node == null || _node.Context != this) return false;

      bool result;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Remove Node" ) )
      {
        _node.SupressEvents = true;

        //удаляем все линки ссылающиеся на нашу ноду
        foreach( var node in ListNodes() )
        {
          node.UnlinkFrom( _node );
        }

        //удаляем из БД (это надо сделать до удаления сабнод, чтобы из БД удалились линки из рандом ноды в сабноду)
        animGraphCreator.macroNodes.RemoveAt( _node.AnGrNodeIndex );

        //удаляем сабноды
        if( _node is RandomNode )
        {
          foreach( var subNode in ( _node as RandomNode ).SubNodes )
          {
            RemoveNode( subNode );
          }
        }

        result = nodes.Remove( _node.Name );
        _node.SupressEvents = false;

        trans.Commit();
      }

      return result;
    }

    /// <summary>
    /// Создает ноду и записывает ее в базу
    /// </summary>
    /// <param name="_name">Имя ноды</param>
    /// <param name="_nodeType">Тип ноды</param>
    /// <param name="_x">координата</param>
    /// <param name="_y">координата</param>
    /// <returns>Возвращает созданную ноду</returns>
    private Node CreateNewNode(string _name, EAnGrNodeType _nodeType, int _x, int _y)
    {
      var agNodeTmp = CreateNodeInDb(_name, _nodeType, _x, _y);

      Node result = ConvertToNode(this, agNodeTmp);

      AddNode(result);
      return result;
    }

    /// <summary>
    /// Создает Normal ноду и записывает ее в базу
    /// </summary>
    /// <param name="_name">Имя ноды</param>
    /// <param name="_x">координата</param>
    /// <param name="_y">координата</param>
    /// <returns>Возвращает созданную ноду</returns>
    public NormalNode CreateNormalNode(string _name, int _x, int _y)
    {
      NormalNode result;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Create Normal Node" ) )
      {
        result = CreateNewNode( _name, EAnGrNodeType.Normal, _x, _y ) as NormalNode;
        trans.Commit();
      }
      
      SetInvalid();

      return result;
    }

    /// <summary>
    /// Создает Random ноду и записывает ее в базу
    /// </summary>
    /// <param name="_name">Имя ноды</param>
    /// <param name="_x">координата</param>
    /// <param name="_y">координата</param>
    /// <returns>Возвращает созданную ноду</returns>
    public RandomNode CreateRandomNode(string _name, int _x, int _y)
    {
      RandomNode result;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Create Random Node" ) )
      {
        result = CreateNewNode( _name, EAnGrNodeType.Dispatcher, _x, _y ) as RandomNode;

        result.SubNodes.Add( CreateSubNode( "subnode" ) );
        result.Looped = true;
        trans.Commit();
      }

      SetInvalid();

      return result;
    }

    /// <summary>
    /// Создает Sub ноду и записывает ее в базу
    /// </summary>
    /// <param name="_name">Имя ноды</param>
    /// <returns>Возвращает созданную ноду</returns>
    public SubNode CreateSubNode(string _name)
    {
      SubNode result;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Create SubNode" ) )
      {
        result = CreateNewNode( _name, EAnGrNodeType.SubNode, 0, 0 ) as SubNode;
        trans.Commit();
      }

      SetInvalid();

      return result;
    }

    /// <summary>
    /// Генерирует валидное (уникальное) имя для новой ноды
    /// </summary>
    /// <param name="_name">имя ноды</param>
    /// <returns>уникальное имя ноды</returns>
    private string GenerateNodeName(string _name)
    {
      string result = _name ?? "new_node";

      for(int i = 0; nodes.ContainsKey(result); ++i)
      {
        result = _name + i;
      }

      return result;
    }

    /// <summary>
    /// Создает в базе новую ноду
    /// </summary>
    /// <param name="_name">Имя ноды</param>
    /// <param name="_nodeType">Тип ноды: Normal, Dispatcher, SubNode</param>
    /// <param name="_x">координата</param>
    /// <param name="_y">координата</param>
    /// <returns>Возвращает созданную ноду</returns>
    private AnGrMacronode CreateNodeInDb(string _name, EAnGrNodeType _nodeType, int _x, int _y)
    {
      _name = GenerateNodeName(_name);

      var agNodeTmp = new AnGrMacronode();
      agNodeTmp.nodeName = _name;
      agNodeTmp.nextNode = _name;
      agNodeTmp.posX = _x;
      agNodeTmp.posY = _y;
      agNodeTmp.nodeType = _nodeType;
      agNodeTmp.sequenceName = animInfos[0].animName;
      agNodeTmp.startPar.value = 0.0f;
      agNodeTmp.stopPar.value = 1.0f;
      agNodeTmp.speed.value = 1.0f;

      animGraphCreator.macroNodes.Add(agNodeTmp);

      // База при добавлении создает новый объект, поэтому забираем его таким извращенным способом, а не берем нами созданный
      return animGraphCreator.macroNodes[animGraphCreator.macroNodes.Count - 1];
    }
    
    /// <summary>
    /// Создает ноду графа из представления ноды в БД
    /// </summary>
    /// <param name="_context">Контекст</param>
    /// <param name="_node">Представление ноды в БД</param>
    /// <returns>Представление ноды в графе</returns>
    private static Node ConvertToNode(AnimGraphContext _context, AnGrMacronode _node)
    {
      Node result = null;

      switch (_node.nodeType)
      {
        case EAnGrNodeType.Dispatcher:
          result = new RandomNode(_context, _node);
          break;

        case EAnGrNodeType.Normal:
          result = new NormalNode(_context, _node);
          break;

        case EAnGrNodeType.SubNode:
          result = new SubNode(_context, _node);
          break;

        default:
          Log.AlwaysAssert("Not supported node type {0}", _node.nodeType);
          break;
      }

      return result;
    }

    public void FixNodeName(string _oldName)
    {
      var node = GetNode(_oldName);

      if(node != null)
      {
        nodes.Remove(_oldName);
        nodes.Add(node.Name, node);
      }
    }

    public void ToRandomNode(NormalNode _normalNode)
    {
      if(_normalNode == null)
        return;

      if(_normalNode is SubNode)
      {
        Log.TraceError("Cant't convert node '{0}' from SubNode to RandomNode", _normalNode.Name);
        return;
      }
      
      AnimGraphCreator animGraph = _normalNode.Context.animGraphCreator;
      AnGrMacronode nodeToConvert = animGraph.macroNodes[_normalNode.AnGrNodeIndex];

      if (nodeToConvert == null || nodeToConvert.nodeType != EAnGrNodeType.Normal)
        return;
      
      using( UndoRedoTransaction trans = new UndoRedoTransaction( string.Format("Convert '{0}' to macronode", _normalNode.Name) ) )
      {
        AnGrMacronode newNode = new AnGrMacronode();

        newNode.nodeType = EAnGrNodeType.Dispatcher;
        nodeToConvert.nodeType = EAnGrNodeType.SubNode;

        newNode.nodeName = nodeToConvert.nodeName;
        nodeToConvert.nodeName = nodeToConvert.nodeName + "1";

        newNode.posX = nodeToConvert.posX;
        newNode.posY = nodeToConvert.posY;

        newNode.speed = new AnGrFormula();
        newNode.speed.value = 1;

        newNode.nextNode = nodeToConvert.nodeName;
        nodeToConvert.nextNode = newNode.nodeName;

        newNode.sequenceName = nodeToConvert.sequenceName;
        newNode.startPar = nodeToConvert.startPar;
        newNode.stopPar = nodeToConvert.stopPar;
        newNode.speed = nodeToConvert.speed;

        AnGrFlMultiTransaction transaction = new AnGrFlMultiTransaction();
        transaction.targetNode = nodeToConvert.nodeName;
        transaction.probability = 1;

        AnGrFlTransaction param = new AnGrFlTransaction();
        param.blending = EAnGrTransactionUpdate.PoseToAnim;
        param.kind = EAnGrTransactionKind.Uniform;
        param.parA = new AnGrFormula();
        param.parA.value = 0;
        param.parB = new AnGrFormula();
        param.parB.value = 0;
        param.fromMin = new AnGrFormula();
        param.fromMin.value = 0;
        param.fromMax = new AnGrFormula();
        param.fromMax.value = 0.01f;
        param.toParam = new AnGrFormula();
        param.toParam.value = 0;
        param.duration = 0.1f;
        transaction.parameters = param;
        newNode.simpleTransactions.Add( transaction );

        transaction = new AnGrFlMultiTransaction();
        transaction.targetNode = newNode.nodeName;
        transaction.probability = 0;

        param = new AnGrFlTransaction();
        param.blending = EAnGrTransactionUpdate.PoseToAnim;
        param.kind = EAnGrTransactionKind.Uniform;
        param.parA = new AnGrFormula();
        param.parA.value = 0;
        param.parB = new AnGrFormula();
        param.parB.value = 0;
        param.fromMin = new AnGrFormula();
        param.fromMin.value = 0.99f;
        param.fromMax = new AnGrFormula();
        param.fromMax.value = 1.0f;
        param.toParam = new AnGrFormula();
        param.toParam.value = 0;
        param.duration = 0.1f;
        transaction.parameters = param;
        nodeToConvert.simpleTransactions.Add( transaction );

        animGraph.macroNodes.Add( newNode );

        trans.Commit();
      }

      RecreateNeeded = true;
      SetInvalid();
    }

    public void ToNormalNode(RandomNode _node)
    {
      if(_node == null)
        return;

      using( UndoRedoTransaction trans = new UndoRedoTransaction( string.Format("Convert '{0}' to NormalNode", _node.Name) ) )
      {
        NormalNode result = CreateNormalNode( "new_node", _node.X, _node.Y );

        result.PlayIndex = _node.PlayIndex;
        result.X = _node.X;
        result.Y = _node.Y;

        CopyNodeBaseProperties( _node.SubNodes[0], result );

        //копируем исходящие линки
        DuplicateOutboundLinks( _node, result );

        //копируем входящие линки
        DuplicateInboundLinks( _node, result );

        //тереь у нас уже есть все линки и мы можем назначить NextNode
        CopyNextNode( _node, result );

        // изменим все ссылки на это имя 
        foreach( var node in ListWithoutSubnodes() )
        {
          if( node == _node )
            continue;

          if( node.NextNode == _node.Name )
          {
            node.NextNode = result.Name;
          }
        }

        string name = _node.Name;

        //удаляем рандомную ноду
        RemoveNode( _node );

        result.Name = name;

        trans.Commit();
      } 

      RecreateNeeded = true;
      SetInvalid();
    }

    public void CreateNodeCopy(Node _srcNode)
    {
      using( UndoRedoTransaction trans = new UndoRedoTransaction( "Copy of node" ) )
      {
        if( _srcNode is NormalNode )
          CreateNodeCopy( _srcNode as NormalNode );

        if( _srcNode is RandomNode )
          CreateNodeCopy( _srcNode as RandomNode );
        trans.Commit();
      }
     
      SetInvalid();
      RecreateNeeded = true;
      
    }

    private void CreateNodeCopy(NormalNode _srcNode)
    {
      NormalNode result = CreateNormalNode("Copy of " + _srcNode.Name, 0, 0);

      CopyNodeBaseProperties(_srcNode, result);

      //копируем исходящие линки
      DuplicateOutboundLinks(_srcNode, result);

      //копируем входящие линки
      DuplicateInboundLinks(_srcNode, result);

      //тереь у нас уже есть все линки и мы можем назначить NextNode
      CopyNextNode(_srcNode, result);
    }

    private void CreateNodeCopy(RandomNode _srcNode)
    {
      RandomNode result = CreateRandomNode("Copy of " + _srcNode.Name, 0, 0);

      //копируем сабноды
      foreach (var subnode in _srcNode.SubNodes)
      {
        SubNode sn = CreateSubNode(subnode.Name);

        result.SubNodes.Add(sn);

        CopyNodeBaseProperties(subnode, sn);
      }

      //сабнода которая создалась при добавлении рандомной ноды
      result.SubNodes.RemoveAt(0);

      //копируем исходящие линки
      DuplicateOutboundLinks(_srcNode, result);

      //копируем входящие линки
      DuplicateInboundLinks(_srcNode, result);

      //тереь у нас уже есть все линки и мы можем назначить NextNode
      CopyNextNode(_srcNode, result);
    }

    #region AnimGraph Utils

    /// <summary>
    /// Копирует основные свойства из одной ноды в другую
    /// </summary>
    /// <param name="_from">Из</param>
    /// <param name="_to">В</param>
    private void CopyNodeBaseProperties(NormalNode _from, NormalNode _to)
    {
      _to.Animation = _from.Animation;
      _to.Speed = _from.Speed;
      _to.SurfaceSpeed = _from.SurfaceSpeed;
      _to.In = _from.In;
      _to.Out = _from.Out;

      //создаем новые маркеры
      foreach( Marker marker in _from.Markers )
      {
        _to.Markers.Add(new Marker
        { 
          Owner = _to,
          Name = marker.Name, 
          VirtPar = marker.VirtPar 
        });
      }
    }
    
    /// <summary>
    /// Создает дубликаты исходящих линков
    /// </summary>
    /// <param name="_from">Нода источник линков</param>
    /// <param name="_to">Нода,в  которую будут продублированы линки</param>
    private void DuplicateOutboundLinks(Node _from, Node _to)
    {
      foreach (var link in _from.Links)
      {
        DuplicateLink(_to, link.ToNode, link);
      }
    }

    /// <summary>
    /// Создает дубликаты всех входящих линков
    /// </summary>
    /// <param name="_from">Исходная нода</param>
    /// <param name="_to">Нода для которой надо создать дубликаты линков</param>
    private void DuplicateInboundLinks(Node _from, Node _to)
    {
      foreach (var node in ListNodes())
      {
        for (int i = 0; i < node.Links.Count; ++i)
        {
          var link = node.Links[i];
          //игнорируем линки 'в текущую ноду' и линки 'из сабнод'
          if (link.ToNode == _from && !(link.FromNode is SubNode))
          {
            DuplicateLink(link.FromNode, _to, link);
          }
        }
      }
    }

    /// <summary>
    /// Создает дубликат линка
    /// </summary>
    /// <param name="_from">Нода, из которой выходит линк</param>
    /// /// <param name="_to">Нода, в которую входит линк</param>
    /// <param name="_linkInfo">Линк, который надо продублировать</param>
    /// <returns></returns>
    private Link DuplicateLink(Node _from, Node _to, Link _linkInfo)
    {
      var result = _from.LinkTo(_to);

      result.Duration = _linkInfo.Duration;
      result.Blending = _linkInfo.Blending;
      result.MinFrom = _linkInfo.MinFrom;
      result.MaxFrom = _linkInfo.MaxFrom;

      return result;
    }

    /// <summary>
    /// Прописывает валидное значение в NextNode
    /// </summary>
    /// <param name="_from">Исходная нода</param>
    /// <param name="_to">Нода, в которую надо прописать значение</param>
    private void CopyNextNode(Node _from, Node _to)
    {
      if (_from.Looped)
      {
        _to.Looped = true;
      }
      else
      {
        _to.Looped = false;
        _to.NextNode = _from.NextNode;
      }
    }

    #endregion
  }
}
