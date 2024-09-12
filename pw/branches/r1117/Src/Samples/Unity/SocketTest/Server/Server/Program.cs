using System;
using System.Text;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.IO;

public class Progremm
{

	private static List<string> _houses = new List<string>();
    const string AllPolicy =
    @"<?xml version='1.0'?>
    <cross-domain-policy>
            <allow-access-from domain=""*"" to-ports=""*"" />
    </cross-domain-policy>";

	static void ListenForRequests()
	{
		int CONNECT_QUEUE_LENGTH = 4;

		Socket server = new Socket( AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp );
        server.Bind(new IPEndPoint(IPAddress.Any, 9999));
		server.Listen( CONNECT_QUEUE_LENGTH );
        
		while ( true )
		{
			Socket client = server.Accept();
            // Send policy
            client.Send(Encoding.UTF8.GetBytes(AllPolicy));

			while (true)
			{

				if (client.Poll( 1, SelectMode.SelectRead ))
				  break;

				try
				{
					List<ArraySegment<byte>> clientData = new List<ArraySegment<byte>>();
					clientData.Add(new ArraySegment<byte>(new byte[4]));
					clientData.Add(new ArraySegment<byte>(new byte[32]));
					clientData.Add(new ArraySegment<byte>(new byte[32]));

					if (client.Receive(clientData) > 0)
					{
						ClientRequest request = GetClientRequest(clientData);

						// Validate
						if (request.header == 1)
						{
							bool isLogined = Validate(request.data0, request.data1);
							byte[] msg = new byte[4];
							msg = BitConverter.GetBytes(isLogined);
							client.Send(msg, SocketFlags.None);
						}

						// Add House
						if (request.header == 2)
						{
							_houses.Add(request.data0);
						    Console.WriteLine("Created " + request.data0);
						}

						// Get Houses
						if (request.header == 3)
						{
							MemoryStream stream = new MemoryStream();
							BinaryFormatter formatter = new BinaryFormatter();
							formatter.Serialize(stream, _houses);
							client.Send(stream.ToArray(), SocketFlags.None);
							stream.Close();
						}
					}
				}
				catch (SocketException e)
				{
					break;
				}

				//byte[msg = new byte[1024];
				//// Send the data.
				//msg = Encoding.UTF8.GetBytes( "Hello World!" );
				//client.Send( msg, SocketFlags.None );
			}
		}
	}
	static void Main()
	{
		// Start the listening thread.
		Thread listener = new Thread( new ThreadStart( ListenForRequests ) );
		listener.IsBackground = true;
		listener.Start();

		Console.WriteLine( "Press <enter> to quit" );
		Console.ReadLine();
	}
	static bool Validate(string login, string pass)
	{
		login = login.Trim('\0');
		pass = pass.Trim('\0');

		Console.WriteLine("Login {0}, Pass {1}", login, pass);

		if ( login == "Nival" && pass == "Network" )
			return true;
		return false;
	}
	static ClientRequest GetClientRequest( List<ArraySegment<byte>> clientData )
	{
		ClientRequest result = new ClientRequest();
		result.header = BitConverter.ToInt32(clientData[0].Array, 0);
		result.data0 = Encoding.UTF8.GetString(clientData[1].Array);
		result.data1 = Encoding.UTF8.GetString(clientData[2].Array);
		return result;
	}
}
public class ClientRequest
{
	public int header;
	public string data0;
	public string data1;
}
