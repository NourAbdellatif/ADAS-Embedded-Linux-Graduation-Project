using ADAS.Application.BusinessLogic.Bugs.DTOs;
using MediatR;

namespace ADAS.Application.BusinessLogic.Bugs.Queries.GetBugTickets;

public class GetBugTicketsQuery : IRequest<List<string>>
{
	public string CarId { get; set; }
}