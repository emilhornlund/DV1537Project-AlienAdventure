//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_SPLASHSCENE_HPP
#define ALIENADVENTURE_SPLASHSCENE_HPP

#include "core/interfaces/IScene.hpp"

class SplashScene : public IScene {
private:
    SplashScene(const SplashScene &original);

    SplashScene& operator=(const SplashScene &original);
protected:
    void performInit() override;

    void performDeinit() override;

    void processExtraEvents() override;

    void performExtraUpdates(const float dt) override;

    void performExtraDrawing() override;

    void didPause() override;

    void didResume() override;
public:
    explicit SplashScene(IGame* game);

    ~SplashScene() override;

    void cleanup() override;
};

#endif //ALIENADVENTURE_SPLASHSCENE_HPP
