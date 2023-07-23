using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ADAS.Infrastructure.Migrations
{
    /// <inheritdoc />
    public partial class userloginattempts : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "RemainingLoginAttempts",
                table: "Users",
                type: "integer",
                nullable: false,
                defaultValue: 0);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "RemainingLoginAttempts",
                table: "Users");
        }
    }
}
