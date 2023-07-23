using ADAS.Application.Interfaces;
using FluentValidation;

namespace ADAS.Application.BusinessLogic.Bugs.Queries.GetBugTickets;

public class GetBugTicketsQueryValidator : AbstractValidator<GetBugTicketsQuery>
{
	private readonly IAdasDbContext _context;
	public GetBugTicketsQueryValidator(IAdasDbContext context)
	{
		_context = context ?? throw new ArgumentNullException(nameof(context));
		RuleFor(q => q.CarId)
			.NotNull()
			.NotEmpty()
			.Must(carId =>
			{
				return _context.Cars.Any(car => car.Id == carId);
			})
			.WithMessage("Car with this id does not exist");
	}
}