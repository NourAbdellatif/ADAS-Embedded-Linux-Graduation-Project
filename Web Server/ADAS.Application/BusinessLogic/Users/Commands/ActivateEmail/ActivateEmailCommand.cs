using MediatR;

namespace ADAS.Application.BusinessLogic.Users.Commands.ActivateEmail;

public class ActivateEmailCommand : IRequest<Unit>
{
	public string Email { get; set; }
}