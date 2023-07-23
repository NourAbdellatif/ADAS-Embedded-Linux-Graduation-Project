FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS base
WORKDIR /app
EXPOSE 80
EXPOSE 443

FROM mcr.microsoft.com/dotnet/sdk:7.0 AS build
WORKDIR /src
COPY ["ADAS.API/ADAS.API.csproj", "ADAS.API/"]
RUN dotnet restore "ADAS.API/ADAS.API.csproj"
COPY . .
WORKDIR "/src/ADAS.API"
RUN dotnet build "ADAS.API.csproj" -c Release -o /app/build

FROM build AS publish
RUN dotnet publish "ADAS.API.csproj" -c Release -o /app/publish

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "ADAS.API.dll"]
