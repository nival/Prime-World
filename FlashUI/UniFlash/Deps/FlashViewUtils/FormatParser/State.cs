namespace FlashView.Utils.FormatParser
{
  interface IState
  {
    StateContext Context { get; set; }

    void Enter();
    void Leave();
    void Update( char ch );
  }

  class StateContext
  {
    public Entry RootEntry { get; private set; }
    public Entry CurrentEntry { get; set; }
    public bool NewLineNeeded { get; set; }

    public StateContext()
    {
      var root = new Entry( EntryType.Root, null, false );

      RootEntry = root;
      CurrentEntry = root;
    }
  }

  class TextState : IState
  {
    public StateContext Context { get; set; }

    public TextState( StateContext context )
    {
      Context = context;
    }

    public void Enter()
    {
      //создаем ноду для этого текста
      var childEntry = new Entry( EntryType.Text, Context.CurrentEntry, false );
      Context.CurrentEntry = childEntry;
    }

    public void Leave()
    {
      //выходим из ноды, т.к. у текста не может быть вложений
      Context.CurrentEntry = Context.CurrentEntry.Parent;
      Context.NewLineNeeded = true;
    }

    public bool IgnoreSpace = true;

    public void Update( char ch )
    {
      //игнорируем переносы строк и табы
      if ( ch != ' ' && char.IsWhiteSpace( ch ) )
        return;

      if ( ch == ' ' && IgnoreSpace )
        return;

      //допустим только один пробел между словами
      IgnoreSpace = ch == ' ';

      Context.CurrentEntry.Text += ch;
    }
  }

  class BrTagState : IState
  {
    public StateContext Context { get; set; }

    public BrTagState( StateContext context )
    {
      Context = context;
    }

    public void Enter()
    {

      Entry parent = null;

      if ( Context.CurrentEntry.EntryType == EntryType.FormattingTag )
        parent = Context.CurrentEntry.Parent;
      else
        parent = Context.CurrentEntry;

      Context.CurrentEntry = new Entry( EntryType.BrTag, parent, false );
    }

    public void Leave()
    {
      //выходим из ноды, т.к. у текста не может быть вложений
      Context.CurrentEntry = Context.CurrentEntry.Parent;
      Context.NewLineNeeded = false;
    }

    public void Update( char ch )
    {
      Context.CurrentEntry.Text += ch;
    }
  }

  class UnaryTagState : IState
  {
    public StateContext Context { get; set; }

    public UnaryTagState( StateContext context )
    {
      Context = context;
    }

    public void Enter()
    {
      Context.CurrentEntry = new Entry( EntryType.UnaryTag, Context.CurrentEntry, false );
    }

    public void Leave()
    {
      //выходим из ноды, т.к. у текста не может быть вложений
      Context.CurrentEntry = Context.CurrentEntry.Parent;
      Context.NewLineNeeded = true;
    }

    public void Update( char ch )
    {
      Context.CurrentEntry.Text += ch;
    }
  }

  class FormattingTagState : IState
  {
    public StateContext Context { get; set; }

    public FormattingTagState( StateContext context )
    {
      Context = context;
    }

    public void Enter()
    {
      Entry parent = null;

      if ( Context.CurrentEntry.EntryType == EntryType.FormattingTag )
        parent = Context.CurrentEntry.Parent;
      else
        parent = Context.CurrentEntry;

      Context.CurrentEntry = new Entry( EntryType.FormattingTag, parent, Context.NewLineNeeded );
    }

    public void Leave()
    {
      Context.NewLineNeeded = true;
    }

    public void Update( char ch )
    {
      Context.CurrentEntry.Text += ch;
    }
  }

  class TagState : IState
  {
    public StateContext Context { get; set; }

    public TagState( StateContext context )
    {
      Context = context;
    }

    public void Enter()
    {
      //создаем ноду для этого тэга
      var childEntry = new Entry( EntryType.Tag, Context.CurrentEntry, false );
      Context.CurrentEntry = childEntry;
    }

    public void Leave()
    {
      Context.NewLineNeeded = false;
    }

    public void Update( char ch )
    {
      Context.CurrentEntry.Text += ch;
    }
  }

  class CloseTagState : IState
  {
    public StateContext Context { get; set; }

    public CloseTagState( StateContext context )
    {
      Context = context;
    }

    public void Enter()
    {
    }

    public void Leave()
    {
      Context.NewLineNeeded = true;

      if ( Context.CurrentEntry == Context.RootEntry )
      {
        NivalCLI.CLI.Warning( "Unneeded close tag. Please fix error in formatting." );
        return;
      }

      //выходим из ноды, закончился тэг и новые Entry должны добавляться в Parent к текущему тэгу
      Context.CurrentEntry = Context.CurrentEntry.Parent;

    }

    public void Update( char ch )
    {

    }
  }
}