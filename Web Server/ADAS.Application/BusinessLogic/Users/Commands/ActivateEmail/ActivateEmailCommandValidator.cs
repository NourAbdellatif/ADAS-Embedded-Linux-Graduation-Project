using ADAS.Application.Interfaces;
using FluentValidation;

namespace ADAS.Application.BusinessLogic.Users.Commands.ActivateEmail;

public class ActivateEmailCommandValidator : AbstractValidator<ActivateEmailCommand>
{
	private readonly IAdasDbContext _context;
	public ActivateEmailCommandValidator(IAdasDbContext context)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		RuleFor(c => c.Email)
			.Must(email =>
			{
				return  _context.Users.Any(u => u.Email == email.Trim() && u.IsActive == false);
			})
			.WithMessage("Invalid email address");
	}
}