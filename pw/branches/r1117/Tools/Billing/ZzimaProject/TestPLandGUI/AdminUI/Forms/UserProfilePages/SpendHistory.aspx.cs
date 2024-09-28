using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.DAL;
using System.Web.UI.DataVisualization.Charting;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class SpendHistory : UserProfileGridViewPage
    {
        #region Constants

        public const string VW_DETAILS = "pvDetails";
        public const string VW_SCT = "pvSCT";
        public const string VW_SCM = "pvSCM";
        public const string VW_RCT = "pvRCT";
        public const string VW_RCM = "pvRCM";
        public const int TAB_MAX_LENGTH = 25;
        public const string TAB_STRIP_CSS = "tabStripFrame";
        public const string TAB_STRIP_NO_BORDER_CSS = "tabStripFrameNoBorder";
        public const int TRESHOLD = 1;

        #endregion
        
        #region Properties

        public ExpensesFilterBLL Filter
        {
            get
            {
                ExpensesFilterBLL filter = new ExpensesFilterBLL();
                filter.AmountFrom = ncAmount.From;
                filter.AmountTo = ncAmount.To;
                filter.DateFrom = dtFrom.DateTime;
                filter.DateTo = dtTo.DateTime;
                foreach (ListItem item in chlGames.Items)
                {
                    if(item.Selected)
                        filter.Services.Add(Convert.ToInt32(item.Value));
                }
                foreach (ListItem item in chlSubjects.Items)
                {
                    if (item.Selected)
                        filter.Subjects.Add(item.Value);
                }
                return filter;
            }
        }

        public string CurrentView
        {
            get
            {
                if (ViewState["cv"] != null)
                {
                    return ViewState["cv"].ToString();
                }
                else
                {
                    ViewState["cv"] = string.Empty;
                    return string.Empty;
                }
            }
            set
            {
                if (ViewState["cv"] != null&&ViewState["cv"].ToString() != value)
                {
                    CurrentSortExpression = string.Empty;
                    CurrentSortDirection = string.Empty;
                    PageIndex = 0;
                }
                ViewState["cv"] = value;
            }
        }

        public bool GameTabsVisible
        {
            get
            {
                return tabControl.Items[1].Enabled && tabControl.Items[2].Enabled;
            }
            set
            {
                tabControl.Items[1].Enabled = tabControl.Items[2].Enabled = value;
            }
        }

        public bool SubjectTabsVisible
        {
            get
            {
                return tabControl.Items[3].Enabled && tabControl.Items[4].Enabled;
            }
            set
            {
                tabControl.Items[3].Enabled = tabControl.Items[4].Enabled = value;
            }
        }

        public bool TabsAndMultiPagesVisible
        {
            get
            {
                return tabStripDiv.Visible && MultiPageDetails.Visible;
            }
            set
            {
                tabStripDiv.Visible = MultiPageDetails.Visible = value;
            }
        }

        public bool TabStripFrameBorderIsVisible
        {
            get
            {
                return (TabStripFrameDiv.Attributes["class"] == TAB_STRIP_CSS);
            }
            set
            {
                TabStripFrameDiv.Attributes["class"] = (value) ? TAB_STRIP_CSS : TAB_STRIP_NO_BORDER_CSS;
            }
        }

        #endregion

        #region Page Events

        protected override void OnInit(EventArgs e)
        {
            base.OnInit(e);

            gvDetails.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);
            gvRCM.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);
            gvRCT.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);
            gvSCM.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);
            gvSCT.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);

            gvDetails.Sorting += new GridViewSortEventHandler(GridView_Sorting);
            gvRCM.Sorting += new GridViewSortEventHandler(GridView_Sorting);
            gvRCT.Sorting += new GridViewSortEventHandler(GridView_Sorting);
            gvSCM.Sorting += new GridViewSortEventHandler(GridView_Sorting);
            gvSCT.Sorting += new GridViewSortEventHandler(GridView_Sorting);

            ConfigureTabs(tabControl);
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                PageIndex = 0;
                PagesCount = 0;
                FillWithGames(chlGames, EmployeeDAL.getServices(UserID));
                FillWithSubjects(chlSubjects, EmployeeDAL.getOperationReasons(UserID));
                TabStripFrameBorderIsVisible = false;
                GameTabsVisible = false;
                SubjectTabsVisible = false;
                CheckAll(chlGames);
                CheckAll(chlSubjects);
            }
            
            //1. To define counts of both games and subjects and perform appropriately tabs
            int gamesCount = 0;
            int subjectsCount = 0;
            int totalCount = 0;
            decimal totalAmount = 0;
            EmployeeDAL.getUserExpensesSummary(UserID, Filter, ref totalCount, ref totalAmount,
                ref gamesCount, ref subjectsCount);
            if (totalCount < 1)
            {
                TabsAndMultiPagesVisible = false;
                TabStripFrameBorderIsVisible = false;
            }
            else
            {
                if (CurrentView == string.Empty)
                {
                    CurrentView = VW_DETAILS;
                    BindGridView();
                }
                FillSummary(totalCount, totalAmount);
                TabsAndMultiPagesVisible = true;
                TabStripFrameBorderIsVisible = true;
                GameTabsVisible = (gamesCount > 1);
                SubjectTabsVisible = (subjectsCount > 1);
                BindGridView();
                SetPagerButtonStates(pgrDetails);
                GetRowsCount(CurrentView);
                UpdatePagerInfo(pgrDetails);
            }
        }

        protected void Page_PreRender(object sender, EventArgs e)
        {
            JavaScriptLoad();
        }

        private void JavaScriptLoad()
        {
            StringBuilder addClickFunctionScript = new StringBuilder();

            addClickFunctionScript.Append(" function addClickFunction(id) {{ ");
            addClickFunctionScript.Append(" var b = document.getElementById(id); ");
            addClickFunctionScript.Append(" if (b && typeof(b.click) == 'undefined') b.click = function() {{ ");
            addClickFunctionScript.Append(" var result = true; if (b.onclick) result = b.onclick(); ");
            addClickFunctionScript.Append(" if (typeof(result) == 'undefined' || result) {{ eval(b.getAttribute('href')); }} ");
            addClickFunctionScript.Append(" }}}}; ");

            string addClickScript = "addClickFunction('{0}');";
            string ClickScript = String.Format(addClickScript, lbnApply.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + lbnApply.ClientID, ClickScript, true);

        }

        protected void CheckAll(CheckBoxList checkBoxList)
        {
            if (checkBoxList != null && checkBoxList.Items.Count > 0)
            {
                foreach (ListItem listItem in checkBoxList.Items)
                {
                    if (!listItem.Selected)
                        listItem.Selected = true;
                }
            }
        }

        #endregion

        #region GridView Events

        protected void GridView_RowCreated(object sender, GridViewRowEventArgs e)
        {
            GridViewSortImages(sender, e);
        }

        protected void GridView_Sorting(object sender, GridViewSortEventArgs e)
        {
            if (CurrentSortExpression == e.SortExpression.ToString())
            {
                if (CurrentSortDirection == "asc")
                    CurrentSortDirection = "desc";
                else
                    CurrentSortDirection = "asc";
            }
            else
            {
                CurrentSortExpression = e.SortExpression.ToString();
                CurrentSortDirection = "asc";
            }
            BindGridView();
        }
        
        #endregion

        #region Chart Methods | Не исправлять. Я позже исправлю. На ООП не было времени.

        

        #endregion

        #region Setting and Getting for Games and Subjects

        protected void BindGridView()
        {
            DataTable DataSourceTable = new DataTable();
            switch (CurrentView)
            {
                default:
                case VW_DETAILS:
                    {
                        gridView = gvDetails;
                        DataSourceTable = EmployeeDAL.getUserExpensesHistoryTable
                            (UserID, PageIndex * gridView.PageSize, 
                            gridView.PageSize, Filter, CurrentSortExpression, 
                            (CurrentSortDirection == "asc") ? true : false);
                        break;
                    }
                case VW_SCT:
                    {
                        gridView = gvSCT;
                        DataSourceTable = EmployeeDAL.getUserExpensesHistorySCTTable
                            (UserID, PageIndex * gridView.PageSize,
                            gridView.PageSize, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false);
                        FillAndConfigureChartSCT(chrtSCT, Translate("SpendHistory.Tabs.pvSCT.Title"), 
                            EmployeeDAL.getUserExpensesHistorySCT(UserID, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false), TRESHOLD);
                        break;
                    }
                case VW_SCM:
                    {
                        gridView = gvSCM;
                        DataSourceTable = EmployeeDAL.getUserExpensesHistorySCMTable
                            (UserID, PageIndex * gridView.PageSize,
                            gridView.PageSize, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false);
                        FillAndConfigureChartSCM(chrtSCM, Translate("SpendHistory.Tabs.pvSCM.Title"), 
                            EmployeeDAL.getUserExpensesHistorySCM( UserID, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false), TRESHOLD);
                        break;
                    }
                case VW_RCT:
                    {
                        gridView = gvRCT;
                        DataSourceTable = EmployeeDAL.getUserExpensesHistoryRCTTable
                            (UserID, PageIndex * gridView.PageSize,
                            gridView.PageSize, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false);
                        FillAndConfigureChartRCT(chrtRCT, Translate("SpendHistory.Tabs.pvRCT.Title"), 
                            EmployeeDAL.getUserExpensesHistoryRCT (UserID, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false), TRESHOLD);
                        break;
                    }
                case VW_RCM:
                    {
                        gridView = gvRCM;
                        DataSourceTable = EmployeeDAL.getUserExpensesHistoryRCMTable
                            (UserID, PageIndex * gridView.PageSize,
                            gridView.PageSize, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false);
                        FillAndConfigureChartRCM(chrtRCM, Translate("SpendHistory.Tabs.pvRCM.Title"), 
                            EmployeeDAL.getUserExpensesHistoryRCM( UserID, Filter, CurrentSortExpression,
                            (CurrentSortDirection == "asc") ? true : false), TRESHOLD);
                        break;
                    }
            }
            gridView.DataSource = DataSourceTable;
            gridView.DataBind();
            UpdatePagerInfo(pgrDetails);
        }

        protected void FillWithGames(CheckBoxList checkBoxList, List<ServiceBLL> games)
        {
            checkBoxList.Items.Clear();
            foreach (ServiceBLL game in games)
            {
                checkBoxList.Items.Add(new ListItem(game.Name, game.ServiceID.ToString()));
            }
        }

        protected void FillWithSubjects(CheckBoxList checkBoxList, List<string> subjects)
        {
            checkBoxList.Items.Clear();
            foreach (string subject in subjects)
            {
                checkBoxList.Items.Add(new ListItem(subject, subject));
            }
        }

        protected List<int> GetGames(CheckBoxList checkBoxList)
        {
            List<int> games = new List<int>();
            foreach (ListItem item in checkBoxList.Items)
            {
                if (item.Selected)
                {
                    int serviceID = Convert.ToInt32(item.Value);
                    games.Add(serviceID);
                }
            }
            return games;
        }

        protected List<string> GetSubjects(CheckBoxList checkBoxList)
        {
            List<string> subjects = new List<string>();
            foreach (ListItem item in checkBoxList.Items)
            {
                if (item.Selected)
                {
                    string subject = item.Value;
                    subjects.Add(subject);
                }
            }
            return subjects;
        }

        protected void FillSummary(int totalCount, decimal totalAmount)
        {
            lblTotalCountValue.Text = totalCount.ToString();
            lblTotalAmountValue.Text = totalAmount.ToString();
        }

        #endregion

        #region Navigation Events and Methods

        protected void GoToFirstTab()
        {
            MultiPageDetails.SetActiveView(pvDetails);
            tabControl.Items[0].Selected = true;
            CurrentView = VW_DETAILS;
            GetRowsCount(VW_DETAILS);
            SetPagerButtonStates(pgrDetails);
            UpdatePagerInfo(pgrDetails);
            BindGridView();

        }

        protected override void Navigate(object sender, EventArgs e)
        {
 	         LinkButton button = (sender as LinkButton);
            switch (button.CommandArgument)
            {
                case "First":
                    PageIndex = 0;
                    break;
 
                case "Prev":
                    PageIndex--;
                    break;

                case "Next":
                    PageIndex++;
                    break;

                case "Last":
                    PageIndex = PagesCount - 1;
                    break;
            }
            BindGridView();
            UpdatePagerInfo(pgrDetails);
        }

        #endregion

        private void GetRowsCount(string view)
        {
            switch (view)
            {
                default:
                case VW_DETAILS:
                    {
                        if (gridView == null)
                            gridView = gvDetails;
                        RowsCount = EmployeeDAL.getUserExpensesHistoryCount(UserID, Filter);
                        PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
                    }
                    break;

                case VW_SCT:
                    {
                        RowsCount = EmployeeDAL.getUserExpensesHistorySCTCount(UserID, Filter);
                        PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
                    }
                    break;

                case VW_SCM:
                    {
                        RowsCount = EmployeeDAL.getUserExpensesHistorySCMCount(UserID, Filter);
                        PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
                    }
                    break;

                case VW_RCT:
                    {
                        RowsCount = EmployeeDAL.getUserExpensesHistoryRCTCount(UserID, Filter);
                        PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
                    }
                    break;

                case VW_RCM:
                    {
                        RowsCount = EmployeeDAL.getUserExpensesHistoryRCMCount(UserID, Filter);
                        PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
                    }
                    break;
            }
        }

        protected void lbnApply_Click(object sender, EventArgs e)
        {
            PagesCount = 0;
            PageIndex = 0;
            gvDetails.SelectedIndex = 0;
            gvDetails.PageIndex = 0;
            GoToFirstTab();
            UpdatePagerInfo(pgrDetails);
        }

        protected void ConfigureTabs(System.Web.UI.WebControls.Menu tabStrip)
        {
            if (tabStrip != null)
            {
                for (int i = 0; i < tabStrip.Items.Count; i++)
                {
                    System.Web.UI.WebControls.MenuItem tab = tabStrip.Items[i];
                    tab.ToolTip = tab.Text;
                    if (tab.Text.ToString().Length > TAB_MAX_LENGTH)
                    {
                        tab.Text = tab.Text.ToString().Substring(0, TAB_MAX_LENGTH) + "...";
                    }
                }
            }
        }

        private void FillAndConfigureChartSCT(Chart chart, string chartTitle,
            List<ExpensesHistorySCTRecord> records, int threshold)
        {
            List<decimal> values = new List<decimal>();
            List<string> labels = new List<string>();
            foreach (var record in records)
            {
                values.Add(record.Percent);
                if (record.Percent < threshold)
                {
                    labels.Add("менее " + threshold + " %");
                }
                else
                {
                    labels.Add(record.ServiceName.ToString() +
                                   ": " + record.Count.ToString() + " ("
                                   + String.Format("{0:0.##}", record.Percent) + "%)");
                }
            }
            FillAndConfigureChart(chart, chartTitle, labels, values);
            Series series = chrtSCT.Series["Series1"];
            CustomizeSmallSegments(series, threshold);
        }

        private void FillAndConfigureChartSCM(Chart chart, string chartTitle,
            List<ExpensesHistorySCMRecord> records, int threshold)
        {
            List<decimal> values = new List<decimal>();
            List<string> labels = new List<string>();
            foreach (var record in records)
            {
                values.Add(record.Percent);
                if (record.Percent < threshold)
                {
                    labels.Add("менее " + threshold + " %");
                }
                else
                {
                    labels.Add(record.ServiceName.ToString() +
                                   ": " + String.Format("{0:0.##}", record.Amount) + " ("
                                   + String.Format("{0:0.##}", record.Percent) + "%)");
                }
            }
            FillAndConfigureChart(chart, chartTitle, labels, values);
            Series series = chart.Series["Series1"];
            CustomizeSmallSegments(series, threshold);
        }

        private void FillAndConfigureChartRCM(Chart chart, string chartTitle,
            List<ExpensesHistoryRCMRecord> records, int threshold)
        {
            List<decimal> values = new List<decimal>();
            List<string> labels = new List<string>();
            foreach (var record in records)
            {
                values.Add(record.Percent);
                if (record.Percent < threshold)
                {
                    labels.Add("менее " + threshold + " %");
                }
                else
                {
                    labels.Add(record.Reason.ToString() +
                                   ": " + String.Format("{0:0.##}", record.Amount) + " ("
                                   + String.Format("{0:0.##}", record.Percent) + "%)");
                }
            }
            
            FillAndConfigureChart(chart, chartTitle, labels, values);
            Series series = chrtSCT.Series["Series1"];
            CustomizeSmallSegments(series, threshold);
        }

        private void FillAndConfigureChartRCT(Chart chart, string chartTitle,
            List<ExpensesHistoryRCTRecord> records, int threshold)
        {
            List<decimal> values = new List<decimal>();
            List<string> labels = new List<string>();
            foreach (var record in records)
            {
                values.Add(record.Percent);
                if (record.Percent < threshold)
                {
                    labels.Add("менее " + threshold + " %");
                }
                else
                {
                    labels.Add(record.Reason.ToString() +
                                   ": " + record.Count.ToString() + " ("
                                   + String.Format("{0:0.##}", record.Percent) + "%)");
                }
            }
       
            FillAndConfigureChart(chart, chartTitle, labels, values);
            Series series = chart.Series["Series1"];
            CustomizeSmallSegments(series, threshold);
        }

        protected void OnTab_ItemClick(object sender, MenuEventArgs e)
        {
            string index = (sender as System.Web.UI.WebControls.Menu).SelectedItem.Value;
            string previousView = CurrentView;
            
            switch(index)
            {
                case VW_DETAILS:
                    MultiPageDetails.SetActiveView(pvDetails);
                    break;
                case VW_RCM:
                    MultiPageDetails.SetActiveView(pvRCM);
                    break;
                case VW_SCM:
                    MultiPageDetails.SetActiveView(pvSCM);
                    break;
                case VW_RCT:
                    MultiPageDetails.SetActiveView(pvRCT);
                    break;
                case VW_SCT:
                    MultiPageDetails.SetActiveView(pvSCT);
                    break;
            }

            CurrentView = index;
            BindGridView();
    
            if (previousView != CurrentView)
            {
                GetRowsCount(CurrentView);
                SetPagerButtonStates(pgrDetails);
                UpdatePagerInfo(pgrDetails);
            }
        }

        protected void gvDetails_Sorted(object sender, EventArgs e)
        {
            gvDetails.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void gvSCT_Sorted(object sender, EventArgs e)
        {
            gvSCT.PageIndex = PageIndex;
            UpdatePagerInfo();
        }
 
        protected void gvSCM_Sorted(object sender, EventArgs e)
        {
            gvSCM.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void gvRCT_Sorted(object sender, EventArgs e)
        {
            gvRCT.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void gvRCM_Sorted(object sender, EventArgs e)
        {
            gvRCM.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void cvDate_ServerValidate(object source, ServerValidateEventArgs args)
        {
            args.IsValid = (dtFrom.DateTime <= dtTo.DateTime);
        }
    }
}
