using ADAS.API.Extensions;
using ADAS.Application.DIExtensions;
using ADAS.Infrastructure.DIExtensions;
using ADAS.Infrastructure.Persistence;
using FluentValidation.AspNetCore;
using Microsoft.EntityFrameworkCore;
using Stripe;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.

builder.Services.AddControllers()
	.AddFluentValidation(options =>
	{
		options.RegisterValidatorsFromAssembly(typeof(ApplicationDIExtensions).Assembly);
	})
	.ConfigureApiBehaviorOptions(options =>
	{
		options.InvalidModelStateResponseFactory = context => context.HandleInvalidRequest();
	});;
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();
builder.Services.AddRazorPages();

var services = builder.Services;

services.AddDatabase();
services.AddApplication();

var app = builder.Build();

StripeConfiguration.ApiKey = Environment.GetEnvironmentVariable("STRIPE_API_KEY");
// Configure the HTTP request pipeline.
app.UseSwagger();
app.UseSwaggerUI();
var scope = app.Services.CreateAsyncScope();
var db = scope.ServiceProvider.GetService<AdasDBContext>();
await db.Database.MigrateAsync();
app.UseRouting();
app.UseHttpsRedirection();
app.UseAuthorization();
app.UseEndpoints(endpoints =>
{
	endpoints.MapControllerRoute(
		name: "default",
		pattern: "{controller}/{action=Index}/{id?}");
	endpoints.MapGet("/", async context => { await context.Response.WriteAsync("Welcome to ADAS API."); });
	endpoints.MapGet("/status", async context => { await context.Response.WriteAsync("Welcome to ADAS API."); });
});

app.Run();