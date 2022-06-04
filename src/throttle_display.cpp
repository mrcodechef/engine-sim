#include "../include/throttle_display.h"

#include "../include/geometry_generator.h"
#include "../include/engine_sim_application.h"

ThrottleDisplay::ThrottleDisplay() {
    m_simulator = nullptr;
}

ThrottleDisplay::~ThrottleDisplay() {
    /* void */
}

void ThrottleDisplay::initialize(EngineSimApplication *app) {
    UiElement::initialize(app);
}

void ThrottleDisplay::destroy() {
    UiElement::destroy();
}

void ThrottleDisplay::update(float dt) {
    UiElement::update(dt);
}

void ThrottleDisplay::render() {
    UiElement::render();

    drawFrame(m_bounds, 1.0, ysMath::Constants::One, m_app->getBackgroundColor());

    const Bounds bounds = m_bounds.inset(10.0f);
    const Bounds title = bounds.verticalSplit(1.0f, 0.9f);
    drawCenteredText("THROTTLE", title.inset(10.0f), 24.0f);

    const Bounds mainDrawArea = bounds.verticalSplit(0.0f, 0.9f);
    renderThrottle(mainDrawArea);
}

void ThrottleDisplay::renderThrottle(const Bounds &bounds) {
    GeometryGenerator *gen = m_app->getGeometryGenerator();

    const float width = pixelsToUnits(bounds.width());
    const float height = pixelsToUnits(bounds.height());
    const float size = std::fmin(width, height);

    const Point origin = getRenderPoint(bounds.getPosition(Bounds::center));

    const float carbBore = size * 0.4f;
    const float carbHeight = size * 0.5f;
    const float plateWidth = carbBore * 0.8f;

    GeometryGenerator::Line2dParameters params;
    params.lineWidth = size * 0.01f;

    GeometryGenerator::Circle2dParameters circleParams;
    circleParams.radius = params.lineWidth / 2.0f;
    circleParams.maxEdgeLength = m_app->pixelsToUnits(5.0f);

    GeometryGenerator::GeometryIndices indices;
    gen->startShape();

    params.x0 = origin.x + carbBore / 2.0f;
    params.y0 = origin.y - carbHeight / 2.0f;
    params.x1 = origin.x + carbBore / 2.0f;
    params.y1 = origin.y + carbHeight / 2.0f;
    gen->generateLine2d(params);

    circleParams.center_x = params.x1;
    circleParams.center_y = params.y1;
    gen->generateCircle2d(circleParams);

    circleParams.center_x = params.x1;
    circleParams.center_y = params.y0;
    gen->generateCircle2d(circleParams);

    params.x0 = origin.x - carbBore / 2.0f;
    params.x1 = origin.x - carbBore / 2.0f;
    gen->generateLine2d(params);

    circleParams.center_x = params.x1;
    circleParams.center_y = params.y1;
    gen->generateCircle2d(circleParams);

    circleParams.center_x = params.x1;
    circleParams.center_y = params.y0;
    gen->generateCircle2d(circleParams);

    // Draw throttle plate
    const float throttleAngle =
        m_simulator->getEngine()->getThrottle() * ysMath::Constants::PI / 2;
    const float cos_theta = std::cos(throttleAngle);
    const float sin_theta = std::sin(throttleAngle);

    params.y0 = origin.y - cos_theta * plateWidth / 2.0f;
    params.x0 = origin.x - sin_theta * plateWidth / 2.0f;
    params.y1 = origin.y + cos_theta * plateWidth / 2.0f;
    params.x1 = origin.x + sin_theta * plateWidth / 2.0f;
    gen->generateLine2d(params);

    circleParams.center_x = params.x0;
    circleParams.center_y = params.y0;
    gen->generateCircle2d(circleParams);

    circleParams.center_x = params.x1;
    circleParams.center_y = params.y1;
    gen->generateCircle2d(circleParams);

    gen->endShape(&indices);

    m_app->getShaders()->SetBaseColor(ysMath::Constants::One);
    m_app->drawGenerated(indices, 0x11, m_app->getShaders()->GetUiFlags());
}
