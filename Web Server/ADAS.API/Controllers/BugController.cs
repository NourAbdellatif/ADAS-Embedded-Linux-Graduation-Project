using ADAS.Application.BusinessLogic.Bugs.Commands.CreateBugTicket;
using ADAS.Application.BusinessLogic.Bugs.Queries.GetBugTickets;
using MediatR;
using Microsoft.AspNetCore.Mvc;

namespace ADAS.API.Controllers;

[ApiController]
[Route("[controller]/[action]")]
public class BugController : ControllerBase
{
	private readonly ISender _sender;

	public BugController(ISender sender)
	{
		_sender = sender ?? throw new ArgumentNullException(nameof(sender));
	}

	[HttpPost]
	public async Task<IActionResult> Create([FromBody] CreateBugTicketCommand command)
	{
		await _sender.Send(command);
		return Ok();
	}
	
	[HttpGet("{carId}")]
	public async Task<IActionResult> Get([FromRoute] GetBugTicketsQuery query)
	{
		var ticket = await _sender.Send(query);
		return Ok(ticket);
	}
}