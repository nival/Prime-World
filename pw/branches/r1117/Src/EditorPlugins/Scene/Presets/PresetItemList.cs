using System.Collections.ObjectModel;

namespace EditorPlugins.Scene.Presets
{
	public class PresetItemList<T> : Collection<T>
		where T : IPresetItem
	{
		private readonly ScenePreset owner;

		public PresetItemList(ScenePreset _preset)
		{
			owner = _preset;
			Clear();
		}

		protected override void InsertItem( int _index, T _item )
		{
			_item.SetOwner( owner );
			base.InsertItem( _index, _item );
		}

		protected override void RemoveItem( int _index )
		{
			owner.AddNoneObject( Items[_index].GetComponentObject() );
			base.RemoveItem( _index );
			owner.Updated();
		}

		protected override void ClearItems()
		{	
			foreach ( var item in Items )
			{
				owner.AddNoneObject( item.GetComponentObject() );
			}

			base.ClearItems();
			owner.Rebuild();
			owner.Updated();
		}
	}
}