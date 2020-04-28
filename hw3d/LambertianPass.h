#pragma once
#include "RenderQueuePass.h"
#include "Job.h"
#include <vector>
#include "Sink.h"
#include "Source.h"
#include "Stencil.h"
#include "Camera.h"

class Graphics;

namespace Rgph
{
	class LambertianPass : public RenderQueuePass
	{
	public:
		void BindMainCamera( const Camera& cam ) noexcept
		{
			pMainCamera = &cam;
		}
		LambertianPass( Graphics& gfx,std::string name )
			:
			RenderQueuePass( std::move( name ) )
		{
			using namespace Bind;
			RegisterSink( DirectBufferSink<RenderTarget>::Make( "renderTarget",renderTarget ) );
			RegisterSink( DirectBufferSink<DepthStencil>::Make( "depthStencil",depthStencil ) );
			RegisterSource( DirectBufferSource<RenderTarget>::Make( "renderTarget",renderTarget ) );
			RegisterSource( DirectBufferSource<DepthStencil>::Make( "depthStencil",depthStencil ) );
			AddBind( Stencil::Resolve( gfx,Stencil::Mode::Off ) );
		}
		void Execute( Graphics& gfx ) const noxnd override
		{
			assert( pMainCamera );
			pMainCamera->BindToGraphics( gfx );
			RenderQueuePass::Execute( gfx );
		}
	private:
		const Camera* pMainCamera = nullptr;
	};
}