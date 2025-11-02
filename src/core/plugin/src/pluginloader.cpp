#include <pluginloader.h>


PluginLoader::PluginLoader(std::unique_ptr<IPluginLoaderImpl> impl) :
    m_impl(std::move(impl))
{
}

std::shared_ptr<IPlugin> PluginLoader::load(const std::string &path)
{
    return m_impl->load(path);
}

void PluginLoader::unload() {
    m_impl->unload();
}

bool PluginLoader::isLoaded() const {
    return m_impl->isLoaded();
}

