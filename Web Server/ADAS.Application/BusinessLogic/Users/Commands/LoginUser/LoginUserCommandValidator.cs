using ADAS.Application.Common.Validators;
using ADAS.Application.Interfaces;
using FluentValidation;

namespace ADAS.Application.BusinessLogic.Users.Commands.LoginUser;

public class LoginUserCommandValidator : BaseUserCommandValidator<LoginUserCommand>
{
	private readonly IAdasDbContext _context;
	public LoginUserCommandValidator(IAdasDbContext context)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		RuleFor(x => x.Email)
			.NotEmpty()
			.EmailAddress();

		RuleFor(x => new { x.Email, x.Password })
			.Must(body =>
			{
				return _context.Users.Any(u => u.Email == body.Email.Trim());
			})
			.WithMessage("Invalid email");
		
		RuleFor(x => x.Email)
			.Must(email =>
			{
				var user = _context.Users.SingleOrDefault(u => u.Email == email.Trim());
				return user != null && user.IsActive;
			})
			.WithMessage("Email is not activated");
	}
}