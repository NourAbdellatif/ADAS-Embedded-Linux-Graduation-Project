using ADAS.Application.Constants;
using ADAS.Application.Interfaces;
using ADAS.Application.Models.Emails;
using ADAS.Application.Utilities;
using MediatR;
using Microsoft.EntityFrameworkCore;

namespace ADAS.Application.BusinessLogic.Users.Commands.ForgotPassword;

public class ForgotPasswordCommandHandler : IRequestHandler<ForgotPasswordCommand, Unit>
{
	private readonly IMailingService _mailingService;
	private readonly IAdasDbContext _context;

	public ForgotPasswordCommandHandler(IMailingService mailingService, IAdasDbContext context)
	{
		_mailingService = mailingService ?? throw new ArgumentNullException(nameof(mailingService));
		_context = context ?? throw new ArgumentNullException(nameof(context));
	}

	public async Task<Unit> Handle(ForgotPasswordCommand request, CancellationToken cancellationToken)
	{
		var user  = await _context.Users.SingleOrDefaultAsync(u => u.Email == request.Email.Trim());
		user.Password = Functions.RandomString();
		var forgotPasswordModel = new ForgotPasswordViewModel()
		{
			Email = request.Email,
			Password = user.Password
		};
		await _context.SaveChangesAsync(cancellationToken);
		await _mailingService.SendEmailAsync(forgotPasswordModel, EmailSubjects.ForgotPassword);
		return Unit.Value;
	}
}