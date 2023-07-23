using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Stripe;

namespace ADAS.Clients.PaymentClient.DIExtensions;

public static class PaymentDIExtensions
{
	public static void AddPaymentClient(this IServiceCollection services)
	{
		services.AddSingleton<IStripeClient>(c =>
		{
			var stripeClient = new StripeClient(Environment.GetEnvironmentVariable("STRIPE_SECRET_KEY"));
			return stripeClient;
		});
	}
}