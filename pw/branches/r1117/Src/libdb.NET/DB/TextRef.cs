using System;
using System.IO;
using System.Text;
using libdb.IO;
using libdb.UndoRedo;

namespace libdb.DB
{
  public class ChangeTextRefOperation : IUndoRedoOperation
  {
    private readonly TextRef text;
    private readonly string value;
    private readonly string oldValue;

    public ChangeTextRefOperation(TextRef text, string value)
    {
      this.text = text;
      this.value = value;
      this.oldValue = text.ToString();
    }

    public void Undo()
    {
      text.FromStringInternal(oldValue);
    }

    public void Redo()
    {
      text.FromStringInternal(value);
    }

    public string DefaultCaption
    {
      get { return value; }
    }

    public libdb.DB.DBResource GetOwner()
    {
      return text.GetOwner();
    }
  }

  [SimpleType]
  [RenameType("CTextRef")]
  public sealed class TextRef : SimpleSerializable<TextRef.TextRefSerializeAttributes>, IBasicDBValue, IChangeable
  {
    public class TextRefSerializeAttributes
    {
      public string textref = string.Empty;
      public TextRefSerializeAttributes() { }
      public TextRefSerializeAttributes(string textref) { this.textref = textref; }
    }

    public class ResetTextRefOperation : IUndoRedoOperation
    {
        private readonly TextRef text;
        private readonly bool value;
        private readonly bool oldValue;

        public ResetTextRefOperation(TextRef text, bool value)
        {
            this.text = text;
            this.value = value;
            this.oldValue = text.isDerivedFromParent;
        }

        public void Undo()
        {
            text.isDerivedFromParent = oldValue;
        }

        public void Redo()
        {
            text.isDerivedFromParent = value;
        }

        public string DefaultCaption
        {
            get { return "Reset TextRef"; }
        }

        public DBResource GetOwner()
        {
            return text.GetOwner();
        }
    }

    private static bool TryLoadString(IFileSystem fileSystem, string fileName, out string text)
    {
      text = string.Empty;
      using (Stream file = fileSystem.OpenFile(fileName))
      {
        if (file == null)
          return false;

        using (TextReader reader = new StreamReader(file))
        {
          text = reader.ReadToEnd();
          reader.Close();
        }
        file.Close();
      }

      return true;
    }

    private static string GetFileNameFromFieldPath(FieldPath path)
    {
      string result = string.Empty;
      foreach (FieldPath.FieldPathItem item in path)
      {
        if (item.Index >= 0)
          result = "_" + item.Index.ToString() + result;

        result = "_" + item.Field.Name + result;

        if (TypeUtils.IsSubclassOf(item.Owner.GetType(), typeof(DBResource)))
        {
          DBResource itemOwner = (item.Owner as DBResource);
          DBID ownerDbid = itemOwner.DBId;
          string ownerName = ownerDbid.FileName;
          if (ownerDbid.IsInlined)
            ownerName += "_" + (new Guid(ownerDbid.Id).ToString("N"));

          if (itemOwner.GetStateName() != string.Empty)
            ownerName += "_" + itemOwner.GetStateName().Replace(' ', '_');

          return ownerName + result + ".txt";
        }
      }

      return string.Empty;
    }

    private static bool StoreTest(IFileSystem fileSystem, string fileName, string text)
    {
      using (Stream file = fileSystem.CreateFile(fileName))
      {
        if (file == null)
          return false;

        using (TextWriter writer = new StreamWriter(file, Encoding.Unicode))
        {
          writer.Write(text);
          writer.Close();
        }
        file.Close();
      }

      return true;
    }

    private DBResource owner = null;
    private string text = string.Empty;
    private string fileName = string.Empty;

    public TextRef() { }

    public TextRef(DBResource owner)
    {
      this.owner = owner;
    }

    public TextRef(DBResource owner, TextRef source)
    {
      this.owner = owner;
      Assign(source);
    }

    private void OnChanged()
    {
      if (parent != null)
        isDerivedFromParent = false;

      if (Changed != null)
        Changed(this, EventArgs.Empty);
    }

    public event EventHandler Changed = null;
    public DBResource GetOwner() { return owner; }

    public string FileName { get { return fileName; } }

    public void FromString(string text)
    {
      if (text != ToString())
        DataBase.AddOperation(new ChangeTextRefOperation(this, text));
    }

    internal void FromStringInternal(string text)
    {
      this.text = text;
      OnChanged();
    }

    public override string ToString()
    {
      if (parent != null && isDerivedFromParent)
        return parent.ToString();
      return text;
    }

    protected override TextRefSerializeAttributes Serialize(FieldPath path)
    {
      string wantedFileName = string.IsNullOrEmpty(text) ? string.Empty : GetFileNameFromFieldPath(path);

      if (!string.IsNullOrEmpty(wantedFileName) && !StoreTest(DataBase.FileSystem, wantedFileName, text))
        wantedFileName = string.Empty;

      fileName = wantedFileName;
      return new TextRefSerializeAttributes(fileName);
    }

    protected override bool Deserialize(TextRef.TextRefSerializeAttributes attributes)
    {
      fileName = attributes.textref;
      //@Ivn@TODO: actually I want Application here
      if (!TryLoadString(DataBase.FileSystem, fileName, out text))
      {
        fileName = string.Empty;
        text = string.Empty;
      }
      OnChanged();

      return true;
    }

    private bool isDerivedFromParent = true;
    private TextRef parent = null;

    public void AssignReCreateFileName( object source, FieldPath path )
    {
        TextRef src = source as TextRef;
        if (src != null)
        {
            fileName = string.IsNullOrEmpty(src.text) ? string.Empty : GetFileNameFromFieldPath(path);

            // avoid calling OnChanged on creating new object due Initialize( this ) in classes' constructors
            if (string.IsNullOrEmpty(ToString()) && string.IsNullOrEmpty(src.ToString()))
                return;

            text = src.text;
            OnChanged();
        }
    }

    public void Assign(object source)
    {
      TextRef src = source as TextRef;
      if (src != null)
      {
        if (string.IsNullOrEmpty(fileName) && !string.IsNullOrEmpty(src.fileName))
          fileName = src.fileName;

        // avoid calling OnChanged on creating new object due Initialize( this ) in classes' constructors
        if (string.IsNullOrEmpty(ToString()) && string.IsNullOrEmpty(src.ToString()))
          return;

        text = src.text;
        OnChanged();
      }
    }

    public void SetParent(object parent)
    {
      if (parent is TextRef)
        this.parent = parent as TextRef;
    }

    public void Reset()
    {
      DataBase.AddOperation(new ResetTextRefOperation(this, true));
    }

    public bool IsDerivedFromParent()
    {
      return parent == null || isDerivedFromParent;
    }
    /// <summary>
    /// Reads text in txt file assigned to this TextRef
    /// </summary>
    /// <returns>Content of assigned txt file</returns>
    public string GetText()
    {
      return text;
      //string result = String.Empty;
      //TryLoadString(DataBase.FileSystem, fileName, out result);
      //return result;
    }
  }
}
