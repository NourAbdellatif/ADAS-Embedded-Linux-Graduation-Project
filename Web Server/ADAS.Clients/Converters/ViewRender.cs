using ADAS.Clients.Interfaces;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Abstractions;
using Microsoft.AspNetCore.Mvc.ModelBinding;
using Microsoft.AspNetCore.Mvc.Razor;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc.ViewFeatures;
using Microsoft.AspNetCore.Routing;

namespace Convie.Clients.Converters
{
	public class ViewRender : IViewRender
	{
		private readonly IRazorViewEngine _viewEngine;
		private readonly ITempDataProvider _tempDataProvider;
		private readonly IServiceProvider _serviceProvider;

		public ViewRender(
			IRazorViewEngine viewEngine,
			ITempDataProvider tempDataProvider,
			IServiceProvider serviceProvider)
		{
			_viewEngine = viewEngine ?? throw new ArgumentNullException(nameof(viewEngine));
			_tempDataProvider = tempDataProvider ?? throw new ArgumentNullException(nameof(tempDataProvider));
			_serviceProvider = serviceProvider ?? throw new ArgumentNullException(nameof(serviceProvider));
		}

		public string Render<TModel>(string name, TModel model)
		{
			return Render(name, model, null);
		}

		public string Render<TModel>(string name, TModel model, ViewDataDictionary viewData)
		{
			var actionContext = GetActionContext();
			

			var viewEngineResult = _viewEngine.FindView(actionContext, name, false);

			if (!viewEngineResult.Success)
			{
				throw new InvalidOperationException(string.Format("Couldn't find view '{0}'", name));
			}

			var view = viewEngineResult.View;
			ViewDataDictionary viewDataDict;

			if (viewData != null)
			{
				viewDataDict = new ViewDataDictionary<TModel>(viewData)
				{
					Model = model
				};
			}
			else
			{
				var metadataProvider = new EmptyModelMetadataProvider();
				var modelState = new ModelStateDictionary();
				viewDataDict = new ViewDataDictionary<TModel>(metadataProvider, modelState)
				{
					Model = model
				};
			}

			using (var output = new StringWriter())
			{
				var viewContext = new ViewContext(
					actionContext,
					view,
					viewDataDict,
					new TempDataDictionary(actionContext.HttpContext, _tempDataProvider),
					output,
					new HtmlHelperOptions());

				view.RenderAsync(viewContext).GetAwaiter().GetResult();

				return output.ToString();
			}
		}

		private ActionContext GetActionContext()
		{
			var httpContext = new DefaultHttpContext
			{
				RequestServices = _serviceProvider
			};

			return new ActionContext(httpContext, new RouteData(), new ActionDescriptor());
		}
	}
}
