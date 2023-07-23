using ADAS.Application.Interfaces;
using FluentValidation;

namespace ADAS.Application.BusinessLogic.Users.Commands.ForgotPassword;

public class ForgotPasswordCommandValidator : AbstractValidator<ForgotPasswordCommand>
{
	private readonly IAdasDbContext _context;
	public ForgotPasswordCommandValidator(IAdasDbContext context)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		RuleFor(c => c.Email)
			.EmailAddress()
			.NotEmpty()
			.NotNull()
			.Must(email =>
			{
				return _context.Users.Any(u => u.Email == email.Trim());
			})
			.WithMessage("Email does not exist in the system.");
	}
}