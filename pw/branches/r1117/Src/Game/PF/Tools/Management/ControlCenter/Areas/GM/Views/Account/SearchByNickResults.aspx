<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="System.Web.Mvc.ViewPage<IEnumerable<AccountInfoModel>>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
	SearchByNickResults
</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">

    <h2>SearchByNickResults</h2>
    
    <table>
      <tr>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().Login) %>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().Fraction) %>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().Fame)%>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().Gender)%>
        </th>
        <th>
          <%= Html.LabelFor(m => m.FirstOrDefault().RegisterDate)%>
        </th>
      </tr>
      <% foreach ( var item in Model )
         { %>
      <tr>
        <td>
          <%= Html.Encode(item.Login) %>
        </td>
        <td>
          <%= Html.Encode(item.Fraction) %>
        </td>
        <td>
          <%= Html.Encode(item.Fame) %>
        </td>
        <td>
          <%= Html.Encode(item.Gender) %>
        </td>
        <td>
          <%= Html.Encode(item.RegisterDate) %>
        </td>
        <td>
          <%= Html.ActionLink( "view", "Details", "Account", new { login = item.Login }, new { } )%>
        </td>
      </tr>
      <% } %>
    </table>

</asp:Content>

<asp:Content ID="Content3" ContentPlaceHolderID="Links" runat="server">
</asp:Content>
