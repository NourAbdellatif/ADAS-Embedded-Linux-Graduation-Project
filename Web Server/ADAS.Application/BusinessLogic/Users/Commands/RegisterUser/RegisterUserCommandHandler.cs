using ADAS.Application.Common.DTOs;
using ADAS.Application.Constants;
using ADAS.Application.Interfaces;
using ADAS.Application.Models.Emails;
using ADAS.Application.Utilities;
using ADAS.Domain.Entities;
using AutoMapper;
using MediatR;

namespace ADAS.Application.BusinessLogic.Users.Commands.RegisterUser;

public class RegisterUserCommandHandler : IRequestHandler<RegisterUserCommand, BaseEntityDTO>
{
	private readonly IAdasDbContext _context;
	private readonly IMapper _mapper;
	private readonly IMailingService _mailingService;

	public RegisterUserCommandHandler(IAdasDbContext context, IMapper mapper, IMailingService mailingService)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		_mapper = mapper ??  throw new ArgumentNullException(nameof(mapper));
		_mailingService = mailingService ?? throw new ArgumentNullException(nameof(mailingService));
	}

	public async Task<BaseEntityDTO> Handle(RegisterUserCommand request, CancellationToken cancellationToken)
	{
		var user = _mapper.Map<User>(request);
		user.Password = Functions.RandomString();
		await _context.Users.AddAsync(user);
		await _context.SaveChangesAsync(cancellationToken);
		var userModel = _mapper.Map<UserRegistrationViewModel>(user);
		await _mailingService.SendEmailAsync(userModel, EmailSubjects.Registration);
		return new BaseEntityDTO()
		{
			Id = user.Id,
		};
	}
}