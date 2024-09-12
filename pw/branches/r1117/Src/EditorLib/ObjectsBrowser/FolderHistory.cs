using System.Collections.Generic;

namespace EditorLib.ObjectsBrowser
{
	/// <summary>
	/// Класс для ведения истории бровзинга, написан для ObjectBrowser, 
	/// но можно использовать для работы с любой историей стороковых значений.
	/// FILO
	/// </summary>
	public class FolderHistory
	{
    private const int HISTORY_SIZE = 10;
    private readonly List<string> history = new List<string>( HISTORY_SIZE );

		private int currentItemIndex = -1;

		/// <summary>
		/// Можно ли промотать историю назад на шаг
		/// </summary>
		public bool CanGoBack
		{
			get { return currentItemIndex > 0; }
		}

		/// <summary>
		/// Можно ли промотать историю вперед на шаг
		/// </summary>
		public bool CanGoForward
		{
			get { return currentItemIndex < (history.Count - 1); }
		}
    
    public int CurrentItemIndex
    {
      get { return currentItemIndex; }
    }

		/// <summary>
		/// Возвращает текущее выбранное значение в истории.
		/// </summary>
		public string CurrentItem
		{
			get
			{
				if (currentItemIndex < 0 || currentItemIndex >= history.Count)
					return null;

				return history[currentItemIndex];
			}
		}

    public IEnumerable<KeyValuePair<string, int>> GetBackwardItems()
	  {
      if( currentItemIndex >= 0 && currentItemIndex < history.Count )
      {
        for( int i = currentItemIndex - 1; i >= 0; --i )
        {
          yield return new KeyValuePair<string, int>(history[i], i);
        }
      }
	  }

    public IEnumerable<KeyValuePair<string, int>> GetForwardItems()
    {
      if( currentItemIndex >= 0 && currentItemIndex < history.Count )
      {
        for( int i = currentItemIndex + 1; i < history.Count; ++i )
        {
          yield return new KeyValuePair<string, int>( history[i], i );
        }
      }
    }

		/// <summary>
		/// Перемещает позицию в истории на еденицу назад.
		/// </summary>
		/// <returns>Возвращает предидущий элемент истории(который после выполнения функции стал текущим)</returns>
		/// <remarks>Если назад историю мотать некуда - просто ничего не происходит</remarks>
		public string GoBack()
		{
			if (CanGoBack)
				currentItemIndex--;

			return CurrentItem;
		}

		/// <summary>
		/// Перемещает позицию в истории на еденицу вперед.
		/// </summary>
		/// <returns>Возвращает следующий элемент истории(который после выполнения функции стал текущим)</returns>
		/// <remarks>Если вперед историю мотать некуда - просто ничего не происходит</remarks>
		public string GoForward()
		{
			if (CanGoForward)
				currentItemIndex++;

			return CurrentItem;
		}

		/// <summary>
		/// Добавляет элемент в историю. Удаляет последующие элементы перед добавлением.
		/// Удаляет первый(самый старый) элемент истории, при превышении лимита глубины хранения истории.
		/// </summary>
		public void Add(string _item)
		{
			if ( currentItemIndex < (history.Count - 1) )
				history.RemoveRange(currentItemIndex + 1, history.Count - currentItemIndex - 1);

			if (history.Count == HISTORY_SIZE)
				history.RemoveAt(0);

      history.Add( _item );
			
      currentItemIndex = history.Count - 1;
		}

		/// <summary>
		/// Удаляет все упоминания элемента из истории 
		/// </summary>
		internal void Remove(string _item)
		{
		  history.RemoveAll( x => x == _item );
			currentItemIndex = -1;
		}

    /// <summary>
    /// Переход к элементу, существующему в истории, без добавления его как нового элемента
    /// </summary>
    /// <param name="_index">индекс элемента (zero based)</param>
    /// <returns>Путь к папке или null</returns>
    internal string NavigateTo( int _index )
    {
      currentItemIndex = _index;
      
      return CurrentItem;
    }
	}
}