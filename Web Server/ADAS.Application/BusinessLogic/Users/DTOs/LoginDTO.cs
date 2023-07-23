using ADAS.Application.Common.DTOs;

namespace ADAS.Application.BusinessLogic.Users.DTOs;

public class LoginDTO : BaseEntityDTO
{
	public int RemainingLoginAttempts { get; set; }
}