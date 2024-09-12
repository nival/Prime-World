<%@ Page Title="" Language="C#" Inherits="System.Web.Mvc.ViewPage<ControlCenter.Areas.GM.Models.PayServiceModel>" MasterPageFile="~/Views/Shared/Site.Master" %>

<asp:Content runat="server" ID="Title" ContentPlaceHolderID="TitleContent">
Purchase paid service
</asp:Content>

<asp:Content runat="server" ID="Main" ContentPlaceHolderID="MainContent">
  <h2 style="color:Red">Purchase paid service for user <%= Model.Login %></h2>

  <% using (Html.BeginForm()) {%>
  <%= Html.ValidationSummary(true) %>
  <fieldset>
    <legend>Premium account</legend>

    <%= Html.HiddenFor(model => model.Login) %>
    <%= Html.HiddenFor(model => model.PremiumAccountDate) %>
    
    <div>
      <% if (Model.PremiumAccountDate.HasValue) { %>
        <span style="color: red; font-weight: bold">ACTIVE</span> until <%= Model.PremiumAccountDate %> UTC<br/>
        (<%= Math.Round((Model.PremiumAccountDate.Value - DateTime.UtcNow).TotalDays, 1) %> days remaining)
      <% } else { %>
        <span style="font-weight: bold">INACTIVE</span>
      <% } %>
    </div>

    <div style="margin-top: 15px">
      <%= Html.ValidationMessageFor(m => m.ServiceTypeId) %>
      <% if (!ViewData.ModelState.IsValidField("ServiceTypeId")) { %> <br/> <% } %>
      <% foreach (var type in Model.GetAllTypes()) { %>
        <%= Html.RadioButtonFor(m => m.ServiceTypeId, type.Id)%>
        <%= Html.Encode(type.Desc) %>
        <br/>
      <% } %>
    </div>

    <div style="margin-top: 15px">
      <%= Html.ValidationMessageFor(m => m.Days) %>
      <% if (!ViewData.ModelState.IsValidField("Days")) { %> <br/> <% } %>
      <%= Html.TextBoxFor(m => m.Days, new { style = "width: 50px"}) %>
      <%= Html.LabelFor(m => m.Days) %>
    </div>

    <input type="submit" value="Submit" style="margin:15px 0 0 0"/>
  </fieldset>
  <% } %>
  
  <div>
    <%= Html.ActionLink("Back to account details", "Details", new { login = Model.Login })%>
  </div>

</asp:Content>
