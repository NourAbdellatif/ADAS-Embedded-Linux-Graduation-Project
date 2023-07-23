using System.Security.Policy;
using ADAS.Application.BusinessLogic.Users.DTOs;
using ADAS.Application.Constants;
using ADAS.Application.Interfaces;
using ADAS.Application.Models.Emails;
using ADAS.Application.Utilities;
using MediatR;
using Microsoft.AspNetCore.Http;
using Microsoft.EntityFrameworkCore;

namespace ADAS.Application.BusinessLogic.Users.Commands.LoginUser;

public class LoginUserCommandHandler : IRequestHandler<LoginUserCommand, LoginDTO>
{
	private readonly IAdasDbContext _context;
	private readonly IMailingService _mailingService;
	public LoginUserCommandHandler(IAdasDbContext context, IMailingService mailingService)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		_mailingService = mailingService ?? throw new ArgumentNullException(nameof(mailingService));
	}

	public async Task<LoginDTO> Handle(LoginUserCommand request, CancellationToken cancellationToken)
	{
		var user = await _context.Users.SingleOrDefaultAsync(u => u.Email == request.Email);
		if (user.Password == request.Password)
		{
			if (user.IsActive)
			{
				user.RemainingLoginAttempts = AccountLockoutConstants.MaxLoginAttempts;
				await _context.SaveChangesAsync(cancellationToken);
				return new LoginDTO()
				{
					Id = user.Id,
					RemainingLoginAttempts = user.RemainingLoginAttempts
				};
			}
		}

		user.RemainingLoginAttempts -= 1;
		if (user.RemainingLoginAttempts <= 0)
		{
			user.IsActive = false;
			string domain = Environment.GetEnvironmentVariable("DOMAIN");
			string activateEmailUrl = $"{domain}/User/ActivateEmail?email={user.Email}";
			user.Password = Functions.RandomString();
			var activateEmailModel = new ActivateEmailViewModel()
			{
				Email = user.Email,
				Link = activateEmailUrl,
				Password = user.Password
			};
			await _mailingService.SendEmailAsync(activateEmailModel, EmailSubjects.ActivateEmail);
		}

		await _context.SaveChangesAsync(cancellationToken);
		return new LoginDTO()
		{
			RemainingLoginAttempts = user.RemainingLoginAttempts
		};

	}
}