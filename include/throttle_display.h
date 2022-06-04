#ifndef ATG_ENGINE_SIM_THROTTLE_DISPLAY_H
#define ATG_ENGINE_SIM_THROTTLE_DISPLAY_H

#include "ui_element.h"

#include "engine.h"
#include "engine_simulator.h"
#include "geometry_generator.h"

class ThrottleDisplay : public UiElement {
    public:
        ThrottleDisplay();
        virtual ~ThrottleDisplay();

        virtual void initialize(EngineSimApplication *app);
        virtual void destroy();

        virtual void update(float dt);
        virtual void render();

        EngineSimulator *m_simulator;

    protected:
        virtual void renderThrottle(const Bounds &bounds);
};

#endif /* ATG_ENGINE_SIM_THROTTLE_DISPLAY_H */
