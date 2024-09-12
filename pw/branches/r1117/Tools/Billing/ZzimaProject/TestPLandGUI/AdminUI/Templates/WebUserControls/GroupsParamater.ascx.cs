using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.MobileControls;
using System.Web.UI.WebControls;
using TextBox=System.Web.UI.WebControls.TextBox;

namespace ZzimaBilling.AdminUI.Templates.WebUserControls
{
    public partial class GroupsParamater : System.Web.UI.UserControl
    {
        #region Properties

        public bool Enabled
        {
            set
            {
                lbxGroups.Enabled = value;
                tbSumGroup.Enabled = value;
                btnAdd.Enabled = value;
                btnSave.Enabled = value;
                btnDelete.Enabled = value;
                ValidationIsEnabled = value;
            }
            get
            {
                return lbxGroups.Enabled;
            }
        }

        public bool ValidationIsEnabled
        {
            get
            {
                return rfvSum.Enabled;
            }
            set
            {
                rfvSum.Enabled = value;
            }

        }

        public List<int> Groups
        {
            get
            {
                if (ViewState["Groups"] == null)
                {
                    ViewState["Groups"] = new List<int>();
                }
                return (List<int>)ViewState["Groups"];
            }
            set
            {
                ViewState["Groups"] = value;
            }
        }

        public int CurrentIndex
        {
            get
            {
                if (ViewState["CurrentIndex"] == null)
                    return -1;
                return Convert.ToInt32(ViewState["CurrentIndex"]);
            }
            set
            {
                ViewState["CurrentIndex"] = value;
            }
        }

        #endregion

        #region Methods

        public GroupsParamater()
        {
        }

        public GroupsParamater(ArrayList array)
        {
            for (int i = 0; i < array.Capacity; i++)
                lbxGroups.Items.Add(new ListItem(array[i].ToString()));
        }

        protected bool CheckListBox(ListBox listBox, ListItem lItem)
        {
            if (listBox.Items.Contains(lItem))
                return true;
            return false;
        }

        private void FillListBoxWithGroups()
        {
            lbxGroups.Items.Clear();
            foreach (int group in Groups)
            {
                lbxGroups.Items.Add(new ListItem(group.ToString()));
            }
            lbxGroups.SelectedIndex = -1;
        }

        private void AddNewGroup(int newGroup)
        {
            if (!Groups.Contains(newGroup))
            {
                Groups.Add(newGroup);
                Groups.Sort();
                FillListBoxWithGroups();
            }
        }

        private void DeleteGroup(int group)
        {
            if (Groups.Contains(group))
            {
                Groups.Remove(group);
                Groups.Sort();
                FillListBoxWithGroups();
                SelectFirstIndex();
            }
        }

        protected void SelectedIndexChanged()
        {
            if (lbxGroups.SelectedItem != null)
                tbSumGroup.Text = lbxGroups.SelectedItem.Value;
        }

        protected void SelectFirstIndex()
        {
            if (lbxGroups.SelectedIndex == -1 && Groups.Count > 0)
            {
                lbxGroups.SelectedIndex = 0;
            }
        }

        #endregion

        #region Events

        protected void Page_Load(object sender, EventArgs e)
        {
            if (CurrentIndex != lbxGroups.SelectedIndex)
            {
                CurrentIndex = lbxGroups.SelectedIndex;
                SelectedIndexChanged();
            }
        }

        protected void btnSave_Click(object sender, ImageClickEventArgs e)
        {
            if (lbxGroups.SelectedItem != null&&tbSumGroup.Text!=string.Empty)
            {
                int newValue = Convert.ToInt32(tbSumGroup.Text);
                int oldValue = Convert.ToInt32(lbxGroups.SelectedItem.Text);
                DeleteGroup(oldValue);
                AddNewGroup(newValue);
                SelectedIndexChanged();
                ValidateGroupsCount();
            }
        }

        protected void btnAdd_Click(object sender, ImageClickEventArgs e)
        {
            int newGroup=Convert.ToInt32(tbSumGroup.Text);
            AddNewGroup(newGroup);
            SelectedIndexChanged();
            ValidateGroupsCount();
        }

        protected void btnDelete_Click(object sender, ImageClickEventArgs e)
        {
            if (lbxGroups.SelectedItem != null)
            {
                int selectedGroup = Convert.ToInt32(lbxGroups.SelectedItem.Text);
                DeleteGroup(selectedGroup);
                tbSumGroup.Text = "";
                SelectedIndexChanged();
                ValidateGroupsCount();
            }
        }

        private void ValidateGroupsCount()
        {
            cvGroups.Validate();
        }

        protected void cvGroups_ServerValidate(object source, ServerValidateEventArgs args)
        {
            if (!Enabled)
            {
                args.IsValid = true;
            }
            else
                args.IsValid = (Groups.Count >= 2);
        }

        #endregion 
    }
}
