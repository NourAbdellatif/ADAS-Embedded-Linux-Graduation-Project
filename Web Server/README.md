# ADAS Web Server

This project is an ADAS (Advanced Driver Assistance System) Web Server built using .NET 7. It provides APIs for user authentication, registration, bug reporting, and integrates a Postgres database. 
The server follows the Clean Architecture principles and utilizes the CQRS (Command Query Responsibility Segregation) pattern. The APIs are used by a QT application

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Configuration](#configuration)
- [Usage](#usage)
- [API Reference](#api-reference)
- [Contributing](#contributing)
- [License](#license)

## Features

- User registration and authentication.
- APIs for bug reporting.
- Clean Architecture with CQRS pattern.
- Integration with Postgres database.

## Prerequisites

Before running the ADAS Web Server, ensure you have the following installed:

- .NET 7 SDK: [Download](https://dotnet.microsoft.com/download)
- Postgres database: [Download](https://www.postgresql.org/download/)

## Installation

1. Clone the repository:

```shell
git clone https://github.com/NourAbdellatif/ADAS.API.git
```
2. Navigate to the project directory:
```shell
cd ADAS.API
```
3. Build Project:
```shell
dotnet build
```
4. Navigate to the project directory:
```shell
dotnet ef database update
```

## Configuration
In the ADAS.API Web project create Properties directory and launchsettings.json in it with the profiles
```json
{
  "$schema": "https://json.schemastore.org/launchsettings.json",
  "iisSettings": {
    "windowsAuthentication": false,
    "anonymousAuthentication": true,
    "iisExpress": {
      "applicationUrl": "http://localhost:15411",
      "sslPort": 44375
    }
  },
  "profiles": {
    "Local": {
      "commandName": "Project",
      "dotnetRunMessages": true,
      "launchBrowser": true,
      "launchUrl": "swagger",
      "applicationUrl": "https://localhost:7091",
      "environmentVariables": {
        "ASPNETCORE_ENVIRONMENT": "Development",
        "DB_CONNECTION_STRING": "Host=localhost;Username=adas_user;Password=adas_password;Database=adas_db",
        "SENDGRID_API_KEY": "",
        "SENDGRID_SENDER_EMAIL": "noor.abdelatif@gmail.com",
        "SENDGRID_SENDER_NAME": "ADAS",
        "SENDGRID_ADMIN_EMAIL": "noorapp7@gmail.com",
        "SENDGRID_ADMIN_NAME": "ADAS",
        "STRIPE_API_KEY": "",
        "IS_EMAIL_ENABLED": "true",
        "DOMAIN": "https://localhost:7091"
      }
    },
  }
}
```

## Usage
Start the webserver
```shell
dotnet run
```

## API Reference
This swagger link shows all the implemented endpoints https://adas-eece2023.azurewebsites.net/swagger/index.html

## Contributing
Contributions to the ADAS Web Server project are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License
The ADAS Web Server is licensed under the MIT License.
