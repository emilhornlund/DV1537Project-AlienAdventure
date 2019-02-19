//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef ALIENADVENTURE_SCENEMANAGER_HPP
#define ALIENADVENTURE_SCENEMANAGER_HPP

#include <memory>
#include <vector>

class IGame;
class IScene;

class SceneHandler {
private:
    IGame* m_game;

    std::vector<std::shared_ptr<IScene>> m_scenes;

    std::vector<std::shared_ptr<IScene>> m_deadScenes;

    SceneHandler(const SceneHandler &original);

    SceneHandler& operator=(const SceneHandler &original);
public:
    explicit SceneHandler(IGame* game);

    virtual ~SceneHandler();

    bool isEmpty() const;

    void addActiveScene(std::shared_ptr<IScene> scene);

    void addInactiveScene(std::shared_ptr<IScene> scene);

    IScene& getActiveScene() const;

    void inactivateActivateScene();

    void dropActiveScene();

    void cleanup();
};

#endif //ALIENADVENTURE_SCENEMANAGER_HPP
