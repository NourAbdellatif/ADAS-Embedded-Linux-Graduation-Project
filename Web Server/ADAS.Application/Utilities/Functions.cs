namespace ADAS.Application.Utilities;

public static class Functions
{
	private static Random random = new Random();

	public static string RandomString()
	{
		const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		return new string(Enumerable.Repeat(chars, 10)
			.Select(s => s[random.Next(s.Length)]).ToArray());
	}
}