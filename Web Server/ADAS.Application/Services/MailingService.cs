using ADAS.Application.Interfaces;
using ADAS.Application.Models.Emails;
using ADAS.Clients.Interfaces;
using ADAS.Clients.MailingClient;
using Microsoft.Extensions.Options;

namespace ADAS.Application.Services;

public class MailingService : IMailingService
{
	private readonly ISendGridClient _sendGridClient;
	private readonly IViewRender _viewRender;
	private readonly EmailConfiguration _emailConfig;

	public MailingService(ISendGridClient sendGridClient, IViewRender viewRender, IOptions<EmailConfiguration> config)
	{
		_sendGridClient = sendGridClient ?? throw new ArgumentNullException(nameof(sendGridClient));
		_viewRender = viewRender ?? throw new ArgumentNullException(nameof(viewRender));
		_emailConfig = config?.Value ?? throw new ArgumentNullException(nameof(config));
	}

	public async Task SendEmailAsync<T>(T viewModel, string subject)
	{
		var emailMessage = GenerateEmailMessage(viewModel, subject);
		await _sendGridClient.SendAsync(emailMessage);
	}

	private EmailMessage GenerateEmailMessage<T>(T viewModel, string subject)
	{
		string viewPath = GetViewPath(typeof(T));
		var htmlBody = _viewRender.Render(viewPath, viewModel);
    
		var emailMessage = new EmailMessage
		{
			Subject = subject,
			HtmlBody = htmlBody
		};
    
		if (viewModel is UserRegistrationViewModel registrationViewModel)
		{
			emailMessage.ReceiverEmail = registrationViewModel.Email;
		}
		else if (viewModel is BugReportViewModel bugReportViewModel)
		{
			emailMessage.ReceiverEmail = _emailConfig.FromEmail;
			emailMessage.FromEmail = _emailConfig.AdminEmail;
			emailMessage.FromName = _emailConfig.AdminName;
		}
		else if (viewModel is ActivateEmailViewModel activateEmailViewModel)
		{
			emailMessage.ReceiverEmail = activateEmailViewModel.Email;
		}
		else if (viewModel is ForgotPasswordViewModel forgotPasswordViewModel)
		{
			emailMessage.ReceiverEmail = forgotPasswordViewModel.Email;
		}
    
		return emailMessage;
	}

	private string GetViewPath(Type viewModelType)
	{
		if (viewModelType == typeof(UserRegistrationViewModel))
		{
			return "Emails/Email";
		}
		else if (viewModelType == typeof(BugReportViewModel))
		{
			return "Emails/BugReport";
		}
		else if (viewModelType == typeof(ActivateEmailViewModel))
		{
			return "Emails/ActivateEmail";
		}
		else if (viewModelType == typeof(ForgotPasswordViewModel))
		{
			return "Emails/ForgotPasswordEmail";
		}
    
		throw new ArgumentException("Invalid view model type.");
	}

}