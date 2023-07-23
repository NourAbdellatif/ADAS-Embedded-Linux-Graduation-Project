using System.Net;
using ADAS.Clients.MailingClient;

namespace ADAS.Clients.Interfaces;

public interface ISendGridClient
{
	Task<HttpStatusCode?> SendAsync(EmailMessage message);
}