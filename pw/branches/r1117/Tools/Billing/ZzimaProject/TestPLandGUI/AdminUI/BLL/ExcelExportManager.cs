using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI.WebControls;
using System.IO;
using System.Web.UI;
using System.Data;

namespace ZzimaBilling.AdminUI.BLL
{
    public class ExcelExportManager
    {
        public static void PrepareAndExport(string fileTitle, GridView gridView, bool showGrid)
        {
            string fileName = String.Format("{0}-{1}.xls", fileTitle, DateTime.Now.ToString("yyyyMMdd_HHmmss"));
            gridView.AllowPaging = false;
            gridView.DataBind();
            ExcelExportManager.Export(fileName, gridView, showGrid);
        }

        public static void Export(string fileName, GridView gridView, bool showGrid)
        {
            HttpContext.Current.Response.Buffer = true;
            HttpContext.Current.Response.ClearContent();
            HttpContext.Current.Response.ClearHeaders();
            HttpContext.Current.Response.ContentType = "application/vnd.xls";
            HttpContext.Current.Response.AddHeader("content-disposition", "attachment;filename=" + fileName);

            StringWriter sw = new StringWriter();
            HtmlTextWriter htw = new HtmlTextWriter(sw);
            //Create a form to contain the grid
            Table table = new Table();
            if (showGrid)
            {
                table.GridLines = gridView.GridLines;
            }
            else
            {
                table.GridLines = GridLines.None;
            }

            //Add the header row to the table
            if (gridView.HeaderRow != null)
            {
                PrepareControlForExport(gridView.HeaderRow);
                table.Rows.Add(gridView.HeaderRow);
            }
            foreach (GridViewRow row in gridView.Rows)
            {
                PrepareControlForExport(row);
                table.Rows.Add(row);
            }
            if (gridView.FooterRow != null)
            {
                PrepareControlForExport(gridView.FooterRow);
                table.Rows.Add(gridView.FooterRow);
            }
            //Render the table into the htmlwriter
            table.RenderControl(htw);
            //Render the htmlwriter into the response
            HttpContext.Current.Response.Write(sw.ToString());
            HttpContext.Current.Response.End();
        }

        private static void PrepareControlForExport(Control control)
        {
            int i = 0;
            while (i < control.Controls.Count)
            {
                Control current = control.Controls[i];
                if (current is LinkButton)
                {
                    control.Controls.Remove(current);
                    control.Controls.AddAt(i, new LiteralControl(((LinkButton)current).Text));
                }
                if (current.HasControls())
                {
                    PrepareControlForExport(current);
                }
                i++;
            }
        }

        //public static DataTable ToDataTable(GridView gridView)
        //{
        //    DataTable table = new DataTable();
        //    foreach (GridViewRow row in gridView.Rows)
        //    {
        //        table.Rows.Add(row);
        //    }
        //    return table;
        //}

    }
}
