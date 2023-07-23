using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ADAS.Infrastructure.Migrations
{
    /// <inheritdoc />
    public partial class removebugdescription : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Description",
                table: "BugTickets");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "Description",
                table: "BugTickets",
                type: "text",
                nullable: false,
                defaultValue: "");
        }
    }
}
