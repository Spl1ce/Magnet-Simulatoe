#include "Particals.h"

Particals::Particals()
{
    parts.clear();
    partSize = 0;
}

Particals::~Particals()
{
}

void Particals::addPart(bool state, sf::Vector2i pos)
{
    particalParts temp;
    temp.state = state;

    temp.pos.x = (float)pos.x;
    temp.pos.y = (float)pos.y;

    temp.vel = sf::Vector2f(0,0);

    parts.push_back(temp);
    partSize = parts.size();
}

void Particals::reset()
{
    drawArray.clear();
    parts.clear();
    partSize = 0;
}

void Particals::update(float fps, sf::RenderWindow &win)
{
    if(partSize < 1){ return; }

    drawArray.clear();

    for(unsigned int i = 0; i < partSize; i++)
    {
        for(unsigned int ii = 0; ii < partSize; ii++)
        {
            if(i != ii) {
                const bool sideX = parts[i].pos.x > parts[ii].pos.x;
                const bool sideY = parts[i].pos.y > parts[ii].pos.y;

                const float disX = fmaxf(abs(parts[i].pos.x - parts[ii].pos.x), 1);
                const float disY = fmaxf(abs(parts[i].pos.y - parts[ii].pos.y), 1);

                const float dis = fmaxf(findDistance(parts[i].pos, parts[ii].pos), 1);

                if(dis < minDis && parts[i].state != parts[ii].state)
                {
                    parts[i].vel.x = 0 - parts[i].vel.x;
                    parts[i].vel.y = 0 - parts[i].vel.y;
                } else
                {
                    float rat = disX / (disX + disY);

                    if(parts[i].state == parts[ii].state)
                    {
                        if (sideX) { parts[i].vel.x += (force / dis) * rat; }
                        else { parts[i].vel.x -= (force / dis) * rat; }

                        if (sideY) { parts[i].vel.y += (force / dis) * (1 - rat); }
                        else { parts[i].vel.y -= (force / dis) * (1 - rat); }
                    } else
                    {
                        if (sideX) { parts[i].vel.x -= (force / dis) * rat; }
                        else { parts[i].vel.x += (force / dis) * rat; }

                        if (sideY) { parts[i].vel.y -= (force / dis) * (1 - rat); }
                        else { parts[i].vel.y += (force / dis) * (1 - rat); }
                    }
                }
            }
        }

        if(wrap){
            if(parts[i].pos.x < 0){
                parts[i].pos.x = (float)dim::width;
            }
            if(parts[i].pos.y < 0){
                parts[i].pos.y = (float)dim::height;
            }
            if(parts[i].pos.x > (float)dim::width){
                parts[i].pos.x = 0;
            }
            if(parts[i].pos.y > (float)dim::height){
                parts[i].pos.y = 0;
            }
        } else {
            if(parts[i].pos.x < 0){
                parts[i].pos.x = 0;
                parts[i].vel.x = abs(parts[i].vel.x);
            }
            if(parts[i].pos.y < 0){
                parts[i].pos.y = 0;
                parts[i].vel.y = abs(parts[i].vel.y);
            }
            if(parts[i].pos.x > (float)dim::width){
                parts[i].pos.x = (float)dim::width;
                parts[i].vel.x = 0 - abs(parts[i].vel.x);
            }
            if(parts[i].pos.y > (float)dim::height){
                parts[i].pos.y = (float)dim::height;
                parts[i].vel.y = 0 - abs(parts[i].vel.y);
            }
        }

        parts[i].pos.x += parts[i].vel.x / fps;
        parts[i].pos.y += parts[i].vel.y / fps;

        /*DRAWING*/
        temp[0].position.x = parts[i].pos.x - parSize;
        temp[0].position.y = parts[i].pos.y - parSize;

        temp[1].position.x = parts[i].pos.x + parSize;
        temp[1].position.y = parts[i].pos.y - parSize;

        temp[2].position.x = parts[i].pos.x + parSize;
        temp[2].position.y = parts[i].pos.y + parSize;

        temp[3].position.x = parts[i].pos.x - parSize;
        temp[3].position.y = parts[i].pos.y + parSize;

        if(parts[i].state)
        {
            temp[0].color = partColor::pos;
            temp[1].color = partColor::pos;
            temp[2].color = partColor::pos;
            temp[3].color = partColor::pos;
        } else
        {
            temp[0].color = partColor::neg;
            temp[1].color = partColor::neg;
            temp[2].color = partColor::neg;
            temp[3].color = partColor::neg;
        }
        drawArray.append(temp[0]);
        drawArray.append(temp[1]);
        drawArray.append(temp[2]);
        drawArray.append(temp[3]);
    }
    win.draw(drawArray);
}

float Particals::findDistance(sf::Vector2f pos1, sf::Vector2f pos2)
{
    float disX = pos1.x - pos2.x;
    float disY = pos1.y - pos2.y;

    return sqrtf((disX * disX) + (disY * disY));
}






