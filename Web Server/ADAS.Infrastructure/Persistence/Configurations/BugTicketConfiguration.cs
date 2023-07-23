using ADAS.Domain.Entities;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace ADAS.Infrastructure.Persistence.Configurations;

public class BugTicketConfiguration : IEntityTypeConfiguration<BugTicket>
{
	public void Configure(EntityTypeBuilder<BugTicket> builder)
	{
		builder.Property(b => b.Id)
			.ValueGeneratedOnAdd();
	}
}