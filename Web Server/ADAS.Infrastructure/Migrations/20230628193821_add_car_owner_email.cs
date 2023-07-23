using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ADAS.Infrastructure.Migrations
{
    /// <inheritdoc />
    public partial class addcarowneremail : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "OwnerEmail",
                table: "Cars",
                type: "text",
                nullable: false,
                defaultValue: "");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "OwnerEmail",
                table: "Cars");
        }
    }
}
