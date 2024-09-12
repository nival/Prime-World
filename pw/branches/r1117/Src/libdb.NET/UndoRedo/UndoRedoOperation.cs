namespace libdb.UndoRedo
{
	public interface IUndoRedoOperation : IOwnerable
	{
		void Undo();
		void Redo();

		string DefaultCaption { get; }
	}
}
