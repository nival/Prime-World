using System;
using System.Reflection;
using Flash.Utils;
using SwfDotNet.IO.Tags;
using SwfDotNet.IO.Tags.Types;
using UnityEngine;
using System.Runtime.Serialization;

namespace Flash
{
    [System.Serializable]
  public class 
    UniPlaceObjectTag : UniBaseTag, IDisplayTag, ISerializable
  {

    private ushort _depth;
    public ushort Depth
    {
      get { return _depth; }
    }
    private string _name;
    public string Name
    {
      get { return _name; }
    }
    protected Matrix4x4 _transform = Matrix4x4.identity;
    public Matrix4x4 Transform
    {
      get { return _transform; }
    }
    private int _targetCharacterId;
    public int TargetCharacterId
    {
      get { return _targetCharacterId; }
    }
    private float _ratio;
    public float Ratio
    {
      get { return _ratio; }
    }
    protected ColorTransform _cxForm = new ColorTransform(null);
    public ColorTransform CxForm
    {
      get { return _cxForm; }
      set { _cxForm = value; }
    }
    private ushort _clipDepth;
    public ushort ClipDepth
    {
      get { return _clipDepth; }
    }
    private bool _hasTransform;
    public bool HasTransform
    {
      get { return _hasTransform; }
    }
    private bool _move;
    public bool Move
    {
      get { return _move; }
    }
    private bool _hasCxForm;
    public bool HasCxForm
    {
      get { return _hasCxForm; }
    }
    private bool _hasBlendMode;
    public bool HasBlendMode
    {
      get { return _hasBlendMode; }
    }
    private BlendMode _blendMode = BlendMode.Normal;
    public BlendMode BlendMode
    {
      get { return _blendMode; }
    }
    private bool _hasFilterList;
    public bool HasFilterList
    {
      get { return _hasFilterList; }
    }
    private FilterList _filterList;
    public FilterList FilterList
    {
      get { return _filterList; }
    }

    public override void GetObjectData(SerializationInfo info, StreamingContext context)
    {
        base.GetObjectData(info, context);
            
        Flash.SerializeHelpers.Pack(info, "_depth", _depth);
        Flash.SerializeHelpers.Pack(info, "_name", _name);
        Flash.SerializeHelpers.Pack(info, "_transform", _transform);
        Flash.SerializeHelpers.Pack(info, "_targetCharacterId", _targetCharacterId);
        Flash.SerializeHelpers.Pack(info, "_ratio", _ratio);
        Flash.SerializeHelpers.Pack(info, "_cxForm", _cxForm);            
        Flash.SerializeHelpers.Pack(info, "_clipDepth", _clipDepth);
        Flash.SerializeHelpers.Pack(info, "_hasTransform", _hasTransform);
        Flash.SerializeHelpers.Pack(info, "_move", _move);
        Flash.SerializeHelpers.Pack(info, "_hasCxForm", _hasCxForm);
        Flash.SerializeHelpers.Pack(info, "_hasBlendMode", _hasBlendMode);
        Flash.SerializeHelpers.Pack(info, "_blendMode", _blendMode);
        Flash.SerializeHelpers.Pack(info, "_hasFilterList", _hasFilterList);
        Flash.SerializeHelpers.Pack(info, "_filterList", _filterList);
    }
        
    public UniPlaceObjectTag(SerializationInfo info, StreamingContext context) 
        : base(info, context) 
    {
        Flash.SerializeHelpers.Unpack(info, "_depth", out _depth);
        Flash.SerializeHelpers.Unpack(info, "_name", out _name);
        Flash.SerializeHelpers.Unpack(info, "_transform", out _transform);
        Flash.SerializeHelpers.Unpack(info, "_targetCharacterId", out _targetCharacterId);
        Flash.SerializeHelpers.Unpack(info, "_ratio", out _ratio);
        Flash.SerializeHelpers.Unpack(info, "_cxForm", out _cxForm);            
        Flash.SerializeHelpers.Unpack(info, "_clipDepth", out _clipDepth);
        Flash.SerializeHelpers.Unpack(info, "_hasTransform", out _hasTransform);
        Flash.SerializeHelpers.Unpack(info, "_move", out _move);
        Flash.SerializeHelpers.Unpack(info, "_hasCxForm", out _hasCxForm);
        Flash.SerializeHelpers.Unpack(info, "_hasBlendMode", out _hasBlendMode);
        Flash.SerializeHelpers.Unpack(info, "_blendMode", out _blendMode);
        Flash.SerializeHelpers.Unpack(info, "_hasFilterList", out _hasFilterList);
        Flash.SerializeHelpers.Unpack(info, "_filterList", out _filterList);
    }

    public UniPlaceObjectTag(BaseTag baseTag, UniSwf owner)
      : base(owner)
    {
      PlaceObject2Tag placeTag = (PlaceObject2Tag)baseTag;

      _name = placeTag.Name;
      _transform = FlashToUnityConverter.ConvertTransformMatrix(placeTag.Matrix);
      _depth = placeTag.Depth;
      _targetCharacterId = placeTag.TargetCharacterId;
      _ratio = placeTag.Ratio;
      _move = placeTag.Move;
      _clipDepth = placeTag.ClipDepth;
      _cxForm = new ColorTransform(placeTag.ColorTransform);
      _hasTransform = placeTag.HasMatrix();
      _hasCxForm = placeTag.HasColorTransform();

      PlaceObject3Tag place3Tag = baseTag as PlaceObject3Tag;
      if (place3Tag == null)
        return;

      _hasBlendMode = place3Tag.HasBlendMose();
      _blendMode = ((PlaceObject3Tag)baseTag).BlendMode;
      _hasFilterList = place3Tag.HasFilterList();
      _filterList = ((PlaceObject3Tag)baseTag).FilterList;
    }
    public void Execute( Frame frame, Sprite sprite )
    {
      if ( _depth < 1 )
        return;

      if ( TargetCharacterId == 0 && !Move )
        return;

      Transform transform = new Transform( this );

      if ( TargetCharacterId > 0 && !Move )
      {
        // new character
        CreateDisplayObject( TargetCharacterId, transform, frame, sprite );
      }

      if ( TargetCharacterId > 0 && Move )
      {
        // replace
        DisplayInstance oldInst = frame.RemoveInternal( _depth );
        CreateDisplayObject( TargetCharacterId, oldInst.Transform, frame, sprite );
        frame.ReplaceTransformAtInternal( _depth, transform );
      }

      if ( TargetCharacterId == 0 && Move )
      {
        // modify exist
        frame.ReplaceTransformAtInternal( _depth, transform );
      }
    }

    private void CreateDisplayObject(int id, Transform initTransform, Frame frame, Sprite parent)
    {
      UniBaseTag tag = null;
      if (!_swf.UniDictionary.TryGetValue(id, out tag))
      {
        Debug.LogWarning(String.Format("Can't find id {0}",id));
        return;
      }

      DisplayObject result = null;

      if (tag is UniDefineShapeTag)
        result = new Shape();
      else if (tag is UniDefineMorphShapeTag)
        result = new MorphShape();
      else if (tag is UniDefineBitsJpegTag)
      {
        result = new Shape();
      }
      else if (tag is UniDefineEditTextTag)
      {
        if (!DoBind(ref result, parent, tag))
          result = new TextField();
      }
      else if (tag is UniDefineSpriteTag)
      {
        if (!DoBind(ref result, parent, tag))
          result = new MovieClip();
      }
      else
      {
        // Not implemented tag
        Debug.LogWarning("Founded not defined tag");
        return;
      }

      // Глубокий биндинг
      if (result is InteractiveObject && ((IBindable)result).ControlNode == null)
      {
        ((IBindable)result).ControlNode = ((IBindable)parent).ControlNode;
        ((IBindable)result).IsTakenFromParent = true;
      }

      result.Name = _name;
      result.Transform = initTransform;

      frame.AddInternal(_depth, new DisplayInstance(result, initTransform), parent);

      // pre concatenate
      result.Transform.Concatenate(true, true);

      // SET FLASH CONTENT
      result.Push(tag);
      // Setup mask after children created
      SetupMask(result, parent);

      result.UpdateLocalBounds();

      // INIT
      if (result is InteractiveObject)
        ((IInteractive)result).InitInternal();

      // Apply Constraint
      if (result is MovieClip)
      {
        Type type = result.GetType();   
        ConstraintAttribute[] attrs = (ConstraintAttribute[])type.GetCustomAttributes(typeof(ConstraintAttribute), true);
        foreach (ConstraintAttribute constraintAttribute in attrs)
        {
          if(!constraintAttribute.Validate( (MovieClip)result ))
            Debug.LogError( constraintAttribute.LastValidationError );
        }

        // field constraints
        if(((IBindable)result).Constraints!=null)
        {
          foreach (ConstraintAttribute constraintAttribute in ((IBindable)result).Constraints)
          {
            if (!constraintAttribute.Validate((MovieClip)result))
              Debug.LogError(constraintAttribute.LastValidationError);
          }

          // Free constraint memory
          ((IBindable) result).Constraints = null;
        }
      }
    }
    private void SetupMask(DisplayObject obj, Sprite sprite)
    {
      // Clear
      if (Depth == 1)
      {
        sprite.TargetMaskDepth = 0;
        sprite.CurrentMask = null;
      }

      // mask
      if (_clipDepth > 0)
      {
        // submit mask
        sprite.CurrentMask = obj;
        obj.IsMask = true;
        sprite.TargetMaskDepth = ClipDepth;
      }

      if (sprite.TargetMaskDepth > 0 && Depth <= sprite.TargetMaskDepth)
      {
        obj.Mask = sprite.CurrentMask;
      }
    }

    private bool DoBind( ref DisplayObject result, Sprite parent, UniBaseTag tag )
    {
      if ( ( (IBindable)parent ).ControlNode == null )
        return false;

      ControlNode parentControlNode = ( (IBindable)parent ).ControlNode;
      ControlNode fieldNode = parentControlNode.FindNode( _name );

      if ( fieldNode == null )
        return false;

      try
      {
        if ( tag is UniDefineEditTextTag && ( fieldNode.Type.IsSubclassOf( typeof( MovieClip ) ) || fieldNode.Type == typeof( MovieClip ) ) )
          throw new InvalidBindException( "TextField can't be binded at field " + fieldNode.Parent.Type + "/" + fieldNode.Field.Name + " wich is subclass of MovieClip" );

        if ( tag is UniDefineSpriteTag && ( fieldNode.Type.IsSubclassOf( typeof( TextField ) ) || fieldNode.Type == typeof( TextField ) ) )
          throw new InvalidBindException( "MovieClip can't be binded at field " + fieldNode.Parent.Type + "/" + fieldNode.Field.Name + " wich is subclass of TextField" );
      }
      catch ( Exception e )
      {
        Debug.LogError( e.Message );
      }

      FieldInfo field = fieldNode.Field;

      // Биндим на уже инициализированный филд в классах view
      result = (DisplayObject)field.GetValue( parentControlNode.Bind );
      if ( result != null )
      {
        ( (IBindable)result ).ControlNode = fieldNode;
        fieldNode.Bind = (InteractiveObject)result;

        // Apply constraint
        ConstraintAttribute[] attrs = (ConstraintAttribute[])field.GetCustomAttributes( typeof( ConstraintAttribute ), true );
        ( (IBindable)result ).Constraints = attrs;
      }
      else
      {
        Debug.LogWarning( "BIND WARNING : You are trying to bind to uninitialised MovieClip " );
      }

      return true;
    }
  }
}
