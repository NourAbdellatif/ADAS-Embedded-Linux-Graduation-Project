using MediatR;

namespace ADAS.Application.BusinessLogic.Users.Commands.ValidateEmail;

public class ValidateUserEmailCommand : IRequest<string>
{
	public string Email { get; set; }
}