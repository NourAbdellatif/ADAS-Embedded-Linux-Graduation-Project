using ADAS.Application.BusinessLogic.Bugs.DTOs;
using ADAS.Application.Interfaces;
using AutoMapper;
using MediatR;

namespace ADAS.Application.BusinessLogic.Bugs.Queries.GetBugTickets;

public class GetBugTicketsQueryHandler : IRequestHandler<GetBugTicketsQuery, List<string>>
{
	private readonly IAdasDbContext _context;
	private readonly IMapper _mapper;

	public GetBugTicketsQueryHandler(IAdasDbContext context, IMapper mapper)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		_mapper = mapper ?? throw new ArgumentNullException(nameof(mapper));
	}

	public async Task<List<string>> Handle(GetBugTicketsQuery request, CancellationToken cancellationToken)
	{
		var bugs = _context.BugTickets.Where(b => b.CarId == request.CarId).ToList();
		return bugs.Select(b => b.Title).ToList();
	}
}