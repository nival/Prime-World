#define DEBUG_ACTIONS

using System;
using System.Runtime.Serialization;
using SwfDotNet.IO.ByteCode.Actions;
using SwfDotNet.IO.Tags;
using UnityEngine;
using System.Collections;

namespace Flash{
	[Serializable]
  public class UniDoActionTag : IDisplayTag, ISerializable
  {
    private ArrayList _actions;
    public ArrayList Actions
    {
      get { return _actions; }
    }
    private IActionExecutorSWF3 _executor = new ActionExecutorSwf3();

    public UniDoActionTag(DoActionTag tag)
    {
      _actions = tag.Actions;
      //Check actions
      foreach (BaseAction action in _actions)
      {
        Type actionType = action.GetType();

        if (actionType != typeof(ActionPlay)
          && actionType != typeof(ActionStop)
          && actionType != typeof(ActionNextFrame)
          && actionType != typeof(ActionPreviousFrame)
          && actionType != typeof(ActionGotoFrame)
          && actionType != typeof(ActionGotoLabel)
          && actionType != typeof(ActionEnd)
          )
        {
          Debug.LogWarning("Unknown Action "+actionType);
        }
      }
    }
    public void Execute(Frame frame, Sprite sprite){ }
    public void DoActions(DisplayObject displayObject)
    {
      object action;
      for ( int i = 0; i < Actions.Count; i++ )
      {
        action = Actions[i];
        if ( action == null )
          continue;
        if(action is ActionPlay)
          _executor.DoActionPlay((ActionPlay)action,displayObject);
        else if (action is ActionStop)
          _executor.DoActionStop((ActionStop)action, displayObject);
        else if (action is ActionNextFrame)
          _executor.DoActionNextFrame((ActionNextFrame)action, displayObject);
        else if (action is ActionPreviousFrame)
          _executor.DoActionPreviousFrame((ActionPreviousFrame)action, displayObject);
        else if (action is ActionGotoFrame)
          _executor.DoActionGotoFrame((ActionGotoFrame)action, displayObject);
        else if (action is ActionGotoLabel)
          _executor.DoActionGotoLabel((ActionGotoLabel)action, displayObject);
        else if(action is ActionEnd)
        {
          break;
          // End of actions
        } 
        //if (action is ActionWaitForFrame)
        //  _executor.DoActionWaitForFrame((ActionWaitForFrame)action, displayObject);
        //if (action is ActionGetUrl)
        //  _executor.DoActionGetUrl((ActionGetUrl)action, displayObject);
        //if (action is ActionStopSounds)
        //  _executor.DoActionStopSounds((ActionStopSounds)action, displayObject);
        //if (action is ActionToggleQuality)
        //  _executor.DoActionToggleQuality((ActionToggleQuality)action, displayObject);
        //if (action is ActionSetTarget)
        //  _executor.DoActionSetTarget((ActionSetTarget)action, displayObject);
      }
    }

		#region Implementation of ISerializable

		public UniDoActionTag(SerializationInfo info, StreamingContext context)
		{
			Flash.SerializeHelpers.Unpack(info, "_actions", out _actions);  
		}

		public void GetObjectData(SerializationInfo info, StreamingContext context)
		{
			Flash.SerializeHelpers.Pack(info, "_actions", _actions);
		}

		#endregion
  }

  public class ActionExecutorSwf3 : IActionExecutorSWF3
  {
    public void DoActionPlay(ActionPlay action, DisplayObject target)
    {
      ((MovieClip)target).Play();
    }
    public void DoActionStop(ActionStop action, DisplayObject target)
    {
      ((MovieClip)target).Stop();
    }
    public void DoActionNextFrame(ActionNextFrame action, DisplayObject target)
    {
      ((MovieClip)target).NextFrame();
    }
    public void DoActionPreviousFrame(ActionPreviousFrame action, DisplayObject target)
    {
      ((MovieClip)target).PrevFrame();
    }
    public void DoActionGotoFrame(ActionGotoFrame action, DisplayObject target)
    {
      ((MovieClip)target).GotoAndStop(action.Frame+1);
    }
    public void DoActionGotoLabel(ActionGotoLabel action, DisplayObject target)
    {
      ((MovieClip)target).GotoAndStop(((MovieClip)target).GetFrameByName(action.Label));
    }
    public void DoActionWaitForFrame(ActionWaitForFrame action, DisplayObject target)
    {
    }
    public void DoActionGetUrl(ActionGetUrl action, DisplayObject target)
    {
    }
    public void DoActionStopSounds(ActionStopSounds action, DisplayObject target)
    {
    }
    public void DoActionToggleQuality(ActionToggleQuality action, DisplayObject target)
    {
    }
    public void DoActionSetTarget(ActionSetTarget action, DisplayObject target)
    {
    }
  }

  public interface IActionExecutorSWF3
  {
    void DoActionPlay(ActionPlay action, DisplayObject target);
    void DoActionStop(ActionStop action, DisplayObject target);
    void DoActionNextFrame(ActionNextFrame action, DisplayObject target);
    void DoActionPreviousFrame(ActionPreviousFrame action, DisplayObject target);
    void DoActionGotoFrame(ActionGotoFrame action, DisplayObject target);
    void DoActionGotoLabel(ActionGotoLabel action, DisplayObject target);
    void DoActionWaitForFrame(ActionWaitForFrame action, DisplayObject target);
    void DoActionGetUrl(ActionGetUrl action, DisplayObject target);
    void DoActionStopSounds(ActionStopSounds action, DisplayObject target);
    void DoActionToggleQuality(ActionToggleQuality action, DisplayObject target);
    void DoActionSetTarget(ActionSetTarget action, DisplayObject target);
  }
}