using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace ADAS.Infrastructure.Migrations
{
    /// <inheritdoc />
    public partial class addcarstable : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_BugTickets_Users_UserId",
                table: "BugTickets");

            migrationBuilder.AlterColumn<string>(
                name: "UserId",
                table: "BugTickets",
                type: "text",
                nullable: true,
                oldClrType: typeof(string),
                oldType: "text");

            migrationBuilder.AddColumn<string>(
                name: "CarId",
                table: "BugTickets",
                type: "text",
                nullable: false,
                defaultValue: "");

            migrationBuilder.CreateTable(
                name: "Cars",
                columns: table => new
                {
                    Id = table.Column<string>(type: "text", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Cars", x => x.Id);
                });

            migrationBuilder.CreateIndex(
                name: "IX_BugTickets_CarId",
                table: "BugTickets",
                column: "CarId");

            migrationBuilder.AddForeignKey(
                name: "FK_BugTickets_Cars_CarId",
                table: "BugTickets",
                column: "CarId",
                principalTable: "Cars",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_BugTickets_Users_UserId",
                table: "BugTickets",
                column: "UserId",
                principalTable: "Users",
                principalColumn: "Id");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_BugTickets_Cars_CarId",
                table: "BugTickets");

            migrationBuilder.DropForeignKey(
                name: "FK_BugTickets_Users_UserId",
                table: "BugTickets");

            migrationBuilder.DropTable(
                name: "Cars");

            migrationBuilder.DropIndex(
                name: "IX_BugTickets_CarId",
                table: "BugTickets");

            migrationBuilder.DropColumn(
                name: "CarId",
                table: "BugTickets");

            migrationBuilder.AlterColumn<string>(
                name: "UserId",
                table: "BugTickets",
                type: "text",
                nullable: false,
                defaultValue: "",
                oldClrType: typeof(string),
                oldType: "text",
                oldNullable: true);

            migrationBuilder.AddForeignKey(
                name: "FK_BugTickets_Users_UserId",
                table: "BugTickets",
                column: "UserId",
                principalTable: "Users",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
