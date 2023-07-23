namespace ADAS.Domain.Entities;

public class Car : EntityBase
{
	public Car()
	{
		BugTickets = new List<BugTicket>();
	}
	public string OwnerEmail { get; set; }

	public virtual List<BugTicket> BugTickets { get; set; }
}