using System;
using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib.IO;

namespace EditorLib.ObjectsBrowser
{
  public partial class BreadcrumbControl : System.Windows.Forms.ToolStrip
  {
    private ToolStripTextBox txtPath = null;
    //private Stack<ToolStripItem> _hidden = new Stack<ToolStripItem>();

    private ObjectsBrowserControl linkedObjectsBrowser = null;
    public ObjectsBrowserControl LinkedObjectsBrowser
    {
      get
      {
        return linkedObjectsBrowser;
      }
      set
      {
        if (linkedObjectsBrowser != null)
          linkedObjectsBrowser.ChangeCurrentFolderEvent -= OnChangeCurrentFolder;
        linkedObjectsBrowser = value;
        if (linkedObjectsBrowser != null)
          linkedObjectsBrowser.ChangeCurrentFolderEvent += new EventHandler(OnChangeCurrentFolder);
      }
    }

    public BreadcrumbControl()
		{
			InitializeComponent();

      if (linkedObjectsBrowser != null)
      {
        linkedObjectsBrowser.ChangeCurrentFolderEvent += new EventHandler(OnChangeCurrentFolder);
      }
      
      this.SuspendLayout();

      this.RenderMode = ToolStripRenderMode.System;
      this.GripStyle = ToolStripGripStyle.Hidden;
      
      InitAdressBar();
      InitOverflow();

      this.ResumeLayout();
		}

    private void InitAdressBar()
    {
      txtPath = new ToolStripTextBox("txtPath");
      txtPath.Visible = false;
      txtPath.AutoSize = false;
      
      txtPath.AcceptsReturn = true;
      txtPath.KeyDown += new KeyEventHandler(OnGoToPath);
      txtPath.LostFocus += new EventHandler(OnEndEditing);
      
      txtPath.Margin = new System.Windows.Forms.Padding(2);
      
      this.MouseClick += new MouseEventHandler(OnShowEditControl);

      Items.Add(txtPath);
    }

    //Создаем новую кнопку для папки
    private ToolStripItem GetNewItem(ObjectsFolder folder)
    {
      ToolStripItem button = null;

      List<ObjectsFolder> folders = new List<ObjectsFolder>(folder.Folders);

      string displayedName = folder.Name;

      if (folder == ObjectsRootFolder.Root)
      {
        displayedName = "Root";
      }

      if (folders.Count > 0)
      {
        ToolStripSplitButton splitButton = new ToolStripSplitButton(displayedName);
        splitButton.ButtonClick += new EventHandler(OnButtonClicked);

        foreach (ObjectsFolder f in folder.Folders)
        {
          ToolStripMenuItem item = new ToolStripMenuItem();
          item.Tag = f;
          item.Text = f.Name;
          item.Click += new EventHandler(OnButtonClicked);

          splitButton.DropDownItems.Add(item);
        }

        button = splitButton;
      }
      else
      {
        button = new ToolStripButton(displayedName);
        button.Click += new EventHandler(OnButtonClicked);
      }

      button.Tag = folder;
      //button.Overflow = ToolStripItemOverflow.Never;

      return button;
    }

    //Создаем кнопки для элементов пути
    private void CreatePathButtons()
    {
      if (LinkedObjectsBrowser.CurrentFolder == null)
        return;

      if (LinkedObjectsBrowser.CurrentFolder.Parent == null)
      {
        Items.Insert(0, GetNewItem(LinkedObjectsBrowser.CurrentFolder));
      }
      else
      {
        Items.Insert(0, GetNewItem(LinkedObjectsBrowser.CurrentFolder));

        ObjectsFolder parent = LinkedObjectsBrowser.CurrentFolder.Parent;

        while (parent != null)
        {
          Items.Insert(0, GetNewItem(parent));
          parent = parent.Parent;
        }
      }
    }

    //Удаляем кнопки с папками
    private void ClearPathButtons()
    {
      for (int i = Items.Count - 1; i >= 0; --i)
      {
        ToolStripItem item = Items[i];

        if (item.Name != "txtPath")
        {
          Items.Remove(item);
        }
      }
    }

    private void ShowAdressBar(bool show)
    {
      //скрываем кнопки папок
      foreach (ToolStripItem item in Items)
      {
        if (item != txtPath)
        {
          item.Visible = !show;
        }
      }

      if(show)
      {
        //показываем адресную строку
        txtPath.Overflow = ToolStripItemOverflow.AsNeeded;
        txtPath.Width = this.Width - this.Padding.Horizontal - txtPath.Margin.Horizontal;
        txtPath.Text = LinkedObjectsBrowser.CurrentFolder.FullName;

        txtPath.Visible = true;
        txtPath.Focus();
        
      }
      else
      {
        //скрываем адресную строку
        txtPath.Visible = false;
        txtPath.BackColor = System.Drawing.SystemColors.Window;
      }
    }

    #region Event Handlers

    private void OnButtonClicked(object sender, EventArgs e)
    {
      ToolStripItem item = sender as ToolStripItem;

      if (item != null)
      {
        ObjectsFolder folder = item.Tag as ObjectsFolder;

        if (folder != null)
        {
          if (folder == linkedObjectsBrowser.CurrentFolder)
          {
            //если пользователь нажал на текущую папку, то отображаем адресную строку
            ShowAdressBar(true);
          }
          else
          {
            //переходим в нужную папку
            linkedObjectsBrowser.CurrentFolder = folder;
          }
        }
      }

    }

    private void OnChangeCurrentFolder(object sender, EventArgs e)
    {     
      ShowAdressBar(false);
      ClearPathButtons();
      CreatePathButtons();
    }

    private void OnGoToPath(object sender, KeyEventArgs e)
    {
      switch (e.KeyCode)
      {
        case Keys.Return://пользователь инициировал переход по пути

          ObjectsFolder folder = null;
          
          //пытаемся получить папку, по введеным данным
          if (ObjectsRootFolder.Root.TryGetFolder(txtPath.Text, out folder))
          {
            LinkedObjectsBrowser.CurrentFolder = folder;
            txtPath.Visible = false;
          }
          else
          {
            //пользователь ошибся при вводе пути
            txtPath.BackColor = System.Drawing.Color.LightSalmon;
          }

          break;
      }
    }

    private void OnEndEditing(object sender, EventArgs e)
    {
      ShowAdressBar(false);
    }

    private void OnShowEditControl(object sender, MouseEventArgs e)
    {
      //смотрим куда кликнул пользователь
      ToolStripItem item = this.GetItemAt(e.X, e.Y);

      //пользователь кликнул на пустое место, а не на элемент тулбара
      if (item == null)
      {
        ShowAdressBar(true);
      }
    }

    #endregion

    #region Overflow

    private void InitOverflow()
    {
      this.OverflowButton.Alignment = ToolStripItemAlignment.Left;
      this.Resize += new EventHandler(OnResize);
      this.LayoutCompleted += new EventHandler(OnLayoutCompleted);
    }

    private void OnLayoutCompleted(object sender, EventArgs e)
    {
      HideItems();
    }

    private void OnResize(object sender, EventArgs e)
    {
      this.PerformLayout();
    }

    private void HideItems()
    {
      int size = this.Padding.Horizontal +
        this.OverflowButton.Width + this.OverflowButton.Margin.Horizontal;

      for (int i = this.Items.Count - 1; i >= 0; --i)
      {
        ToolStripItem item = this.Items[i];

        if (item != txtPath)
        {
          size += item.Width + item.Margin.Horizontal;
          
          if (size > this.DisplayRectangle.Right)
          {
            //скрываем, элементы которые не влезли
            item.Overflow = ToolStripItemOverflow.Always;
          }
          else
          {
            //отображаем элемент, он уже мог быть скрыт и его надо вернуть на панель
            item.Overflow = ToolStripItemOverflow.AsNeeded;
          }
        }
      }
    }

    #endregion

  }
}
