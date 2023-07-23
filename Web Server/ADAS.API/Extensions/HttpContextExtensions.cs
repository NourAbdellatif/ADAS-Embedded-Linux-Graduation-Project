using ADAS.Application.Models;
using Microsoft.AspNetCore.Mvc;

namespace ADAS.API.Extensions;

public static class HttpContextExtensions
{
	public static BadRequestObjectResult HandleInvalidRequest(this ActionContext context)
	{
		var result = context.ModelState
			.Where(x => x.Value.Errors.Count > 0)
			.Select(x => new InvalidRequestResult(x.Key, x.Value.Errors.Select(x => x.ErrorMessage)));

		return new BadRequestObjectResult(result);
	}
}