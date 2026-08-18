using System;

namespace Flash
{
	public class Event : EventArgs
	{
		private bool _propogateAcrossNode = true;
		public bool PropogateAcrossNode
		{
			get { return _propogateAcrossNode; }
		}
		private bool _propogateAcrossHierarchy;
		public bool PropogateAcrossHierarchy
		{
			get { return _propogateAcrossHierarchy; }
		}
		protected string _eventType;
		public string EventType
		{
			get { return _eventType; }
		}
	  private UnityEngine.Event _unityEvent;
	  public UnityEngine.Event UnityEvent
	  {
      get { return _unityEvent; }
	  }

    public Event(string type, bool propogateAcrossHierarchy)  : this(type,propogateAcrossHierarchy,null){}
		public Event( string type, bool propogateAcrossHierarchy, UnityEngine.Event unityEvent )
		{
			_eventType = type;
			_propogateAcrossHierarchy = propogateAcrossHierarchy;
		  _unityEvent = unityEvent;
		}

		public void StopPropagation()
		{
			_propogateAcrossNode = false;
		}
		public void StopImmediatePropagation()
		{
      if (_unityEvent != null)
      {
        _unityEvent.Use();
        FlashInput.Input.ResetInputAxes();
      }
		  _propogateAcrossHierarchy = false;
		}
	}
}
