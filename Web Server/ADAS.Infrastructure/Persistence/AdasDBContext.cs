using System.Reflection;
using ADAS.Application.Interfaces;
using ADAS.Domain.Entities;
using Microsoft.EntityFrameworkCore;

namespace ADAS.Infrastructure.Persistence;

public class AdasDBContext : DbContext, IAdasDbContext
{
	public DbSet<User> Users => Set<User>();
	public DbSet<BugTicket> BugTickets => Set<BugTicket>();
	public DbSet<Car> Cars => Set<Car>();

	public AdasDBContext(DbContextOptions<AdasDBContext> options) : base(options)
	{
	}
	
	protected override void OnModelCreating(ModelBuilder builder)
	{
		builder.ApplyConfigurationsFromAssembly(Assembly.GetExecutingAssembly());

		base.OnModelCreating(builder);
	}
	

}