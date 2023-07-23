using ADAS.Application.Constants;
using ADAS.Application.Interfaces;
using ADAS.Application.Models.Emails;
using ADAS.Domain.Entities;
using AutoMapper;
using MediatR;
using Microsoft.EntityFrameworkCore;

namespace ADAS.Application.BusinessLogic.Bugs.Commands.CreateBugTicket;

public class CreateBugTicketCommandHandler : IRequestHandler<CreateBugTicketCommand, Unit>
{
	private readonly IAdasDbContext _context;
	private readonly IMapper _mapper;
	private readonly IMailingService _mailingService;

	public CreateBugTicketCommandHandler(IAdasDbContext context, IMapper mapper, IMailingService mailingService)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		_mapper = mapper ?? throw new ArgumentNullException(nameof(mapper));
		_mailingService = mailingService ?? throw new ArgumentNullException(nameof(mailingService));
	}

	public async Task<Unit> Handle(CreateBugTicketCommand request, CancellationToken cancellationToken)
	{
		var car = _context.Cars.Include(u => u.BugTickets).SingleOrDefault(u => u.Id == request.CarId);
		var bugTicket = _mapper.Map<BugTicket>(request);
		car?.BugTickets.Add(bugTicket);
		await _context.SaveChangesAsync(cancellationToken);
		var bugReportViewModel = _mapper.Map<BugReportViewModel>(bugTicket);
		await _mailingService.SendEmailAsync(bugReportViewModel, EmailSubjects.BugReport);
		return Unit.Value;
	}
}