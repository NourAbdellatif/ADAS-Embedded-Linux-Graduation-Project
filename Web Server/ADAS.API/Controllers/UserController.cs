using ADAS.Application.BusinessLogic.Users.Commands.ActivateEmail;
using ADAS.Application.BusinessLogic.Users.Commands.ForgotPassword;
using ADAS.Application.BusinessLogic.Users.Commands.LoginUser;
using ADAS.Application.BusinessLogic.Users.Commands.RegisterUser;
using ADAS.Application.BusinessLogic.Users.Commands.ValidateEmail;
using MediatR;
using Microsoft.AspNetCore.Mvc;

namespace ADAS.API.Controllers;

[ApiController]
[Route("[controller]/[action]")]
public class UserController : ControllerBase
{
	private readonly ILogger<UserController> _logger;
	private readonly ISender _sender;

	public UserController(ILogger<UserController> logger, ISender sender)
	{
		_logger = logger ?? throw new ArgumentNullException(nameof(logger));
		_sender = sender ?? throw new ArgumentNullException(nameof(sender));
	}

	[HttpPost]
	public async Task<IActionResult> Register([FromBody] RegisterUserCommand command)
	{
		_logger.LogInformation("Registering User");
		var id = await _sender.Send(command);
		return Ok(id);
	}
	
	[HttpPost]
	public async Task<IActionResult> Login([FromBody] LoginUserCommand command)
	{
		_logger.LogInformation("Registering User");
		var id = await _sender.Send(command);
		return Ok(id);
	}
	
	[HttpPost]
	public async Task<IActionResult> ValidateEmail([FromBody] ValidateUserEmailCommand command)
	{
		_logger.LogInformation("Validating Email");
		var isValid = await _sender.Send(command);
		return Ok(isValid);
	}
	
	[HttpPost]
	public async Task<IActionResult> ForgotPassword([FromBody] ForgotPasswordCommand command)
	{
		_logger.LogInformation("Forgot Password");
		var isValid = await _sender.Send(command);
		return Ok(isValid);
	}

	[HttpGet]
	public async Task<IActionResult> ActivateEmail([FromQuery] ActivateEmailCommand command)
	{
		_logger.LogInformation("Activating Email");
		await _sender.Send(command);
		return Ok("Activated");
	}

}