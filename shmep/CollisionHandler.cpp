#include "CollisionHandler.h"
#include "GameObject.h"
#include "Scene.h"
#include "Collider.h"
#include "setup.h"


void CollisionHandler::update()
{
    int i = 0;
    while (i < gameObject->scene->rootGameObjects.size()) {
        int j = i + 1;
        GameObject* obj1 = gameObject->scene->rootGameObjects[i];
        while (j < gameObject->scene->rootGameObjects.size()) {
            GameObject* obj2 = gameObject->scene->rootGameObjects[j];
            Collider* c1, * c2;
            c1 = obj1->getColllider();
            c2 = obj2->getColllider();
            if (c1 != nullptr && c2 != nullptr) {
                bool collision = c1->checkCollision(c2);
                if (collision) {
                    if ((obj1->tag == "PlayerProjectile" && obj2->tag == "Enemy") ||
                        obj1->tag == "Enemy" && obj2->tag == "PlayerProjectile") {
                        delete(obj1);
                        delete(obj2);
                        i--;
                        break;
                    }
                    if ((obj1->tag == "Player" && (obj2->tag == "Enemy" || obj2->tag == "EnemyProjectile")) ||
                        (obj1->tag == "Enemy" || obj1->tag == "EnemyProjectile") && obj1->tag == "Player") {
                        
                        gameObject->scene->clear();
                        startGameSetup();
                        return;
                    }
                }
            }
            j++;
        }
        i++;
    }
}
