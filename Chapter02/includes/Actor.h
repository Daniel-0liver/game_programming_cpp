#pragma once
#include <memory>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
class Component;
struct Vector2 { float x{}; float y{}; };
enum class State { Active, Paused, Dead };
class Actor {
public:
    explicit Actor(std::string name, Vector2 position = {});
    ~Actor();
    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;
    Vector2 getPosition() const { return mPosition; }
    void setPosition(Vector2 position) { mPosition = position; }
    State getState() const { return mState; }
    void setState(State state) { mState = state; }
    const std::string& getName() const { return mName; }
    void AddComponent(std::unique_ptr<Component> component);
    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer) const;
private:
    std::string mName;
    Vector2 mPosition;
    State mState{State::Active};
    std::vector<std::unique_ptr<Component>> mComponents;
};
