using System.Collections.Generic;

namespace FlashView.Utils.FormatParser
{
  enum EntryType
  {
    Root,
    Text,
    Tag,
    BrTag,
    UnaryTag,
    FormattingTag
  }

  class Entry
  {
    public string Text { get; set; }
    public Entry Parent { get; private set; }
    public EntryType EntryType { get; private set; }
    public bool NewLineNeeded { get; private set; }

    private readonly List<Entry> _children = new List<Entry>();
    public List<Entry> Children { get { return _children; } }

    public Entry( EntryType type, Entry parent, bool newLineNeeded )
    {
      EntryType = type;
      Parent = parent;
      Text = string.Empty;
      NewLineNeeded = newLineNeeded;

      if ( parent != null )
        parent.Children.Add( this );
    }
  }
}
