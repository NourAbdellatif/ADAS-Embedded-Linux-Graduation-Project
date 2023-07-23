using ADAS.Application.Common.Commands;
using ADAS.Application.Interfaces;
using FluentValidation;

namespace ADAS.Application.Common.Validators;

public class BaseUserCommandValidator<T> : AbstractValidator<T> where T : BaseUserCommand
{
	private readonly IAdasDbContext _context;
	public BaseUserCommandValidator(IAdasDbContext context)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		RuleFor(c => c.Email)
			.NotEmpty()
			.EmailAddress();
		
		RuleFor(c => c.Email)
			.Must(email =>
			{
				return !_context.Users.Any(u=>u.Email == email.Trim());
			})
			.WithMessage("Email already exists !");
	}
	
	public BaseUserCommandValidator()
	{
		RuleFor(c => c.Email)
			.NotEmpty()
			.EmailAddress();

		RuleFor(c => c.Password)
			.NotEmpty()
			.NotNull();
	}
	
}