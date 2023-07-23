using ADAS.Clients.Interfaces;
using Convie.Clients.Converters;
using Microsoft.Extensions.DependencyInjection;

namespace ADAS.Clients.MailingClient.DIExtensions;

public static class MailingDIExtensions
{
	public static IServiceCollection AddMailingClient(this IServiceCollection services)
	{
		services.AddOptions<EmailConfiguration>()
			.Configure((options) =>
			{
				var isEmailEnabled = Environment.GetEnvironmentVariable("IS_EMAIL_ENABLED");
				options.APIKey = Environment.GetEnvironmentVariable("SENDGRID_API_KEY");
				options.FromEmail = Environment.GetEnvironmentVariable("SENDGRID_SENDER_EMAIL");
				options.FromName = Environment.GetEnvironmentVariable("SENDGRID_SENDER_NAME");
				options.IsEmailEnabled = bool.TryParse(isEmailEnabled, out bool result) && result;
				options.AdminEmail = Environment.GetEnvironmentVariable("SENDGRID_ADMIN_EMAIL");
				options.AdminName = Environment.GetEnvironmentVariable("SENDGRID_ADMIN_NAME");
			});
		services.AddLocalization(options => options.ResourcesPath = "Localization");
		services.AddScoped<IViewRender, ViewRender>();
		services.AddSingleton<ISendGridClient, SendgridClient>();
		return services;
	}
}