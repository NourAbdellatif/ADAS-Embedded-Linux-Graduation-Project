using ADAS.Application.BusinessLogic.Bugs.Commands.CreateBugTicket;
using ADAS.Application.BusinessLogic.Bugs.DTOs;
using ADAS.Application.Models.Emails;
using ADAS.Domain.Entities;
using AutoMapper;

namespace ADAS.Application.BusinessLogic.Bugs.Profiles;

public class BugProfile : Profile
{
	public BugProfile()
	{
		CreateMap<BugTicket, BugReportViewModel>()
			.ForMember(model =>model.CarId, opt => opt.MapFrom(ticket => ticket.Car.Id))
			.ForMember(model => model.CarOwnerEmail, opt => opt.MapFrom(ticket => ticket.Car.OwnerEmail))
			.ReverseMap();
		
		CreateMap<BugTicket,CreateBugTicketCommand>()
			.ReverseMap();

		CreateMap<BugTicket, BugTicketDTO>()
			.ReverseMap();
	}
}