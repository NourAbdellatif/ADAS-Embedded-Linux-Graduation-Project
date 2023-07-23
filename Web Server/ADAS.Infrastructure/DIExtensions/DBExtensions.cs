using ADAS.Application.Interfaces;
using ADAS.Infrastructure.Persistence;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;

namespace ADAS.Infrastructure.DIExtensions;

public static class DBExtensions
{
	public static IServiceCollection AddDatabase(this IServiceCollection services)
	{
		var connectionString = Environment.GetEnvironmentVariable("DB_CONNECTION_STRING");
		AppContext.SetSwitch("Npgsql.EnableLegacyTimestampBehavior", true);

		services.AddDbContext<AdasDBContext>((provider, options) =>
		{
			options.UseNpgsql(connectionString, o => o.UseNetTopologySuite());
		});

		services.AddScoped<IAdasDbContext>(provider => provider.GetRequiredService<AdasDBContext>());
		return services;
	}
}