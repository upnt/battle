#include "player.h"
#include <string>

player::player(tstring name, int maxHp, int atk) : 
    name(name), maxHp(maxHp), atk(atk)
{
    hp = maxHp;
}

void player::draw(HDC& hdc, bool isEnemy)
{
    drawHp(hdc, isEnemy);
    if (isEnemy)
        return;

    Rectangle(hdc, 
        textBoxRec.left,  textBoxRec.top, 
        textBoxRec.right, textBoxRec.bottom);

    DrawText(hdc, formatTexts().c_str(), -1, &textRec, DT_WORDBREAK | DT_LEFT);
    
}

void player::drawHp(HDC& hdc, bool isEnemyHp)
{
    auto hpRec = new RECT();
    if (isEnemyHp)
        DrawText(hdc, (name + TEXT(": ") + to_tstring(hp) + TEXT("/") + to_tstring(maxHp)).c_str(), -1, &enemyHpRec, DT_RIGHT);
    else
        DrawText(hdc, (name + TEXT(": ") + to_tstring(hp) + TEXT("/") + to_tstring(maxHp)).c_str(), -1, &myHpRec, DT_LEFT);
}

void player::attack(player& another)
{
    if (!isAlive())
        return;
    appendTexts(name + TEXT(" attacked ") + another.name);
    another.damage(atk);

}


bool player::damage(int damage)
{
    if (!isAlive())
        return true;

    hp -= damage;
    
    appendTexts(name + TEXT(" damaged at ") + to_tstring(damage));

    if (!isAlive())
    {
        hp = 0;
        appendTexts(name + TEXT(" is dead"));
        return false;
    }

    
    return true;
}


bool player::isAlive()
{
    return (hp > 0);
}

void player::appendTexts(tstring text)
{
    if (texts[0].empty())
    {
        texts[0] = text;
        return;
    }

    if (texts[1].empty())
    {
        texts[1] = text;
        return;
    }

    if (texts[2].empty())
    {
        texts[2] = text;
        return;
    }

    texts[0] = texts[1];
    texts[1] = texts[2];
    texts[2] = text;
    return;

}

tstring player::formatTexts()
{
    return texts[0] + TEXT("\n") + texts[1] + TEXT("\n") + texts[2];
}
