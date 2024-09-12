<%@ Page Language="C#" MasterPageFile="~/AdminUI/Templates/ZzimaMaster.Master" AutoEventWireup="true"
    CodeBehind="Templates.aspx.cs" Inherits="ZzimaBilling.AdminUI.Forms.Templates"
    ValidateRequest="false" EnableEventValidation="true" Title="<%$ resources:AdminUI, Title.Templates %>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="BodyPlaceHolder" runat="server">
    <link href="../../css/Templates.css" rel="stylesheet" type="text/css" />
    <link href="../../css/Grid.css" rel="stylesheet" type="text/css" />

    <script language="javascript" type="text/javascript">

        var msgConfirmEdit = "<%#getEditConfirm() %>";
        var msgConfirmDel = "<%#getDelConfirm() %>";



        function select(row, rowIndex) {
            var prevSel = document.getElementById('<%# inp_row_index.ClientID %>');
            var prevRow = document.getElementById("row" + prevSel.value);

            var conf = true;
            //test
            prevSel.value = rowIndex;
            var panel = document.getElementById('<%#DetailsFrame.ClientID %>');
            //Если панель с шаблоном открыта
            if (panel != null && panel.attributes.getNamedItem("src").value != "")
            //Спрашиваем отменить ли изменения
                conf = confirm(msgConfirmEdit);
            if (conf) {
                if (panel != null && panel.attributes.getNamedItem("src").value != "") {
                    panel.style.display = "none";
                    panel.attributes.getNamedItem("src").value = "";
                    panel.style.display = "none";
                }
                if (prevRow != null && prevRow.attributes.getNamedItem("st") != null) {
                    prevRow.className = prevRow.attributes.getNamedItem("st").value;
                }
                prevSel.value = rowIndex;
                row.className = "selectRow";
                enableButtons(true);
            }
            return conf;
        }

        function onLoadT() {
            var prevSel = document.getElementById('<%#inp_row_index.ClientID %>');
            if (prevSel) {
                var prevRow = document.getElementById("row" + prevSel.value);
                enableButtons(true);
                if (prevRow) {
                    prevRow.scrollIntoView(false);
                }
                else {
                    enableButtons(false);
                }
            }
            
        }

        function clearSelected() {
            var prevSel = document.getElementById('<%#inp_row_index.ClientID %>');
            if (prevSel) {
                prevSel.value = "";
                enableButtons(false);
            }
        }

        function onDelete() {
            var conf = false;
            conf = confirm(msgConfirmDel);
            if (conf) {
                __doPostBack("btnDel", "btnDelete_click");  
            }
            
            return conf;
        }

        function onAdd() {
            var conf = true;
            var panel = document.getElementById('<%#DetailsFrame.ClientID %>');
            if (panel != null && panel.attributes.getNamedItem("src").value != "")
                conf = confirm(msgConfirmEdit);
            if (conf) {
                //clearSelected();
                __doPostBack("btnEdit", "btnEdit_click");
            }
            return conf;
        }

        function enableButtons(enable) {
            var editBtn = document.getElementById('<%#btnEdit.ClientID %>');
            if (editBtn) {
                enableEditButton(enable);
            }
            var delBtn = document.getElementById('<%#btnDelete.ClientID %>');
            if (delBtn) {
                enableDeleteButton(enable);
            }
        }

        function enableDeleteButton(enable) {
            var delBtn = document.getElementById('<%#btnDelete.ClientID %>');
            var imgBtn = document.getElementById('<%#imgDelete.ClientID %>');
            if (enable) {
                if (imgBtn && delBtn) {
                    imgBtn.style.display = 'none';
                    delBtn.style.display = 'block';
                }
            }
            else {
                if (imgBtn && delBtn) {
                    imgBtn.style.display = 'block';
                    delBtn.style.display = 'none';
                }
            }
        }

        function enableEditButton(enable) {
            var delBtn = document.getElementById('<%#btnEdit.ClientID %>');
            var imgBtn = document.getElementById('<%#imgEdit.ClientID %>');
            if (enable) {
                if (imgBtn && delBtn) {
                    imgBtn.style.display = 'none';
                    delBtn.style.display = 'block';
                }
            }
            else {
                if (imgBtn && delBtn) {
                    imgBtn.style.display = 'block';
                    delBtn.style.display = 'none';
                }
            }
        }

//        function enableEditButton(enable) {
//            var editBtn = document.getElementById('<%#btnEdit.ClientID %>');
//            if (enable) {
//                editBtn.disabled = '';
//                editBtn.setAttribute('onclick', 'onAdd()');
//            }
//            else {
//                editBtn.disabled = 'disabled';
//            }
//        }

    </script>

    <input id="inp_row_index" name="inp_row_index" type="hidden" runat="server" />
    <asp:Button ID="btnRefreshGrid" runat="server" Text="" Visible="false" />
    <table style="padding-top: 10px; width: 100%;">
        <tr height="30px">
            <td valign="middle">
                <table>
                    <tr height="30px">
                        <td class="underLabel">
                            <asp:Label ID="lblListOfTemplatesTitle" runat="server" Text="<%$resources: AdminUI, Templates.ListTitle %>"></asp:Label>
                            <img alt="" src="../../Images/arrow.gif" class="arrowIcon" />
                        </td>
                    </tr>
                </table>
            </td>
            <td align="right">
                <div>
                    <table>
                        <tr>
                            <td class="buttonTempl">
                                <asp:ImageButton ID="btnAdd" runat="server" ImageUrl="~/AdminUI/Images/icon-add.gif"
                                    OnClientClick="return onAdd()" OnClick="btnAdd_Click" ToolTip="<%$resources: AdminUI, Templates.Add.Tooltip %>" />
                            </td>
                            <td class="buttonSep">
                                &nbsp;
                            </td>
                            <td class="buttonTempl">
                                 <img src="../../Images/icon-edit.gif"  id="btnEdit" runat="server" style="display:none"
                                    onclick="return onAdd()"  alt="<%$resources: AdminUI, Templates.Edit.Tooltip %>"  class="buttonTemplDel"/>
                                <img src="../../Images/icon-edit.gif"  id="imgEdit" runat="server" style="display:block"
                                    alt="<%$resources: AdminUI, Templates.Edit.Tooltip %>"/>  
                            </td>
                            <td class="buttonSep">
                                &nbsp;
                            </td>
                            <td class="buttonTempl">
                                <img src="../../Images/icon-delete.gif"  id="btnDelete" runat="server" style="display:none"
                                    onclick="return onDelete()"  alt="<%$resources: AdminUI, Templates.Delete.Tooltip %>"  class="buttonTemplDel"/>
                                <img src="../../Images/icon-delete.gif"  id="imgDelete" runat="server" style="display:block"
                                    alt="<%$resources: AdminUI, Templates.Delete.Tooltip %>"/>
                            </td>
                        </tr>
                    </table>
            </td>
        </tr>
        <tr height="250px">
            <td colspan="2" valign="top">
                <div class="gridAreaTemplates">
                    <asp:Panel ID="gvPagerRow" runat="server">
                        <table cellpadding="0" cellspacing="0" width="100%">
                            <tr>
                                <td align="left">
                                    <div>
                                        <table>
                                            <tr class="pagerRowHeight">
                                                <td>
                                                    &nbsp;
                                                </td>
                                                <td>
                                                    <asp:Label ID="lblTotalCount" runat="server" Text="<%$ resources:AdminUI, Templates.TotalCount %>"></asp:Label>
                                                </td>
                                                <td>
                                                    &nbsp;
                                                </td>
                                                <td>
                                                    <asp:Label ID="lblCount" class="labelCount" runat="server" Text="0"></asp:Label>
                                                </td>
                                            </tr>
                                        </table>
                                    </div>
                                </td>
                                <td align="right">
                                    <div>
                                        <table>
                                            <tr>
                                                <td align="right">
                                                    <asp:Literal ID="Literal9" runat="server" Text="<%$ resources: AdminUI, Pager.Page%>" />
                                                    <asp:Label ID="PageNumberLabel" CssClass="labelCount" runat="server" />
                                                    <asp:Literal ID="Literal10" runat="server" Text="<%$ resources: AdminUI, Pager.Of%>" />
                                                    <asp:Label ID="TotalPagesLabel" CssClass="labelCount" runat="server" />
                                                </td>
                                                <td width="20px">
                                                    &nbsp;
                                                </td>
                                                <td>
                                                    <asp:LinkButton ID="lnkFirstPage" CommandName="Page" CommandArgument="First" runat="server"
                                                        CssClass="labelCount" Text="<%$ resources: AdminUI, Pager.First %>" ToolTip="<%$ resources: AdminUI, Pager.Tip.First %>"></asp:LinkButton>
                                                </td>
                                                <td>
                                                    <asp:LinkButton ID="lnkPrevPage" CommandName="Page" CommandArgument="Prev" runat="server"
                                                        Text="<%$ resources: AdminUI, Pager.Prev %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Prev %>"></asp:LinkButton>
                                                </td>
                                                <td>
                                                    <asp:LinkButton ID="lnkNextPage" CommandName="Page" CommandArgument="Next" runat="server"
                                                        Text="<%$ resources: AdminUI, Pager.Next %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Next %>"></asp:LinkButton>
                                                </td>
                                                <td>
                                                    <asp:LinkButton ID="lnkLastPage" CommandName="Page" CommandArgument="Last" runat="server"
                                                        Text="<%$ resources: AdminUI, Pager.Last %>" CssClass="labelCount" ToolTip="<%$ resources: AdminUI, Pager.Tip.Last %>"></asp:LinkButton>
                                                </td>
                                            </tr>
                                        </table>
                                    </div>
                                </td>
                            </tr>
                        </table>
                    </asp:Panel>
                    <asp:GridView ID="gvTemplates" runat="server" AutoGenerateColumns="False" DataSourceID="odsTemplates"
                        OnRowCreated="gvTemplates_RowCreated" OnSelectedIndexChanged="gvTemplates_SelectedIndexChanged"
                        GridLines="Vertical" BorderWidth="1px" BorderStyle="Solid" BorderColor="#3B3C37"
                        CellPadding="0" Width="100%" AllowPaging="True" AllowSorting="True" PageSize="6"
                        OnSorting="gvTemplates_Sorting" OnSorted="gvTemplates_Sorted">
                        <Columns>
                            <asp:BoundField DataField="TemplateID" HeaderText="ID" SortExpression="TemplateID"
                                HeaderStyle-CssClass="columnInv">
                                <HeaderStyle CssClass="columnInv"></HeaderStyle>
                                <ItemStyle CssClass="columnInv" />
                            </asp:BoundField>
                            <asp:BoundField DataField="Name" HeaderText="<%$resources: AdminUI, Templates.NameTitle %>"
                                SortExpression="Name">
                                <ItemStyle Width="20%" />
                            </asp:BoundField>
                            <asp:BoundField DataField="Mask" HeaderText="<%$resources: AdminUI, Templates.MaskTitle %>"
                                SortExpression="Mask">
                                <ItemStyle />
                            </asp:BoundField>
                        </Columns>
                        <PagerStyle HorizontalAlign="Right" />
                        <HeaderStyle CssClass="headerRow" VerticalAlign="Middle" />
                        <PagerSettings Position="Top" Visible="False" />
                        <RowStyle CssClass="normalRow" />
                        <AlternatingRowStyle CssClass="alternativeRow" />
                    </asp:GridView>
                </div>
            </td>
        </tr>
        <asp:ObjectDataSource ID="odsTemplates" runat="server" SelectMethod="getTemplatesTable"
            TypeName="ZzimaBilling.AdminUI.Forms.Templates"></asp:ObjectDataSource>
        <tr height="10px">
            <td class="templateSeparator" colspan="2">
                &nbsp;
            </td>
        </tr>
        <tr height="250px" valign="top">
            <td colspan="2" width="100%">
                <!--TemplateDetails div-->
                <iframe id="DetailsFrame" runat="server" scrolling="no" style="width: 1000px; height: 250px"
                    frameborder="0"></iframe>
            </td>
        </tr>
    </table>
</asp:Content>
