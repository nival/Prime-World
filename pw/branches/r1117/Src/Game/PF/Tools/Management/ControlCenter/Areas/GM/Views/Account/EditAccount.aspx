<%@ Page Title="" Language="C#" MasterPageFile="~/Views/Shared/Site.Master" Inherits="ViewPage<AccountInfoModel>" %>

<asp:Content ID="Content1" ContentPlaceHolderID="TitleContent" runat="server">
  EditAccount
</asp:Content>

<asp:Content ID="cLinks" ContentPlaceHolderID="Links" runat="server">

  <link rel="stylesheet" href="/Content/pager.css" />
  <link href="../../Content/jquery-ui-1.8.17.custom.css" rel="stylesheet" type="text/css" />
  <style type="text/css">
    /* css for timepicker */
    .ui-timepicker-div .ui-widget-header { margin-bottom: 8px; }
    .ui-timepicker-div dl { text-align: left; }
    .ui-timepicker-div dl dt { height: 25px; margin-bottom: -25px; }
    .ui-timepicker-div dl dd { margin: 0 10px 10px 65px; }
    .ui-timepicker-div td { font-size: 90%; }
    .ui-tpicker-grid-label { background: none; border: none; margin: 0; padding: 0; }
  </style>
  
  <style type="text/css">
    .filter { border: 0px; }
    .filter td { border: 0px; }
  </style>
  
  <script type="text/javascript" src="../../Scripts/jquery-ui-1.8.16.custom.min.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery.localizeDate.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery-ui-timepicker-addon.js"></script>
  <script type="text/javascript" src="../../Scripts/jquery-ui-sliderAccess.js"></script>

  <script type="text/javascript">
      $(document).ready(function() {
        localizeDate();
        $('#LastPaymentTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
        $('#LastLampDropTime').datetimepicker({ dateFormat: 'dd.mm.yy', timeFormat: 'hh:mm:ss', showSecond: true });
      });
  </script>

</asp:Content>

<asp:Content ID="Content2" ContentPlaceHolderID="MainContent" runat="server">
  <div style="font-size: 1.2em; color: #000000; margin-bottom: 15px;">
    <%= Html.Encode( "Edit Account: " + Model.Login ) %>
  </div>

  <% using ( Html.BeginForm() ) {%>
  <%= Html.ValidationSummary() %>
  <fieldset>
    <legend>Fields</legend>
    <%= Html.HiddenFor(model => model.Auid) %>
    <%= Html.HiddenFor(model => model.Login) %>
    <%= Html.HiddenFor(model => model.Email) %>
    <%= Html.HiddenFor(model => model.TimeZone) %>
    <div class="editor-label">
      <%= Html.LabelFor( m => m.Banned )%>
      <%= Html.Encode( ( Model.Banned == null ? " : no" : " : till " + Model.Banned ) )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( m => m.Muted )%>
      <%= Html.Encode( ( Model.Muted == null ? " : no" : " : till " + Model.Muted ) )%>
    </div>
    <br />
    <div class="editor-label">
      <%= Html.LabelFor(model => model.NickName) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.NickName) %>
      <%= Html.ValidationMessageFor(model => model.NickName) %>
      <%= Html.HiddenFor(model => model.HiddenNickName) %>
    </div>
    
    <div class="editor-label">
      <%= Html.LabelFor(model => model.JoinedSNids) %>
    </div>
    <div class="editor-field">
      <% for (int i = 0; i < Model.JoinedSNids.Count; i++ ) { %>
        <%= Html.HiddenFor(m => m.JoinedSNids[i])%>
        <%= Html.Encode(Model.JoinedSNids[i])%>
        <% if (Model.JoinedSNids.Count > 1 && Model.JoinedSNids[i] != Model.SNid) %>
          <%= Html.ActionLink("delete", "DisjointSN", new { Model.Auid, sn = Model.JoinedSNids[i] },
                              new { onclick = String.Format("return confirm('Do you really want to disjoint {0} from auid={1}')", Model.JoinedSNids[i].ToUpper(), Model.Auid) })%>
          <br/>
          <%= Html.ActionLink( "set as fsn", "ChangeFSN", new { Model.Auid, sn = Model.JoinedSNids[i] },
                              new { onclick = String.Format("return confirm('Do you really want to change fsn to {0} for auid={1}')", Model.JoinedSNids[i].ToUpper(), Model.Auid) })%>
        <br/>
      <% } %>
    </div>
    
    <% if (Model.GuildBuildingLevel != -1) { %>
      <div class="editor-label">
        <%= Html.LabelFor(m => m.GuildBuildingLevel)%>
      </div>
      <div class="editor-field">
        <%= Html.TextBoxFor(model => model.GuildBuildingLevel)%>
      </div>
    <% } else { %>
      <%= Html.HiddenFor(model => model.GuildBuildingLevel)%>
    <% } %>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Fame) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Fame) %>
      <%= Html.ValidationMessageFor(model => model.Fame) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Fraction) %>
    </div>
    <div class="editor-field">
      <%= Html.DropDownListFor( model => model.Fraction, new SelectList( ( Enum.GetValues( typeof( FractionEnum ) ) ).Cast<FractionEnum>().Take( 2 ) ) )%>
      <%= Html.ValidationMessageFor(model => model.Fraction) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.Gender ) %>
    </div>
    <div class="editor-field">
      <%= Html.DropDownListFor( model => model.Gender, new SelectList( ( Enum.GetValues( typeof( GenderEnum ) ) ) ) )%>
      <%= Html.ValidationMessageFor(model => model.Gender ) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Location) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Location) %>
      <%= Html.ValidationMessageFor(model => model.Location) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Reliability) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Reliability) %>
      <%= Html.ValidationMessageFor(model => model.Reliability) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.IsRegularMMAllowed)%>
    </div>
    <div class="editor-field">
      <%= Html.CheckBoxFor(model => model.IsRegularMMAllowed)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.IsDeveloper) %>
    </div>
    <div class="editor-field">
      <%= Html.CheckBoxFor(model => model.IsDeveloper) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.IsSpectator) %>
    </div>
    <div class="editor-field">
      <%= Html.CheckBoxFor( model => model.IsSpectator )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.ExtraComplaints)%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.ExtraComplaints) %>
      <%= Html.ValidationMessageFor( model => model.ExtraComplaints)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.ExtraSessionComplaints)%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.ExtraSessionComplaints) %>
      <%= Html.ValidationMessageFor(model => model.ExtraSessionComplaints)%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor( model => model.CanMute )%>
    </div>
    <div class="editor-field">
      <%= Html.CheckBoxFor( model => model.CanMute )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.LordRating )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.LordRating) %>
      <%= Html.ValidationMessageFor( model => model.LordRating )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.DailyRating )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.DailyRating) %>
      <%= Html.ValidationMessageFor( model => model.DailyRating)%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.NumberOfWins )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.NumberOfWins) %>
      <%= Html.ValidationMessageFor( model => model.NumberOfWins )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.NumberOfWinsForPR )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.NumberOfWinsForPR) %>
      <%= Html.ValidationMessageFor( model => model.NumberOfWinsForPR )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.PlayerRating )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.PlayerRating) %>
      <%= Html.ValidationMessageFor( model => model.PlayerRating )%>
    </div>

    <div class="editor-label">
      <%= Html.LabelFor( model => model.Dodges )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Dodges) %>
      <%= Html.ValidationMessageFor( model => model.Dodges )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.RetiredTime )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.RetiredTime) %>
      <%= Html.ValidationMessageFor( model => model.RetiredTime )%>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.SwitchQuant )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.SwitchQuant ) %>
      <%= Html.ValidationMessageFor(model => model.SwitchQuant ) %>
      <%= Html.HiddenFor(model => model.HiddenSwitchQuant) %>
      <%= Html.HiddenFor(model => model.MaxFractionChangesQuant) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor( model => model.NickChangesQuant )%>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.NickChangesQuant) %>
      <%= Html.ValidationMessageFor(model => model.NickChangesQuant) %>
      <%= Html.HiddenFor(model => model.HiddenNickChanges) %>
      <%= Html.HiddenFor(model => model.MaxNickChangesQuant) %>
    </div>
    
    <div style="margin: 20px 0 10px 0;">Resources :</div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Silver) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Silver) %>
      <%= Html.ValidationMessageFor(model => model.Silver) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Resource1) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Resource1) %>
      <%= Html.ValidationMessageFor(model => model.Resource1) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Resource2) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Resource2) %>
      <%= Html.ValidationMessageFor(model => model.Resource2) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Resource3) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Resource3) %>
      <%= Html.ValidationMessageFor(model => model.Resource3) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Perl) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Perl) %>
      <%= Html.ValidationMessageFor(model => model.Perl) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.RedPerl) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.RedPerl) %>
      <%= Html.ValidationMessageFor(model => model.RedPerl) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.CWPoints) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.CWPoints) %>
      <%= Html.ValidationMessageFor(model => model.CWPoints) %>
    </div>
    <div class="editor-label">
      <%= Html.LabelFor(model => model.Shard) %>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.Shard) %>
      <%= Html.ValidationMessageFor(model => model.Shard) %>
    </div>
      <% for (int i = 0; i < Model.Currencies.Count; i++){ %>
          <div class="editor-label">
              <%= Html.Encode( Model.Currencies[i].Key )%>
              <%= Html.HiddenFor(model => model.Currencies[i].Key )%>
          </div>
          <div class="editor-field">
              <%= Html.EditorFor(model => model.Currencies[i].Value)%>
              <%= Html.ValidationMessageFor(model => model.Currencies[i].Value)%>
          </div>
      <% } %>
    <div class="editor-label">
      <label for="LastPaymentTime" class="timeZoneLabel">LastPaymentTime, UTC+0</label>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.LastPaymentTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.LastPaymentTime.HasValue ? Model.LastPaymentTime.Value.ToString("dd'.'MM'.'yyyy HH:mm:ss") : "" } })%>
    </div>
    <div class="editor-label">
      <label for="LastLampDropTime" class="timeZoneLabel">LastLampDropTime, UTC+0</label>
    </div>
    <div class="editor-field">
      <%= Html.TextBoxFor(model => model.LastLampDropTime, new Dictionary<string, object> { { "class", "utcdateVal" }, { "Value", Model.LastLampDropTime.HasValue ? Model.LastLampDropTime.Value.ToString("dd'.'MM'.'yyyy HH:mm:ss") : "" } })%>
    </div>
    <div class="editor-label" style="margin: 30px 0 10px 0;">
      <%= Html.LabelFor(model => model.MessageToUser) %>
    </div>
    <div class="editor-field">
      <%= Html.TextAreaFor( model => model.MessageToUser, new { cols = "50%", rows = "10" } )%>
      <%= Html.ValidationMessageFor(model => model.MessageToUser) %>
    </div>
    <p>
      <input type="submit" value="Save" />
    </p>
  </fieldset>
  <% } %>
  <div>
    <%= Html.ActionLink("Back to account details", "Details", new { Model.Auid })%>
  </div>
</asp:Content>