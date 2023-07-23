using ADAS.Application.BusinessLogic.Users.DTOs;
using ADAS.Application.Common.Commands;
using ADAS.Application.Common.DTOs;
using MediatR;

namespace ADAS.Application.BusinessLogic.Users.Commands.LoginUser;

public class LoginUserCommand : BaseUserCommand, IRequest<LoginDTO>
{

}