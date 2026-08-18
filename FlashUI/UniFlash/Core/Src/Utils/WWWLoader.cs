using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

namespace Flash.Utils
{
  public class WWWLoader
  {
    public string Url
    {
      get { return _www.url; }
    }
    public string Error
    {
      get { return _www.error; }
    }
    public bool IsDone
    {
      get { return _www.isDone; }
    }
    public Dictionary<string, string> ResponseHeaders
    {
      get { return _www.GetResponseHeaders(); }
    }
    private Action<WWWLoader> _actionFinished;
    private UnityWebRequest _www;
    public UnityWebRequest Www
    {
      get { return _www; }
    }

    public WWWLoader(string url, Action<WWWLoader> actionFinished)
    {
      _actionFinished = actionFinished;
      _www = UnityWebRequest.Get(url);
    }
    public virtual void Finished()
    {
      _actionFinished(this);
    }
    public override string ToString()
    {
      return "Error: " + (!String.IsNullOrEmpty(Error) ? Error : "Null") + "; IsDone: " + IsDone;
    }
  }

	public class ImageLoader : WWWLoader
	{
	  private Texture2D _image;
		public Texture2D Image
		{
			get
			{
			  return _image;
			}
		}

		public ImageLoader(string url, Action<WWWLoader> actionFinished) : base (url,actionFinished)
		{
			UniFlashPlayer.MainFlashPlayer.StartCoroutine(UniFlashPlayer.MainFlashPlayer.LoadImageFromUrl(this));
		}
    public override string ToString()
    {
      return base.ToString() +"; Image :" + Image ;
    }
    public override void Finished()
    {
      string contentType = ResponseHeaders["CONTENT-TYPE"];

      if(String.IsNullOrEmpty(Www.error))
      {
        if (contentType.Contains("image") && contentType != "image/jpg" && contentType != "image/png" && contentType != "image/jpeg")
        {
          _image = new Texture2D(1, 1, TextureFormat.ARGB32, false);
          _image.LoadFromBytes(Www.downloadHandler.data);
          GarbageCollectorTimer.Collect();
        }
        else
        {
          _image = new Texture2D(2, 2);
          _image.LoadImage(Www.downloadHandler.data);
        }
      }

      base.Finished();
    }
	}

  // MovieLoader (MovieTexture через WWW.GetMovieTexture) удалён при миграции на Unity 2019:
  // стрим видео теперь делает VideoPlayer.url напрямую в MediaPlayer (без WWW).

  public class WWWErrorEventArgs : EventArgs
  {
    private string _error;
    public string Error
    {
      get { return _error; }
    }

    public WWWErrorEventArgs(string error)
    {
      _error = error;
    }
  }
}