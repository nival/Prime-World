using System;
using System.Collections;
using System.Net;
using System.Net.Sockets;
using System.Security;
using System.Text;
using UnityEngine;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

class Client : MonoBehaviour
{

	Socket _sock = new Socket( AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp );
	IPAddress _host = IPAddress.Parse( "127.0.0.1" );

	private string _login = string.Empty;
	private string _pass = string.Empty;
	private static bool _showLoginWin = true;
	private string _message = "";

	private void Start()
	{
        Debug.Log(Security.PrefetchSocketPolicy("127.0.0.1", 9999, 1000)); 
        SetConnection();
	}

	private void SetConnection()
	{
        IPEndPoint hostep = new IPEndPoint(_host, 9999);
		
		// Set Connection
		try
		{
			_sock.Connect( hostep );
		    byte[] policy = new byte[1024];
		    _sock.Receive(policy);
		}
		catch ( SocketException e )
		{
			_message = "Problem connecting to _host" ;
			return;
		}

		_message = "Connected";
	}
	private void Send()
	{
		//Send
		try
		{
			_sock.Send( Encoding.ASCII.GetBytes( "Testing" ) );
		}
		catch ( SocketException e )
		{
			Console.WriteLine( "Problem sending data" );
			Console.WriteLine( e.ToString() );
		}
	}
	private void Validate()
	{
		//Send
		try
		{
			ArraySegment<byte> header = new ArraySegment<byte>(BitConverter.GetBytes(1));
			byte[] loginBytes = Encoding.UTF8.GetBytes( _login );
			byte[] passBytes = Encoding.UTF8.GetBytes( _pass );
			byte[] loginS = new byte[32];
			byte[] passS = new byte[32];
			loginBytes.CopyTo( loginS, 0 );
			passBytes.CopyTo( passS, 0 );
			ArraySegment<byte> login = new ArraySegment<byte>( loginS );
			ArraySegment<byte> pass = new ArraySegment<byte>( passS );
			List<ArraySegment<byte>> loginData = new List<ArraySegment<byte>>();
			loginData.Add( header );
			loginData.Add(login);
			loginData.Add(pass);
			_sock.Send( loginData );

			byte[] msg = new byte[4];
			_sock.Receive(msg);
			bool logined = BitConverter.ToBoolean( msg, 0 );

			if ( logined )
			{
				_showLoginWin = false;
			    _message= "Success" ;    
			}
			else
				_message = "Not success";
		}
		catch ( SocketException e )
		{
			Console.WriteLine( "Problem sending data" );
			Console.WriteLine( e.ToString() );
		}
	}
	private void OnDisable()
	{
		Debug.Log("Closed");
		_sock.Shutdown(SocketShutdown.Both);
		_sock.Close();
	}
	private void OnGUI()
	{
		if(_showLoginWin)
			GUI.Window(0, new Rect(100, 50, 300, 150), LoginWindow, "Login");
		else
		{
			if(GUI.Button(new Rect(100,50,300,50),"BuildHouse"))
			{
				CreateHouse("Big House "+UnityEngine.Random.Range(1,100).ToString());
			}
			if ( GUI.Button( new Rect( 100, 120, 300, 50 ), "GetHouses" ) )
			{
				GetHouses();
			}
		}


		GUIStyle box = new GUIStyle(GUI.skin.box);
		box.wordWrap = true;
		box.alignment = TextAnchor.UpperLeft;
		GUI.Box( new Rect( 0, 200, 1000, 600 ), _message, box );
	}
  private void CreateHouse(string name)
    {
        //Send
        try
        {
            ArraySegment<byte> header = new ArraySegment<byte>(BitConverter.GetBytes(2));
            byte[] loginBytes = Encoding.UTF8.GetBytes(name);
            _message = "Create " + name;
            byte[] passBytes = Encoding.UTF8.GetBytes(string.Empty);
            byte[] loginS = new byte[32];
            byte[] passS = new byte[32];
            loginBytes.CopyTo(loginS, 0);
            passBytes.CopyTo(passS, 0);
            ArraySegment<byte> login = new ArraySegment<byte>(loginS);
            ArraySegment<byte> pass = new ArraySegment<byte>(passS);
            List<ArraySegment<byte>> loginData = new List<ArraySegment<byte>>();
            loginData.Add(header);
            loginData.Add(login);
            loginData.Add(pass);
            _sock.Send(loginData);
        }
        catch (SocketException e)
        {
            Console.WriteLine("Problem sending data");
            Console.WriteLine(e.ToString());
        }
    }
	private void GetHouses()
	{
		//Send
		try
		{
			ArraySegment<byte> header = new ArraySegment<byte>( BitConverter.GetBytes( 3 ) );
			byte[] loginBytes = Encoding.UTF8.GetBytes( string.Empty );
			byte[] passBytes = Encoding.UTF8.GetBytes( string.Empty );
			byte[] loginS = new byte[32];
			byte[] passS = new byte[32];
			loginBytes.CopyTo( loginS, 0 );
			passBytes.CopyTo( passS, 0 );
			ArraySegment<byte> login = new ArraySegment<byte>( loginS );
			ArraySegment<byte> pass = new ArraySegment<byte>( passS );
			List<ArraySegment<byte>> loginData = new List<ArraySegment<byte>>();
			loginData.Add( header );
			loginData.Add( login );
			loginData.Add( pass );
			_sock.Send( loginData );

			byte[] msg = new byte[1024];
			_sock.Receive( msg );
			MemoryStream stream = new MemoryStream(msg);
			BinaryFormatter formatter = new BinaryFormatter();
			List<string> houses = formatter.Deserialize( stream ) as List<string>;
		    stream.Close();

			_message = string.Empty;
			foreach(string house in houses)
			{
				_message+="\n"+ house;
			}
		}
		catch ( SocketException e )
		{
			Console.WriteLine( "Problem sending data" );
			Console.WriteLine( e.ToString() );
		}
	}
	private void LoginWindow(int WindowID)
	{
		GUI.Label(new Rect(20, 40, 100, 20), "Login");
		GUI.Label( new Rect( 20, 70, 100, 20 ), "Password" );
		_login = GUI.TextField( new Rect( 90, 40, 100, 20 ), _login, 25 );
		_pass = GUI.PasswordField( new Rect( 90, 70, 100, 20 ), _pass, "*"[0], 25 );

		if(GUI.Button(new Rect(70,110,100,20),"Login"))
		{
			Validate();
		}
	}
}