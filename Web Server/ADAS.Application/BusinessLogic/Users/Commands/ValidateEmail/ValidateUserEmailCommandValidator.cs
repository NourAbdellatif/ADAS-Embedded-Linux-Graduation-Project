using FluentValidation;

namespace ADAS.Application.BusinessLogic.Users.Commands.ValidateEmail;

public class ValidateUserEmailCommandValidator : AbstractValidator<ValidateUserEmailCommand>
{
	public ValidateUserEmailCommandValidator()
	{
		RuleFor(c => c.Email)
			.NotNull()
			.NotEmpty()
			.EmailAddress()
			.WithMessage("Email is not valid");
	}
}