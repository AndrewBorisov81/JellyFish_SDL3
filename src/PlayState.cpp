#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "JellyFish.h"
#include "JellyFishMover.h"
#include "Constants.h"
#include "Mover.h"
#include "Point.h"
#include "Math2.h"

#include <stdlib.h>
#include <time.h> 
#include <vector>
#include <functional>

const std::string PlayState::s_playID = "PLAY";

bool PlayState::onEnter()
{
  srand(time(NULL));

  int W, H;
  SDL_GetWindowSize(TheGame::Instance()->getWindow(), &W, &H);
  m_screenSize.w = W;
  m_screenSize.h = H;
  
  //Test jelly fish
  Point posJellyFish(500, 250);
  createJellyFish(posJellyFish);

  return true;
}

bool PlayState::onExit()
{
  m_gameObjects.clear();
  m_toDeleteGameObjects.clear();
  TheTextureManager::Instance()->clearFromTextureMap("helicopter");

  return true;
}

void PlayState::handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    m_leftMouseDown = true;
                    m_mouseClickDone = false; // optional
                    printf("Left button pressed\n"); // debug
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    m_leftMouseDown = false;
                    m_mouseClickDone = false;
                     printf("Left button released\n"); // debug
                }
                break;
        }
    }

    int buttons = SDL_GetMouseState(&m_mouseX, &m_mouseY);

    if (buttons & SDL_BUTTON_LEFT)
    {
        if (m_leftMouseDown && !m_mouseClickDone)
        {
            mouseClick(m_mouseX, m_mouseY);
            m_mouseClickDone = true;
        }
    }
}



void PlayState::update()
{
  for (auto &el : m_gameObjects)
    el->update();

  for (auto &el : m_gameObjects)
  {
    if (el->isToDelete())
      m_toDeleteGameObjects.push_back(el);
  }

  if (!m_toDeleteGameObjects.empty())
  {
    for (auto &curElement : m_toDeleteGameObjects)
    {
      auto result = std::find(m_gameObjects.begin(), m_gameObjects.end(), curElement);

      if (result != m_gameObjects.end())
        m_gameObjects.erase(result);
    }
    m_toDeleteGameObjects.clear();
  }
}

void PlayState::render()
{
  for (auto &el : m_gameObjects)
  {
    el->draw();
  }
}

GameObject* PlayState::createJellyFish(const Point& pos)
{
  Size screenSize(m_screenSize.w, m_screenSize.h);
  Size objSize(m_objSize.w, m_objSize.h);

  Point posJellyFish(pos.x, pos.y);
  posJellyFish.x -= m_objSize.w / 2;
  posJellyFish.y -= m_objSize.h / 2;

  Vector2D randomEndPoint = getRandomPoint(posJellyFish, screenSize, objSize);

  auto lfGetRandomPoint = [this, posJellyFish, screenSize, objSize](Point)->Vector2D {return this->getRandomPoint(posJellyFish, m_screenSize, m_objSize); };
  std::function<Vector2D(Point)> f;
  f = lfGetRandomPoint;

  Mover* jellyFishMover = new JellyFishMover(randomEndPoint);
  jellyFishMover->setCallBackStopMoveEndPath(f);

  GameObject* jellyFish = JellyFish::create(posJellyFish.x, posJellyFish.y, jellyFishMover);

  m_gameObjects.push_back(jellyFish);

  return jellyFish;
}

void PlayState::deleteGameObject(GameObject* gameObject, std::vector<GameObject*> toDeleteGameObjects)
{
  gameObject->toDelete();
}

Vector2D PlayState::getRandomPoint(const Point& beginPoint, const Size& screenSize, const Size& objectSize)
{
  Vector2D beginVec(beginPoint.x, beginPoint.y);
  Vector2D randomPoint;

  while (!checkScreenBorders(screenSize, randomPoint, objectSize) && !checkMinDist(beginVec, randomPoint, objectSize))
  {
    int randomX = 0;
    int randomY = 0;

    randomPoint.setX(0);
    randomPoint.setY(0);

    randomX = rand() % ((int)screenSize.w + 1);
    randomY = rand() % ((int)screenSize.h + 1);

    randomPoint.setX((float)randomX);
    randomPoint.setY((float)randomY);
  }

  return Vector2D(randomPoint.getX(), randomPoint.getY());
}

bool PlayState::checkScreenBorders(const Size& screenSize, const Vector2D& objPos, const Size& objSize)
{
  bool noCollision = true;

  if (objPos.getX() - 0.5 * objSize.w < 0 || objPos.getX() + 0.5 * objSize.w > screenSize.w) return false;
  if (objPos.getY() - 0.5 * objSize.h < 0 || objPos.getY() + 0.5 * objSize.h > screenSize.h) return false;

  return noCollision;
}

bool PlayState::checkMinDist(const Vector2D& beginPoint, const Vector2D& endPoint, const Size& objectSize)
{
  bool minDist = false;

  float maxLengthObject = (objectSize.h > objectSize.w) ? objectSize.h : objectSize.w;

  float minDistBeginEndPoint = 2 * maxLengthObject;

  float dist = Math2::distance(beginPoint.getX(), beginPoint.getY(), endPoint.getX(), endPoint.getY());

  if (dist < maxLengthObject)
  {
    minDist = true;
  }

  return minDist;
}

GameObject* PlayState::getHitObject(const Vector2D& pos, const std::vector<GameObject*>& gameObjects)
{
  GameObject* hitObject = nullptr;
  bool isHitObject = false;

  Point A, B, C, D;
  Point M((int)pos.getX(), (int)pos.getY());

  Size curObjSize;
  Vector2D curObjPos(0, 0);

  for (auto &el : gameObjects)
  {
    if (el->isClickable())
    {
      curObjSize.w = el->getWidth();
      curObjSize.h = el->getHeight();

      curObjPos.setX(el->getPosition().getX());
      curObjPos.setY(el->getPosition().getY());

      A.x = curObjPos.getX();
      A.y = curObjPos.getY();
      B.x = curObjPos.getX() + curObjSize.w;
      B.y = curObjPos.getY();
      C.x = curObjPos.getX() + curObjSize.w;
      C.y = curObjPos.getY() + curObjSize.h;
      D.x = curObjPos.getX();
      D.y = curObjPos.getY() + curObjSize.h;

      isHitObject = Math2::isInside(A, B, C, D, M);
    }

    if (isHitObject)
    {
      hitObject = el;
      break;
    }
  }

  return hitObject;
}

void PlayState::mouseClick(int mouseX, int mouseY)
{
  Vector2D mousePoint((float)mouseX, (float)mouseY);

  GameObject* hitObject = getHitObject(mousePoint, m_gameObjects);

  if (hitObject)
  {
    deleteGameObject(hitObject, m_toDeleteGameObjects);
  }
  else
  {
    Size curObjSize(m_objSize.w, m_objSize.h);

    bool isNoCollideBorders = checkScreenBorders(m_screenSize, mousePoint, curObjSize);

    if (isNoCollideBorders)
    {
      createJellyFish(Point(mouseX, mouseY));
    }
  }
  m_objectCreated = true;
}
