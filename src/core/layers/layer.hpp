#ifndef __layer_h__
#define __layer_h__

#include <string>

#include "platform_detection.hpp"
#include "events.hpp"

namespace core::layers
{
    /**
     * @brief Base class for all layers in Trimana engine.
     *
     * This class is the base class for all layers in the Trimana engine. The Trimana engine
     * is designed to be modular, and this class provides a common interface for all layers
     * to follow. The Trimana engine will call the methods defined in this class in a specific
     * order at runtime, allowing different layers to interact with each other and perform
     * their specific tasks.
     *
     * @details
     *
     * The Trimana engine will call the `on_attach()` method when a layer is first added to
     * the engine. The layer can use this method to perform any necessary setup or initialization.
     *
     * The `on_detach()` method will be called when a layer is removed from the engine.
     * The layer can use this method to clean up any resources or perform any necessary cleanup.
     *
     * The `on_update()` method will be called every frame to update the layer's state. The layer
     * can use this method to update its internal state based on any external input or events.
     *
     * The `on_event()` method will be called when an event is triggered. The layer can use this
     * method to handle the event and perform any necessary actions in response to the event.
     *
     * All layers must provide a unique name to identify them in the engine, and this name can be
     * retrieved using the `get_name()` method.
     */
    class TRIMANA_API layer
    {
    public:
        /**
         * @brief Default constructor.
         *
         * This constructor is used to create a layer object. The layer name is provided
         * as a parameter to uniquely identify the layer in the engine.
         */
        layer(const std::string &name) : m_debug_name(name) {}

        /**
         * @brief Destructor.
         *
         * This destructor is called when the layer is removed from the engine. It performs
         * any necessary cleanup or deallocation of resources.
         */
        virtual ~layer() = default;

        /**
         * @brief Called when a layer is first added to the engine.
         *
         * This method is called by the engine when a layer is first added to the engine.
         * The layer can use this method to perform any necessary setup or initialization.
         */
        virtual void on_attach() {}

        /**
         * @brief Called when a layer is removed from the engine.
         *
         * This method is called by the engine when a layer is removed from the engine.
         * The layer can use this method to clean up any resources or perform any necessary cleanup.
         */
        virtual void on_detach() {}

        /**
         * @brief Called every frame to update the layer's state.
         *
         * This method is called by the engine every frame to update the layer's state.
         * The layer can use this method to update its internal state based on any external input
         * or events.
         */
        virtual void on_update() {}

        /**
         * @brief Called when an event is triggered.
         *
         * This method is called by the engine when an event is triggered. The layer can use
         * this method to handle the event and perform any necessary actions in response to the event.
         */
        virtual void on_event(core::events::event &e) {}

        /**
         * @brief Get the name of the layer.
         *
         * Returns the name of the layer, which is provided in the constructor to uniquely identify
         * the layer in the engine.
         */
        const std::string &get_name() const { return m_debug_name; }

    protected:
        /**
         * @brief Store the name of the layer.
         */
        std::string m_debug_name{};
    };
}
#endif // __layer_h__