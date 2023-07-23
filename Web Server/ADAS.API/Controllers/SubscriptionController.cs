using Microsoft.AspNetCore.Mvc;
using Stripe.Checkout;

namespace ADAS.API.Controllers;

[ApiController]
[Route("[controller]/[action]")]
public class SubscriptionController : ControllerBase
{
	[HttpGet]
	public ActionResult Create()
	{
		var domain = "http://localhost:4242";
		var options = new SessionCreateOptions
		{
			LineItems = new List<SessionLineItemOptions>
			{
				new SessionLineItemOptions
				{
					// Provide the exact Price ID (for example, pr_1234) of the product you want to sell
					Price = "price_1NN1lXKJxM4rppCoFXCa2gta",
					Quantity = 1,
				},
			},
			Mode = "subscription",
			SuccessUrl = domain + "/success.html",
			CancelUrl = domain + "/cancel.html",
		};
		var service = new SessionService();
		Session session = service.Create(options);

		Response.Headers.Add("Location", session.Url);
		return new StatusCodeResult(303);
	}
	
}