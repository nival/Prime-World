using libdb.DB;

namespace libdb
{
	public interface IOwnerable
	{
		DBResource GetOwner();
	}
}
