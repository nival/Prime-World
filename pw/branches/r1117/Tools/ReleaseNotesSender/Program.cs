// Проверяет URL на обновление (при этом хранит последнюю проверенную версию у себя в папке)
// и если есть изменения, шлет страницу на email 
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Mail;
using System.Security.Cryptography;
using System.Text;

namespace ReleaseNotesSender
{
  class Program
  {
    static void Main( string[] args )
    {
      string URL =
        "http://SITE";
      
      string file =  getMd5Hash(URL);
      string oldContent = null;
      if ( File.Exists( file ) )
        oldContent = File.ReadAllText( file, Encoding.UTF8 );

      HttpWebRequest wr= (HttpWebRequest) WebRequest.Create(
                                            "http://SITE" );
      wr.Method = "POST";
      wr.ContentType = "application/x-www-form-urlencoded";
      string param =  "&os_username=Botforasaturov&os_password=password";
      wr.ContentLength = param.Length;

      // Write the request 
      StreamWriter stOut = new StreamWriter( wr.GetRequestStream(), Encoding.ASCII );
      stOut.Write( param );
      stOut.Close(); 
      

      string resp = new StreamReader(wr.GetResponse().GetResponseStream()).ReadToEnd();
      resp = resp.Remove( 0, resp.IndexOf( "MAIL_MARKER_START" ) + 17 );
      resp = resp.Remove(resp.IndexOf( "MAIL_MARKER_END" )-17);
      resp = @"<style>
confluenceTh
{
white-space:nowrap;
font-family:Verdana;
font-size:11px;
}

table.confluenceTable
{
border-collapse:collapse;
margin:5px;
font-family:Verdana;
font-size:11px;
}

td.confluenceTd, table.confluenceTable td.confluenceTd  {
border:1px solid #CCCCCC;
padding:3px 4px;
vertical-align:top;
font-family:Verdana;
font-size:11px;
}

th.confluenceTh, table.confluenceTable th.confluenceTh {
background-color:#F0F0F0;
border:1px solid #CCCCCC;
padding:3px 4px;
text-align:center;
vertical-align:top;
font-family:Verdana;
font-size:11px;
}
</style>" + resp;

      if ( oldContent == resp )
        return;

      System.Net.Mail.SmtpClient smtp = new System.Net.Mail.SmtpClient("mail.SITE.com", 25);
			smtp.Credentials = new NetworkCredential( "cred.com", "secret" );
      smtp.Send( new MailMessage( "confluence", "mail",
                                  "PF Editor Release Notes Updated", resp )
                   {IsBodyHtml = true});
      
      File.WriteAllText( file, resp, Encoding.UTF8 );
    }

    static string getMd5Hash( string input )
    {
      MD5 md5Hasher = MD5.Create();
      byte[] data = md5Hasher.ComputeHash( Encoding.Default.GetBytes( input ) );

      StringBuilder sBuilder = new StringBuilder();

      for ( int i = 0; i < data.Length; i++ )
        sBuilder.Append( data[i].ToString( "x2" ) );
      
      return sBuilder.ToString();
    }

    

  }
}
