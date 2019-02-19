//
// Created by Emil Hörnlund on 2018-09-14.
//

#ifndef COREGAMELIB_SCENEMANAGER_HPP
#define COREGAMELIB_SCENEMANAGER_HPP

#include <memory>
#include <vector>

namespace CGL { //CoreGameLib
    class IGame;
    class IScene;

    class SceneHandler {
    private:
        IGame *m_game;

        std::vector<std::shared_ptr<IScene>> m_scenes;

        std::vector<std::shared_ptr<IScene>> m_deadScenes;

        SceneHandler(const SceneHandler &original);

        SceneHandler &operator=(const SceneHandler &original);
    public:
        explicit SceneHandler(IGame *game);

        virtual ~SceneHandler();

        bool isEmpty() const;

        void addActiveScene(std::shared_ptr<IScene> scene);

        void addInactiveScene(std::shared_ptr<IScene> scene);

        IScene &getActiveScene() const;

        void inactivateActivateScene();

        void dropActiveScene();

        void cleanup();
    };
}

#endif //COREGAMELIB_SCENEMANAGER_HPP
