
namespace Flash
{
	public interface IBindable
	{
		ControlNode ControlNode { get; set; }
		bool IsTakenFromParent { get; set; }
    ConstraintAttribute[] Constraints { get; set; }
	}
}
