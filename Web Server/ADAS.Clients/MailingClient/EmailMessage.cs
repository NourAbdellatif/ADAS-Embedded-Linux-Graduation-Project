namespace ADAS.Clients.MailingClient;

public class EmailMessage
{
	public string Subject { get; set; }
	public string FromEmail { get; set; }
	public string FromName { get; set; }
	public string ReceiverEmail { get; set; }
	public string HtmlBody { get; set; }
}