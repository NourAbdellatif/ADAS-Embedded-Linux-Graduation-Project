using MediatR;

namespace ADAS.Application.BusinessLogic.Users.Commands.ForgotPassword;

public class ForgotPasswordCommand : IRequest<Unit>
{
	public string Email { get; set; }
}