namespace ADAS.Domain.Entities;

public class BugTicket : EntityBase
{
	public string Title { get; set; }
	public Car Car { get; set; }
	public string CarId { get; set; }
	public bool IsResolved { get; set; }
}