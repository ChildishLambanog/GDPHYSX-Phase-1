#include "ContactResolver.h"

void P6::ContactResolver::ResolveContacts(std::vector<ParticleContact*> contacts, float time)
{
    unsigned int resolveCount = 0;
    unsigned int maxIterations = max_iterations;

    while (resolveCount < maxIterations)
    {
        //Find the contact with the least separating speed
        int minIndex = -1;
        float minSeparatingSpeed = std::numeric_limits<float>::max();

        for (size_t i = 0; i < contacts.size(); i++)
        {
            float sepSpeed = contacts[i]->GetSeparatingSpeed();
            if (sepSpeed < minSeparatingSpeed || contacts[i]->depth > 0)
            {
                minSeparatingSpeed = sepSpeed;
                minIndex = static_cast<int>(i);
            }
        }

        //If all separating speeds are >= 0 and depth <= 0 we break
        if (minIndex == -1 || (minSeparatingSpeed >= 0.0f && contacts[minIndex]->depth <= 0.0f))
        {
            break;
        }

        //Resolve the contact with the least separating speed
        contacts[minIndex]->Resolve(time);
        resolveCount++;
    }
}
