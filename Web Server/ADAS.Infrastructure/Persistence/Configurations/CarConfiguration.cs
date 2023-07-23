using ADAS.Domain.Entities;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;

namespace ADAS.Infrastructure.Persistence.Configurations;

public class CarConfiguration : IEntityTypeConfiguration<Car>
{
	public void Configure(EntityTypeBuilder<Car> builder)
	{
		builder.Property(e => e.Id).ValueGeneratedOnAdd();

		builder.HasMany(e => e.BugTickets)
			.WithOne(e => e.Car)
			.HasForeignKey(e => e.CarId);
	}
}