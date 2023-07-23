using ADAS.Domain.Entities;
using Microsoft.EntityFrameworkCore;

namespace ADAS.Application.Interfaces;

public interface IAdasDbContext
{
	DbSet<User> Users { get; }
	DbSet<BugTicket> BugTickets { get; }
	DbSet<Car> Cars { get; }
	Task<int> SaveChangesAsync(CancellationToken cancellationToken);
}