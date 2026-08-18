using System.Collections;
using System.Collections.Generic;

namespace Flash
{
	public sealed class FocusNode : IEnumerable<FocusNode>
	{
		private InteractiveObject _node;
		public InteractiveObject Node
		{
			get { return _node; }
		}
		private FocusNode _previous;
		public FocusNode Previous
		{
			get { return _previous; }
		}
		private FocusNode _next;
		public FocusNode Next
		{
			get { return _next; }
		}
		public FocusNode First
		{
			get
			{
				FocusNode prev = this;
				while ( prev.Previous != null )
				{
					//Debug.Log("FIRST : "+prev.Node.Name);
					prev = prev.Previous;
				}
				return prev;
			}
		}

		public FocusNode( InteractiveObject node )
		{
			_node = node;
		}

		public IEnumerator<FocusNode> GetEnumerator()
		{
			FocusNode next = this;

			while ( next != null )
			{
				yield return next;
				next = next.Next;
			}
		}
		IEnumerator IEnumerable.GetEnumerator()
		{
			return GetEnumerator();
		}
		public void AddPrevious(FocusNode previous)
		{
			_previous = previous;
			previous._next = this;
		}
		public void AddNext(FocusNode next)
		{
			_next = next;
			_next._previous = this;
		}
		public bool Contains(ref FocusNode node,InteractiveObject obj)
		{
			foreach(FocusNode descent in this)
			{
				if ( descent._node == obj )
				{
					node = descent;
					return true;
				}
			}
			return false;
		}
	}
}
