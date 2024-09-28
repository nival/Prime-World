using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Web;
using System.Web.UI.WebControls;
using System.Data;
using System.Web.UI.DataVisualization.Charting;
using ZzimaBilling.AdminUI.DAL;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public class UserProfileGridViewPage:UserProfileBasePage
    {
        #region Fields

        private LinkButton btnFirst = null;
        private LinkButton btnPrevious = null;
        private LinkButton btnNext = null;
        private LinkButton btnLast = null;
        private Label lblCountRows;
        private Label lblPageCount;
        private Label lblPageNumber;
        public GridView gridView;

        #endregion

        #region Properties

        public int PageIndex
        {
            get
            {
                if (ViewState["pi"] == null)
                {
                    ViewState["pi"] = 0;
                }
                return Convert.ToInt32(ViewState["pi"]);
            }
            set
            {
                if (value >= 0)
                {
                    ViewState["pi"] = value;
                    if (gridView != null)
                        gridView.PageIndex = value;
                }
            }
        }

        public int RowsCount
        {
            get
            {
                if (ViewState["rcount"] == null)
                {
                    ViewState["rcount"] = 0;
                }
                return Convert.ToInt32(ViewState["rcount"]);
            }
            set
            {
                if (value >= 0)
                    ViewState["rcount"] = value;
            }
        }

        public int PagesCount
        {
            get
            {
                if (ViewState["pcount"] == null)
                {
                    ViewState["pcount"] = 0;
                }
                return Convert.ToInt32(ViewState["pcount"]);
            }
            set
            {
                if (value >= 0)
                    ViewState["pcount"] = value;
            }
        }

        public string CurrentSortExpression
        {
            get
            {
                if (ViewState["sortExpression"] != null)
                {
                    return ViewState["sortExpression"].ToString();
                }
                else
                {
                    ViewState["sortExpression"] = string.Empty;
                    return string.Empty;
                }
            }
            set
            {
                ViewState["sortExpression"] = value;
            }
        }

        public string CurrentSortDirection
        {
            get
            {
                if (ViewState["sortDirection"] != null)
                {
                    return ViewState["sortDirection"].ToString();
                }
                return string.Empty;
            }
            set
            {
                ViewState["sortDirection"] = value;
            }
        } 

        #endregion

        #region Events

        protected void GridViewSortImages(object sender, GridViewRowEventArgs e)
        {
            GridView senderGridView = (GridView)sender;
            Literal space = new Literal();
            space.Text = "    ";
            if (e.Row != null && e.Row.RowType == DataControlRowType.Header)
            {
                for (int i = 0; i < senderGridView.Columns.Count; i++)
                {
                    TableCell cell = e.Row.Cells[i];
                    DataControlField column = senderGridView.Columns[i];

                    if (cell.HasControls())
                    {
                        LinkButton button = cell.Controls[0] as LinkButton;
                        if (button != null)
                        {
                            if (CurrentSortExpression == column.SortExpression)
                            {
                                if (CurrentSortDirection == "asc")
                                    cell.ControlStyle.CssClass = "headerRowAsc";
                                else if (CurrentSortDirection == "desc")
                                    cell.ControlStyle.CssClass = "headerRowDesc";
                            }
                        }
                    }
                }
            }
        }

        protected virtual void Navigate(object sender, EventArgs e)
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
            UpdatePagerInfo();
            //ods needs to bind
        }

        #endregion

        #region Methods

        protected void SetPagerButtonStates(Panel pnlPager)
        {
            // get controls
            lblCountRows = (Label)pnlPager.FindControl("lblCount");
            lblPageCount = (Label)pnlPager.FindControl("TotalPagesLabel");
            lblPageNumber = (Label)pnlPager.FindControl("PageNumberLabel");
            btnFirst = (LinkButton)pnlPager.FindControl("lnkFirstPage");
            btnPrevious = (LinkButton)pnlPager.FindControl("lnkPrevPage");
            btnNext = (LinkButton)pnlPager.FindControl("lnkNextPage");
            btnLast = (LinkButton)pnlPager.FindControl("lnkLastPage");

            // define events
            btnFirst.Click += new EventHandler(Navigate);
            btnPrevious.Click += new EventHandler(Navigate);
            btnLast.Click += new EventHandler(Navigate);
            btnNext.Click += new EventHandler(Navigate);
        }

        protected virtual void UpdatePagerInfo()
        {
            // set labels
            lblCountRows.Text = RowsCount.ToString();
            lblPageCount.Text = PagesCount.ToString();

            lblPageNumber.Text = (PagesCount != 0 ? PageIndex + 1 : 0).ToString();
            btnFirst.Enabled = btnPrevious.Enabled = (PageIndex != 0);
            btnNext.Enabled = btnLast.Enabled = (PageIndex < (PagesCount - 1));
        }

        protected void UpdatePagerInfo(Panel panel)
        {
            Label lblCountRows = (Label)panel.FindControl("lblCount");
            Label lblPageCount = (Label)panel.FindControl("TotalPagesLabel");
            Label lblPageNumber = (Label)panel.FindControl("PageNumberLabel");

            LinkButton btnFirst, btnNext, btnLast, btnPrevious;
            btnFirst = (LinkButton)panel.FindControl("lnkFirstPage");
            btnPrevious = (LinkButton)panel.FindControl("lnkPrevPage");
            btnNext = (LinkButton)panel.FindControl("lnkNextPage");
            btnLast = (LinkButton)panel.FindControl("lnkLastPage");

            // set labels
            lblCountRows.Text = RowsCount.ToString();
            lblPageCount.Text = PagesCount.ToString();

            lblPageNumber.Text = (PagesCount != 0 ? PageIndex + 1 : 0).ToString();
            btnFirst.Enabled = btnPrevious.Enabled = (PageIndex != 0);
            btnNext.Enabled = btnLast.Enabled = (PageIndex < (PagesCount - 1));
        }

        protected void GetRowsCount(GridView gridView)
        {
            RowsCount = gridView.Rows.Count;
            PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
        } 

        #endregion

        #region Chart Methods

        private void AddTitleToChart(Chart chart, string title)
        {
            if (chart != null)
            {
                chart.Titles.Clear();
                Title chartTitle = new Title(title);
                chart.Titles.Add(chartTitle);
            }
        }

        protected void FillAndConfigureChart(Chart chart, string chartTitle,
              List<string> labels, List<decimal> values)
        {
            AddTitleToChart(chart, chartTitle);
            chart.Series["Series1"].Points.DataBindXY(labels, values);
            chart.Series["Series1"]["PieLabelStyle"] = "Outside";
            foreach (DataPoint point in chart.Series["Series1"].Points)
            {
                point["Exploded"] = "true";
            }
        }

        protected void CustomizeSmallSegments(Series series, int collectedThreshohld)
        {
            if (series != null)
            {
                series["CollectedThreshold"] = collectedThreshohld.ToString();
                series["CollectedLegendText"] = "Остальные";
                series["CollectedColor"] = "Gray";
                series["CollectedToolTip"] = "Остальные";

            }
        }
        #endregion
    }
}
