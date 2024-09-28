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
using ZzimaBilling.AdminUI.Forms.UserProfilePages;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.DAL;
using System.Web.UI.DataVisualization.Charting;

namespace ZzimaBilling.Admin.UserProfilePages
{
    public partial class PaymentsHistory : UserProfileGridViewPage
    {
        #region Constants

        public const string VW_DETAILS = "pwDetails";
        public const string VW_TRANSACTION = "pwTransactions";
        public const string VW_AMOUNT = "pwMoneyAmount";
        public const int TAB_MAX_LENGTH = 25;
        public const string TAB_STRIP_CSS = "tabStripFrame";
        public const string TAB_STRIP_NO_BORDER_CSS = "tabStripFrameNoBorder";
        public const int TRESHOLD = 1;

        #endregion

        #region Properties

        public Filter Filter
        {
            get
            {
                Filter filter = new Filter();
                filter.AmountFrom = ncAmount.From;
                filter.AmountTo = ncAmount.To;
                filter.DateFrom = dtFrom.DateTime;
                filter.DateTo = dtTo.DateTime;
                if (ddlPaymentSystem.Items.Count > 0)
                {
                    filter.PaymentSystem = ddlPaymentSystem.SelectedItem.Value;
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
                if (ViewState["cv"] != null && ViewState["cv"].ToString() != value)
                {
                    CurrentSortExpression = string.Empty;
                    CurrentSortDirection = string.Empty;
                    PageIndex = 0;
                }
                ViewState["cv"] = value;
            }
        }

        public bool ChartTabsVisible
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

        #region Methods

        protected void FillPaymentSystems(DropDownList ddl)
        {
            List<PSystemBLL> ppsystems = UserDAL.GetRealPaymentSystems(UserID);
            ddl.Items.Clear();
            ddl.Items.Add(new ListItem(Translate("PaymentsHistory.AllSystems"), string.Empty));
            foreach (PSystemBLL item in ppsystems)
                ddl.Items.Add(new ListItem(item.Name, item.Name));
        }

        protected void FillPaymentsSummary(PaymentsHistorySummary summary)
        {
            lblTotalCountValue.Text = summary.TotalCount.ToString();
            lblTotalAmountValue.Text = summary.TotalAmount.ToString();
            lblDiffPSValue.Text = summary.PaymentSystemsCount.ToString();
        }

        #endregion

        #region Events

        protected override void OnInit(EventArgs e)
        {
            base.OnInit(e);

            gvDetails.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);
            gvMoney.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);
            gvTransactions.RowCreated += new GridViewRowEventHandler(GridView_RowCreated);

            gvDetails.Sorting += new GridViewSortEventHandler(GridView_Sorting);
            gvMoney.Sorting += new GridViewSortEventHandler(GridView_Sorting);
            gvTransactions.Sorting += new GridViewSortEventHandler(GridView_Sorting);

            gvDetails.AllowSorting = true;
            gvMoney.AllowSorting = true;
            gvTransactions.AllowSorting = true;

            ConfigureTabs(tabControl);
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                PageIndex = 0;
                PagesCount = 0;
                FillPaymentSystems(ddlPaymentSystem);
                TabStripFrameBorderIsVisible = false;
            }

            Session["Filter"] = Filter;
            PaymentsHistorySummary summary = EmployeeDAL.getUserPaymentsSummary(UserID, Filter);

            if (summary.PaymentSystemsCount < 1)
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
                FillPaymentsSummary(summary);
                TabsAndMultiPagesVisible = true;
                TabStripFrameBorderIsVisible = true;
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

        protected void BindGridView()
        {
            List<PaymentsHistoryRecord> recs = EmployeeDAL.getUserPaymentsHistory(UserID, Filter);

            switch (CurrentView)
            {
                default:
                case VW_DETAILS:
                    gridView = gvDetails;
                    break;

                case VW_TRANSACTION:
                    gridView = gvTransactions;
                    FillAndConfigureChartCT(chrtTransactions,
                        Translate("PaymentsHistory.pwTransactions.Chart.Title"),
                        EmployeeDAL.getUserPaymentsHistoryCT(recs), TRESHOLD);
                    break;

                case VW_AMOUNT:
                    gridView = gvMoney;
                    FillAndConfigureChartCM(chrtMoneyAmount,
                        Translate("PaymentsHistory.pwMoney.Chart.Title"),
                        EmployeeDAL.getUserPaymentsHistoryCM(recs), TRESHOLD);
                    break;
            }
            gridView.DataBind();
            UpdatePagerInfo(pgrDetails);
        }

        protected void GoToFirstTab()
        {
            MultiPageDetails.SetActiveView(pwDetails);
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

        private void GetRowsCount(string p)
        {
            switch (p)
            {
                default:
                case VW_DETAILS:
                    {
                        if (gridView == null)
                            gridView = gvDetails;
                        RowsCount = EmployeeDAL.getUserPaymentsHistoryCount(UserID, Filter);
                        PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
                    }
                    break;

                case VW_TRANSACTION:
                    {
                        RowsCount = EmployeeDAL.getUserPaymentsHistoryCTCount(UserID, Filter);
                        PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
                    }
                    break;

                case VW_AMOUNT:
                    {
                        RowsCount = EmployeeDAL.getUserPaymentsHistoryCMCount(UserID, Filter);
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

        private void FillAndConfigureChartCT(Chart chart, string chartTitle,
            List<PaymentsHistoryCTRecord> records, int threshold)
        {
            if (records.Count > 0)
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
                        labels.Add(record.PaymentSystem.ToString() +
                                       ": " + record.Count.ToString() + " ("
                                       + String.Format("{0:0.##}", record.Percent) + "%)");
                    }
                }
                FillAndConfigureChart(chart, chartTitle, labels, values);
                Series series = chart.Series["Series1"];
                CustomizeSmallSegments(series, threshold);
            }
        }

        protected void FillAndConfigureChartCM(Chart chart, string chartTitle,
            List<PaymentsHistoryCMRecord> records, int threshold)
        {
            if (records.Count > 0)
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
                        labels.Add(record.PaymentSystem.ToString() +
                                       ": " + String.Format("{0:0.##}", record.Amount) + " ("
                                       + String.Format("{0:0.##}", record.Percent) + "%)");
                    }
                }
                FillAndConfigureChart(chart, chartTitle, labels, values);
                Series series = chart.Series["Series1"];
                CustomizeSmallSegments(series, threshold);
            }
        }

        protected void OnTab_ItemClick(object sender, MenuEventArgs e)
        {
            string index = (sender as System.Web.UI.WebControls.Menu).SelectedItem.Value;
            string previousView = CurrentView;

            switch (index)
            {
                case VW_DETAILS:
                    MultiPageDetails.SetActiveView(pwDetails);
                    break;
                case VW_TRANSACTION:
                    MultiPageDetails.SetActiveView(pwTransactions);
                    break;
                case VW_AMOUNT:
                    MultiPageDetails.SetActiveView(pwMoneyAmount);
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
        #endregion

        protected void gvMoney_Sorted(object sender, EventArgs e)
        {
            gvMoney.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void gvTransactions_Sorted(object sender, EventArgs e)
        {
            gvTransactions.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void gvDetails_Sorted(object sender, EventArgs e)
        {
            gvDetails.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void cvDate_ServerValidate(object source, ServerValidateEventArgs args)
        {
            args.IsValid = (dtFrom.DateTime <= dtTo.DateTime);
        }

        protected void CustomizeSmallSegments(Series series, int collectedThreshohld)
        {
            if (series != null)
            {
                series["CollectedThreshold"] = collectedThreshohld.ToString();
                series["CollectedColor"] = "Gray";
            }
        }
    }
}