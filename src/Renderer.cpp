#include "Renderer.hpp"

#include "_SFMLRenderer.hpp"
std::unique_ptr<Renderer> Renderer::CreateBestRenderer() {
	return std::make_unique<SFMLRenderer>();
}