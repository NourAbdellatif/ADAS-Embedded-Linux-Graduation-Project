
using ADAS.Application.BusinessLogic.Users.Commands.RegisterUser;
using ADAS.Application.Constants;
using ADAS.Application.Models.Emails;
using ADAS.Domain.Entities;
using AutoMapper;

namespace ADAS.Application.BusinessLogic.Users.Profiles;

public class UserProfile : Profile
{
	public UserProfile()
	{
		CreateMap<RegisterUserCommand, User>()
			.ForMember(u => u.RemainingLoginAttempts, opt => opt.MapFrom(c => AccountLockoutConstants.MaxLoginAttempts))
			.ForMember(u => u.IsActive, opt => opt.MapFrom(c => true));
		
		CreateMap<User, UserRegistrationViewModel>();
	}
}