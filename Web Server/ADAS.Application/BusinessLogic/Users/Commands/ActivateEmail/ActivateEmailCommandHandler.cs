using ADAS.Application.Constants;
using ADAS.Application.Interfaces;
using MediatR;
using Microsoft.EntityFrameworkCore;

namespace ADAS.Application.BusinessLogic.Users.Commands.ActivateEmail;

public class ActivateEmailCommandHandler : IRequestHandler<ActivateEmailCommand>
{
	private readonly IAdasDbContext _context;

	public ActivateEmailCommandHandler(IAdasDbContext context)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
	}

	public async Task<Unit> Handle(ActivateEmailCommand request, CancellationToken cancellationToken)
	{
		var user = await _context.Users.SingleOrDefaultAsync(u => u.Email == request.Email);
		user.IsActive = true;
		user.RemainingLoginAttempts = AccountLockoutConstants.MaxLoginAttempts;
		await _context.SaveChangesAsync(cancellationToken);
		return Unit.Value;
	}
}