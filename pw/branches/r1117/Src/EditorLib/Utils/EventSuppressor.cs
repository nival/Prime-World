using System;
using libdb.Diagnostics;

namespace EditorLib.Utils
{
	/// <summary>
	/// Класс EventSuppresser применяется для автоматического сбрасывания булевого флага.
	/// Часто нужно выставить булевый флаг, идентифицирующий о игнорировании 
	/// событий пока не будет выполнен какой-то кусок кода. 
	/// И после выполнения этого кода надо сбросить флаг.
	/// Проблема в том, что если внутри блока вызвать return или бросить исключение, 
	/// которое будет обработано выше по стеку блоком catch не выставить флаг в false,
	/// то события перестанут обрабатываться совсем. 
	/// При использовании EventSuppresser c блоком using такой проблемы не возникнет.
	/// 
	///	ЛУЧШЕ НЕ ИСПОЛЬЗОВАТЬ ЭТОТ КЛАСС ДЛЯ НОВЫХ КОМПОНЕНТ (ТОЛЬКО КАК ВРЕМЕННАЯ 
	/// МЕРА В СТАРЫХ С БУЛЕВЫМИ ФЛАГАМИ И СЛОЖНОЙ ЛОГИКОЙ, КОТОРУЮ НЕЛЬЗЯ БЫСТРО ОТРЕФАКТОРИТЬ), 
	/// СТРОЙТЕ ЛОГИКУ ПРИЛОЖЕНИЯ ТАК, ЧТОБЫ НЕ ПРИХОДИЛОСЬ САПРЕССИТЬ СОБЫТИЯ.
	/// ЕСЛИ МЕТОД НЕ ДОЛЖЕН БЫТЬ ВЫЗВАН, ТО НЕ ВЫЗЫВАЙТЕ ЕГО. 
	/// НЕ РЕГУЛИРУЙТЕ ЛОГИКУ ИСПОЛНЕНИЯ МЕТОДА БУЛЕВЫМИ ФЛАГАМИ.
	/// </summary>
	public sealed class EventSuppressor
	{
		#region Nested Types

		public class SuppressorTransaction : IDisposable
		{
			private readonly EventSuppressor suppressor;
			private bool disposed = false;

			public SuppressorTransaction( EventSuppressor _suppressor )
			{
				suppressor = _suppressor;
				suppressor.InternalSuppress();
			}

			public void Dispose()
			{
				if ( !disposed )
				{
					suppressor.Unsuppress();
					disposed = true;
				}
			}
		}

		#endregion

		private int suppressed = 0;

		public bool IsSuppressed
		{
			get { return suppressed > 0; }
		}

		public SuppressorTransaction Suppress()
		{
			return new SuppressorTransaction(this);
		}

		private void InternalSuppress()
		{
			++suppressed;
		}

		public void Unsuppress()
		{
			--suppressed;

			Log.Assert(suppressed >= 0, "");

			if ( suppressed < 0 )
				suppressed = 0;

		}
	}
}
