using ADAS.Application.Common.Commands;
using ADAS.Application.Common.DTOs;
using MediatR;

namespace ADAS.Application.BusinessLogic.Users.Commands.RegisterUser;

public class RegisterUserCommand : BaseUserCommand, IRequest<BaseEntityDTO>
{
}