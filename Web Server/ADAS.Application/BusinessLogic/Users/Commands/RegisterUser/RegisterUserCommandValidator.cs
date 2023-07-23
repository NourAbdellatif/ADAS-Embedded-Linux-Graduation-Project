using ADAS.Application.Common.Validators;
using ADAS.Application.Interfaces;
using FluentValidation;

namespace ADAS.Application.BusinessLogic.Users.Commands.RegisterUser;

public class RegisterUserCommandValidator : BaseUserCommandValidator<RegisterUserCommand>
{

	public RegisterUserCommandValidator(IAdasDbContext context) : base(context)
	{
	}
}