using MediatR;

namespace ADAS.Application.BusinessLogic.Bugs.Commands.CreateBugTicket;

public class CreateBugTicketCommand : IRequest<Unit>
{
	public string Title { get; set; }
	public string CarId { get; set; }
}