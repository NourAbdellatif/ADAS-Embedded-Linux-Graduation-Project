using System.Net;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using SendGrid;
using SendGrid.Helpers.Mail;
using ISendGridClient = ADAS.Clients.Interfaces.ISendGridClient;

namespace ADAS.Clients.MailingClient;

public class SendgridClient : ISendGridClient
{
	private readonly ILogger<SendgridClient> _logger;
	private readonly SendGridClient _sendGridClient;
	private readonly EmailConfiguration _emailConfig;
	public SendgridClient(
		ILogger<SendgridClient> logger,
		IOptions<EmailConfiguration> configuration)
	{
		_logger = logger ?? throw new ArgumentNullException(nameof(logger));
		_emailConfig = configuration?.Value ?? throw new ArgumentNullException(nameof(configuration));

		var apiKey = _emailConfig.APIKey;
		_sendGridClient = new SendGridClient(apiKey);
	}
	public async Task<HttpStatusCode?> SendAsync(EmailMessage message)
	{
		if (!_emailConfig.IsEmailEnabled)
		{
			_logger.LogInformation("current {env} doesn't allow sending emails", Environment.GetEnvironmentVariable("ASPNETCORE_ENVIRONMENT"));

			return null;
		}

		if (message.FromEmail == null || message.FromName == null)
		{
			message.FromEmail = _emailConfig.FromEmail;
			message.FromName = _emailConfig.FromName;
		}

		var reciever = new EmailAddress(message.ReceiverEmail);
		var sendgridMessage = new SendGridMessage()
		{
			From = new EmailAddress()
			{
				Email = message.FromEmail,
				Name = message.FromName
			},
			Subject = message.Subject,
			HtmlContent = message.HtmlBody
		};
		sendgridMessage.AddTo(reciever);
		_logger.LogInformation("sending email to {email} from {fromEmail}", message.ReceiverEmail, message.FromEmail);
		var response = await _sendGridClient.SendEmailAsync(sendgridMessage);
		
		return response.StatusCode;
	}
}