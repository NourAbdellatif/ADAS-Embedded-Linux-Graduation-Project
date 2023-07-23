using ADAS.Application.Interfaces;
using MediatR;
using Microsoft.EntityFrameworkCore;

namespace ADAS.Application.BusinessLogic.Users.Commands.ValidateEmail;

public class ValidateUserEmailCommandHandler : IRequestHandler<ValidateUserEmailCommand, string>
{
	private readonly IAdasDbContext _context;

	public ValidateUserEmailCommandHandler(IAdasDbContext context)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
	}

	public async Task<string> Handle(ValidateUserEmailCommand request, CancellationToken cancellationToken)
	{
		var user = await _context.Users.SingleOrDefaultAsync(u => u.Email == request.Email.Trim());
		if (user == null)
		{
			return "false";
		}
		if(user.IsActive)
		{
			return "true";
		}
		return "banned";
	}
}