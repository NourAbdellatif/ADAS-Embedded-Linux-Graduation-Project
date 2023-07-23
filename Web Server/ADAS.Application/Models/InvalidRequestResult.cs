namespace ADAS.Application.Models;

public class InvalidRequestResult
{
	public string Field { get; set; }
	public IEnumerable<string> Errors { get; set; }

	public InvalidRequestResult(string field, IEnumerable<string> errors)
	{
		Field = field;
		Errors = errors;
	}
}