/**
 * @file Game.hpp
 * @date 2016-11-25
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_GAME_HPP
#define ALIENADVENTURE_GAME_HPP

#include <Core/IGame.hpp>

#include <memory>

namespace AA { //AlienAdventure
    class Game : public CGL::IGame {
    private:
        Game(const Game &original);

        Game &operator=(const Game &original);
    public:
        Game();

        ~Game() override;
    };
}

#endif /* ALIENADVENTURE_GAME_HPP */
