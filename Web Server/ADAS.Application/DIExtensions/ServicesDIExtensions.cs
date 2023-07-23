using ADAS.Application.Interfaces;
using ADAS.Application.Services;
using Microsoft.Extensions.DependencyInjection;

namespace ADAS.Application.DIExtensions;

public static class ServicesDIExtensions
{
	public static IServiceCollection AddServices(this IServiceCollection services)
	{
		services.AddTransient<IMailingService, MailingService>();
		return services;
	}
}