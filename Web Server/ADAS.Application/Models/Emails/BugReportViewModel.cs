namespace ADAS.Application.Models.Emails;

public class BugReportViewModel
{
	public string Id { get; set; }
	public string Title { get; set; }
	public string CarId { get; set; }
	public string CarOwnerEmail { get; set; }
}